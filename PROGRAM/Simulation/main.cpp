/*
 * SafeRide: Sistem Helm Pintar - FULL AVR C CONVERSION WITH OLED TEXT DISPLAY
 * Platform: ATmega2560 (Pure AVR C)
 * Pinout: RED=D6 (PH3), VIB=D5 (PE3), BUZ=D3 (PE5), BTN=D2 (PE4), BATT=A0 (PF0)
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

// ── Macro Manipulasi Bit ──────────────────────────────────────────────────
#define SET_BIT(reg, bit)   (reg |= (1 << bit))
#define CLR_BIT(reg, bit)   (reg &= ~(1 << bit))
#define TOGGLE_BIT(reg, bit)(reg ^= (1 << bit))
#define READ_BIT(reg, bit)  ((reg >> bit) & 1)

// ── Batas Ambang Pengukuran (Thresholds) ──────────────────────────────────
#define DROWSY_PITCH_MIN   25.0f
#define DROWSY_PITCH_MAX   60.0f
#define CRASH_ACCEL_G      2.5f
#define CRASH_GYRO_DPS     300.0f
#define BATTERY_LOW_PCT    20
#define BATTERY_MAX_V      4.2f
#define BATTERY_MIN_V      3.0f

#define SERIAL_INTERVAL_MS   200
#define DROWSY_CONFIRM_MS    1500
#define ALERT_DURATION_MS    3000
#define PANIC_DEBOUNCE_MS    300

// ── Modul Font ASCII 5x7 untuk OLED Render ────────────────────────────────
const uint8_t font5x7[][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, // Spasi (0x20)
    {0x00, 0x00, 0x5f, 0x00, 0x00}, // !
    {0x00, 0x07, 0x00, 0x07, 0x00}, // "
    {0x14, 0x7f, 0x14, 0x7f, 0x14}, // #
    {0x24, 0x2a, 0x7f, 0x2a, 0x12}, // $
    {0x23, 0x13, 0x08, 0x64, 0x62}, // %
    {0x36, 0x49, 0x55, 0x22, 0x50}, // &
    {0x00, 0x05, 0x03, 0x00, 0x00}, // '
    {0x00, 0x1c, 0x22, 0x41, 0x00}, // (
    {0x00, 0x41, 0x22, 0x1c, 0x00}, // )
    {0x14, 0x08, 0x3e, 0x08, 0x14}, // *
    {0x08, 0x08, 0x3e, 0x08, 0x08}, // +
    {0x00, 0x50, 0x30, 0x00, 0x00}, // ,
    {0x08, 0x08, 0x08, 0x08, 0x08}, // -
    {0x00, 0x60, 0x60, 0x00, 0x00}, // .
    {0x20, 0x10, 0x08, 0x04, 0x02}, // /
    {0x3e, 0x51, 0x49, 0x45, 0x3e}, // 0
    {0x00, 0x42, 0x7f, 0x40, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x21, 0x41, 0x45, 0x4b, 0x31}, // 3
    {0x18, 0x14, 0x12, 0x7f, 0x10}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x3c, 0x4a, 0x49, 0x49, 0x30}, // 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1e}, // 9
    {0x00, 0x36, 0x36, 0x00, 0x00}, // :
    {0x00, 0x56, 0x36, 0x00, 0x00}, // ;
    {0x08, 0x14, 0x22, 0x41, 0x00}, // <
    {0x14, 0x14, 0x14, 0x14, 0x14}, // =
    {0x00, 0x41, 0x22, 0x14, 0x08}, // >
    {0x02, 0x01, 0x51, 0x09, 0x06}, // ?
    {0x32, 0x49, 0x79, 0x41, 0x3e}, // @
    {0x7e, 0x11, 0x11, 0x11, 0x7e}, // A
    {0x7f, 0x49, 0x49, 0x49, 0x36}, // B
    {0x3e, 0x41, 0x41, 0x41, 0x22}, // C
    {0x7f, 0x41, 0x41, 0x22, 0x1c}, // D
    {0x7f, 0x49, 0x49, 0x49, 0x41}, // E
    {0x7f, 0x09, 0x09, 0x09, 0x01}, // F
    {0x3e, 0x41, 0x49, 0x49, 0x7a}, // G
    {0x7f, 0x08, 0x08, 0x08, 0x7f}, // H
    {0x00, 0x41, 0x7f, 0x41, 0x00}, // I
    {0x20, 0x40, 0x41, 0x3f, 0x01}, // J
    {0x7f, 0x08, 0x14, 0x22, 0x41}, // K
    {0x7f, 0x40, 0x40, 0x40, 0x40}, // L
    {0x7f, 0x02, 0x0c, 0x02, 0x7f}, // M
    {0x7f, 0x04, 0x08, 0x10, 0x7f}, // N
    {0x3e, 0x41, 0x41, 0x41, 0x3e}, // O
    {0x7f, 0x09, 0x09, 0x09, 0x06}, // P
    {0x3e, 0x41, 0x51, 0x21, 0x5e}, // Q
    {0x7f, 0x09, 0x19, 0x29, 0x46}, // R
    {0x46, 0x49, 0x49, 0x49, 0x31}, // S
    {0x01, 0x01, 0x7f, 0x01, 0x01}, // T
    {0x3f, 0x40, 0x40, 0x40, 0x3f}, // U
    {0x1f, 0x20, 0x40, 0x20, 0x1f}, // V
    {0x3f, 0x40, 0x38, 0x40, 0x3f}, // W
    {0x63, 0x14, 0x08, 0x14, 0x63}, // X
    {0x07, 0x08, 0x70, 0x08, 0x07}, // Y
    {0x61, 0x51, 0x49, 0x45, 0x43}  // Z
};

// ── State System ──────────────────────────────────────────────────────────
typedef enum {
    STATE_OK,
    STATE_DROWSY,
    STATE_CRASH,
    STATE_PANIC
} SystemState;

SystemState sysState       = STATE_OK;
unsigned long drowsyStart  = 0;
unsigned long alertStart   = 0;
unsigned long lastSerial   = 0;
unsigned long lastPanic    = 0;
bool          alertActive  = false;
float         pitch = 0, roll = 0, accelG = 1.0f, gyroDPS = 0;
int           battPct      = 100;
float         battV        = 4.2f;

// ── Penanganan Waktu internal (Millis via Timer 0) ────────────────────────
volatile unsigned long timer0_millis = 0;
ISR(TIMER0_OVF_vect) {
    static unsigned char fraction = 0;
    timer0_millis += 1;
    fraction += 24;
    if (fraction >= 100) {
        fraction -= 100;
        timer0_millis += 1;
    }
}

unsigned long millis() {
    unsigned long m;
    uint8_t oldSREG = SREG;
    cli();
    m = timer0_millis;
    SREG = oldSREG;
    return m;
}

void init_millis() {
    TCCR0B |= (1 << CS01) | (1 << CS00); 
    TIMSK0 |= (1 << TOIE0);              
}

// ── UART0 Driver (Komunikasi JSON) ────────────────────────────────────────
void uart_init(unsigned long baud) {
    unsigned int ubrr = F_CPU / 16 / baud - 1;
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << TXEN0); 
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_print_char(char c) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

void uart_print(const char* s) {
    while (*s) uart_print_char(*s++);
}

void uart_print_float(float val, uint8_t decimals) {
    if (val < 0) {
        uart_print_char('-');
        val = -val;
    }
    unsigned long int_part = (unsigned long)val;
    char buf[16];
    ltoa(int_part, buf, 10);
    uart_print(buf);
    if (decimals > 0) {
        uart_print_char('.');
        float frac_part = val - (float)int_part;
        for (uint8_t i = 0; i < decimals; i++) {
            frac_part *= 10.0f;
            uint8_t digit = (uint8_t)frac_part;
            uart_print_char('0' + digit);
            frac_part -= digit;
        }
    }
}

// ── I2C (TWI) Driver dengan Fail-Safe Timeout ─────────────────────────────
void i2c_init() {
    TWSR = 0;  
    TWBR = 72; 
    TWCR = (1 << TWEN); 
}

bool i2c_start() {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    uint16_t timeout = 500;
    while (!(TWCR & (1 << TWINT)) && timeout) { timeout--; _delay_us(1); }
    return (timeout > 0);
}

void i2c_stop() {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    uint16_t timeout = 500;
    while((TWCR & (1 << TWSTO)) && timeout) { timeout--; _delay_us(1); }
}

bool i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    uint16_t timeout = 500;
    while (!(TWCR & (1 << TWINT)) && timeout--) { _delay_us(1); }
    return (timeout > 0);
}

uint8_t i2c_read_ack() {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    uint16_t timeout = 500;
    while (!(TWCR & (1 << TWINT)) && timeout--) { _delay_us(1); }
    return TWDR;
}

uint8_t i2c_read_nack() {
    TWCR = (1 << TWINT) | (1 << TWEN);
    uint16_t timeout = 500;
    while (!(TWCR & (1 << TWINT)) && timeout--) { _delay_us(1); }
    return TWDR;
}

// ── MPU6050 Driver ────────────────────────────────────────────────────────
#define MPU_ADDR 0x68
void mpu_write_reg(uint8_t reg, uint8_t val) {
    if (i2c_start()) {
        i2c_write((MPU_ADDR << 1) | 0);
        i2c_write(reg);
        i2c_write(val);
        i2c_stop();
    }
}

void mpu_init() {
    _delay_ms(20);
    mpu_write_reg(0x6B, 0x00); 
    _delay_ms(10);
    mpu_write_reg(0x1C, 0x08); 
    mpu_write_reg(0x1B, 0x08); 
}

void readIMU() {
    int16_t ax = 0, ay = 0, az = 16384, gx = 0, gy = 0, gz = 0;
    if (i2c_start()) {
        if(i2c_write((MPU_ADDR << 1) | 0)) {
            i2c_write(0x3B);
            i2c_stop();
            if (i2c_start()) {
                i2c_write((MPU_ADDR << 1) | 1);
                ax = (i2c_read_ack() << 8) | i2c_read_ack();
                ay = (i2c_read_ack() << 8) | i2c_read_ack();
                az = (i2c_read_ack() << 8) | i2c_read_ack();
                i2c_read_ack(); i2c_read_ack(); 
                gx = (i2c_read_ack() << 8) | i2c_read_ack();
                gy = (i2c_read_ack() << 8) | i2c_read_ack();
                gz = (i2c_read_ack() << 8) | i2c_read_nack();
                i2c_stop();
            }
        } else { i2c_stop(); }
    }
    float axG = ax / 16384.0f;
    float ayG = ay / 16384.0f;
    float azG = az / 16384.0f;

    pitch = fabs(atan2(-axG, sqrt(ayG * ayG + azG * azG)) * 180.0f / M_PI);
    roll  = atan2(ayG, azG) * 180.0f / M_PI;
    accelG  = sqrt(axG * axG + ayG * ayG + azG * azG);
    gyroDPS = sqrt((gx/131.0f)*(gx/131.0f) + (gy/131.0f)*(gy/131.0f) + (gz/131.0f)*(gz/131.0f));
}

// ── SSD1306 OLED GFX Engine Register-Level ────────────────────────────────
#define OLED_ADDR 0x3C
uint8_t oled_buffer[1024]; // 128x64 piksel lokal buffer RAM

void oled_command(uint8_t cmd) {
    if (i2c_start()) {
        i2c_write(OLED_ADDR << 1);
        i2c_write(0x00); 
        i2c_write(cmd);
        i2c_stop();
    }
}

void oled_init() {
    _delay_ms(20);
    oled_command(0xAE); // Turn off display
    oled_command(0x20); // Set Memory Addressing Mode
    oled_command(0x00); // Horizontal Addressing Mode
    
    // ── PERBAIKAN MIRRORING (Arah Simetri Orientasi Layar) ────────
    oled_command(0xA1); // Mengubah Segment Remap (0xA0=Terbalik, 0xA1=Normal)
    oled_command(0xC8); // Mengubah COM Output Scan (0xC0=Terbalik, 0xC8=Normal)
    // ──────────────────────────────────────────────────────────────
    
    oled_command(0x8D); // Enable charge pump
    oled_command(0x14); 
    oled_command(0xAF); // Turn on display
}

void oled_clear() {
    for (uint16_t i = 0; i < 1024; i++) oled_buffer[i] = 0;
}

void oled_display() {
    oled_command(0x21); // Column address
    oled_command(0);
    oled_command(127);
    oled_command(0x22); // Page address
    oled_command(0);
    oled_command(7);

    if (i2c_start()) {
        if(i2c_write(OLED_ADDR << 1)) {
            i2c_write(0x40); 
            for (uint16_t i = 0; i < 1024; i++) {
                i2c_write(oled_buffer[i]);
            }
        }
        i2c_stop();
    }
}

// Gambar satu pixel ke koordinat internal RAM buffer
void oled_draw_pixel(int x, int y, uint8_t color) {
    if (x < 0 || x >= 128 || y < 0 || y >= 64) return;
    if (color) {
        oled_buffer[x + (y / 8) * 128] |= (1 << (y % 8));
    } else {
        oled_buffer[x + (y / 8) * 128] &= ~(1 << (y % 8));
    }
}

void oled_draw_fast_hline(int x, int y, int w, uint8_t color) {
    for (int i = 0; i < w; i++) oled_draw_pixel(x + i, y, color);
}

void oled_draw_rect(int x, int y, int w, int h, uint8_t color) {
    for (int i = 0; i < w; i++) { oled_draw_pixel(x+i, y, color); oled_draw_pixel(x+i, y+h-1, color); }
    for (int i = 0; i < h; i++) { oled_draw_pixel(x, y+i, color); oled_draw_pixel(x+w-1, y+i, color); }
}

void oled_fill_rect(int x, int y, int w, int h, uint8_t color) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            oled_draw_pixel(x + i, y + j, color);
        }
    }
}

// Menulis satu karakter huruf berbasis data bitmap array font5x7
void oled_print_char(int x, int y, char c, uint8_t size, uint8_t color) {
    if (c < 32 || c > 122) return; 
    uint8_t idx = c - 32;
    for (uint8_t i = 0; i < 5; i++) {
        uint8_t line = font5x7[idx][i];
        for (uint8_t j = 0; j < 8; j++) {
            if (line & (1 << j)) {
                if (size == 1) {
                    oled_draw_pixel(x + i, y + j, color);
                } else {
                    oled_fill_rect(x + (i * size), y + (j * size), size, size, color);
                }
            }
        }
    }
}

void oled_print_str(int x, int y, const char* str, uint8_t size, uint8_t color) {
    while (*str) {
        oled_print_char(x, y, *str++, size, color);
        x += (6 * size);
        if (x > 122) break;
    }
}

// ── ADC Battery Driver ────────────────────────────────────────────────────
void adc_init() {
    ADMUX = (1 << REFS0); 
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
}

void readBattery() {
    ADCSRA |= (1 << ADSC);
    uint16_t timeout = 1000;
    while ((ADCSRA & (1 << ADSC)) && timeout--) { _delay_us(1); }
    int raw = ADC;
    battV   = 3.0f + ((float)raw / 1023.0f) * (BATTERY_MAX_V - BATTERY_MIN_V);
    battPct = (int)(((battV - BATTERY_MIN_V) / (BATTERY_MAX_V - BATTERY_MIN_V)) * 100);
    if (battPct < 0) battPct = 0;
    if (battPct > 100) battPct = 100;
}

// ── Buzzer Tone Driver via Timer 3 (Pin D3 / PE5) ─────────────────────────
void set_buzzer_freq(uint16_t freq) {
    if (freq == 0) {
        TCCR3A = 0; TCCR3B = 0;
        CLR_BIT(PORTE, 5);
        return;
    }
    TCCR3A = (1 << COM3C0); 
    TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS31); 
    ICR3 = F_CPU / (2 * 8 * freq) - 1;
}

// ── IO Hardware Setup ─────────────────────────────────────────────────────
void io_init() {
    SET_BIT(DDRH, 3); // D6 (RED LED) -> OUTPUT
    SET_BIT(DDRE, 3); // D5 (VIBRATOR) -> OUTPUT
    SET_BIT(DDRE, 5); // D3 (BUZZER) -> OUTPUT
    CLR_BIT(DDRE, 4); // D2 (PANIC BTN) -> INPUT
    SET_BIT(PORTE, 4); // Pull-up internal aktif
}

bool checkPanic() {
    if (READ_BIT(PINE, 4) == 0) { 
        unsigned long now = millis();
        if (now - lastPanic > PANIC_DEBOUNCE_MS) {
            lastPanic = now;
            return true;
        }
    }
    return false;
}

// ── State Machine & Logic Control ─────────────────────────────────────────
void updateState() {
    unsigned long now = millis();

    if (alertActive && (now - alertStart > ALERT_DURATION_MS)) {
        if (sysState == STATE_CRASH || sysState == STATE_PANIC) {
            sysState    = STATE_OK;
            alertActive = false;
        }
    }

    if (checkPanic()) {
        sysState    = STATE_PANIC;
        alertStart  = now;
        alertActive = true;
        return;
    }

    if (accelG > CRASH_ACCEL_G || gyroDPS > CRASH_GYRO_DPS) {
        sysState    = STATE_CRASH;
        alertStart  = now;
        alertActive = true;
        return;
    }

    if (sysState != STATE_CRASH && sysState != STATE_PANIC) {
        if (pitch > DROWSY_PITCH_MIN && pitch < DROWSY_PITCH_MAX) {
            if (drowsyStart == 0) drowsyStart = now; 
            if ((now - drowsyStart) > DROWSY_CONFIRM_MS) {
                sysState    = STATE_DROWSY;
                alertActive = true;
                alertStart  = now;
            }
        } else {
            drowsyStart = 0; 
            if (sysState == STATE_DROWSY) {
                sysState    = STATE_OK;
                alertActive = false;
            }
        }
    }
}

void driveOutputs() {
    unsigned long now = millis();
    bool buzz = false, vibe = false, redLed = false;

    switch (sysState) {
        case STATE_DROWSY:
            buzz   = (now % 1000) < 300;
            vibe   = buzz;
            redLed = true;
            break;
        case STATE_CRASH:
        case STATE_PANIC:
            buzz   = (now % 400) < 200;
            vibe   = true;
            redLed = (now % 200) < 100;
            break;
        default:
            if (battPct <= BATTERY_LOW_PCT) redLed = (now % 1000) < 150;
            break;
    }

    if (buzz) set_buzzer_freq((sysState == STATE_DROWSY) ? 880 : 1500);
    else set_buzzer_freq(0);

    if (vibe)   SET_BIT(PORTE, 3); else CLR_BIT(PORTE, 3); // D5
    if (redLed) SET_BIT(PORTH, 3); else CLR_BIT(PORTH, 3); // D6
}

// ── Rendering Layout OLED Sesuai Format Contoh Arduino Anda ─────────────────
void drawOLED() {
    oled_clear();
    
    // Header teks Utama
    oled_print_str(0, 0, "SAFERIDE", 1, 1);

    // Desain Baterai Bar (Sebelah Kanan Atas)
    int bx = 90, by = 0;
    oled_draw_rect(bx, by, 30, 10, 1);
    oled_draw_pixel(bx + 30, by + 3, 1);
    oled_draw_pixel(bx + 30, by + 4, 1);
    oled_draw_pixel(bx + 30, by + 5, 1);
    oled_draw_pixel(bx + 30, by + 6, 1);
    
    int fill = (battPct * 28) / 100;
    if (fill > 0) oled_fill_rect(bx + 1, by + 1, fill, 8, 1);

    if (battPct <= BATTERY_LOW_PCT) {
        oled_fill_rect(bx, by, 30, 10, 1);
        oled_print_str(bx + 3, by + 1, "LOW!", 1, 0); // Teks Hitam di dalam kotak putih
    }

    // Garis Pemisah Horizontal
    oled_draw_fast_hline(0, 13, 128, 1);

    // State Kondisi Pengendara
    switch (sysState) {
        case STATE_DROWSY: {
            bool blink = (millis() % 600) < 300;
            if (blink) {
                oled_fill_rect(0, 16, 128, 22, 1);
                oled_print_str(10, 20, "MENGANTUK", 2, 0); // Text besar invers hitam
            }
            char pStr[16];
            // Menambahkan simbol derajat menggunakan ASCII alternatif 247
            sprintf(pStr, "PITCH: %d%c", (int)pitch, 247);
            oled_print_str(0, 44, pStr, 1, 1);
            oled_print_str(0, 54, "PERINGATAN: FOKUS!", 1, 1);
            break;
        }
        case STATE_CRASH: {
            oled_print_str(10, 18, "!! CRASH", 2, 1);
            oled_print_str(10, 35, "DETEKSI!", 2, 1);
            char gStr[32];
            sprintf(gStr, "G: %d.%d DPS: %d", (int)accelG, ((int)(accelG*10))%10, (int)gyroDPS);
            oled_print_str(0, 54, gStr, 1, 1);
            break;
        }
        case STATE_PANIC: {
            oled_print_str(14, 18, "!! SOS !!", 2, 1);
            oled_print_str(18, 42, "KONDISI DARURAT", 1, 1);
            oled_print_str(22, 53, "SINYAL DIKIRIM", 1, 1);
            break;
        }
        default: { // STATE_OK (Aman)
            oled_print_str(0, 17, "STATUS: AMAN", 1, 1);
            char line2[32], line3[32], line4[32];
            // Menambahkan simbol derajat %c (247) untuk pitch dan roll
            sprintf(line2, "PITCH: %d%c  ROLL: %d%c", (int)pitch, 247, (int)roll, 247);
            sprintf(line3, "ACCEL: %d.%d G", (int)accelG, ((int)(accelG*100))%100);
            sprintf(line4, "GYRO:  %d DPS", (int)gyroDPS);
            oled_print_str(0, 29, line2, 1, 1);
            oled_print_str(0, 41, line3, 1, 1);
            oled_print_str(0, 53, line4, 1, 1);
            break;
        }
    }
    oled_display();
}

void sendSerial() {
    const char* stateStr;
    switch (sysState) {
        case STATE_DROWSY: stateStr = "DROWSY";  break;
        case STATE_CRASH:  stateStr = "CRASH";   break;
        case STATE_PANIC:  stateStr = "PANIC";   break;
        default:           stateStr = "OK";      break;
    }

    uart_print("{\"state\":\"");
    uart_print(stateStr);
    uart_print("\",\"pitch\":");
    uart_print_float(pitch, 2);
    uart_print(",\"roll\":");
    uart_print_float(roll, 2);
    uart_print(",\"accelG\":");
    uart_print_float(accelG, 3);
    uart_print(",\"gyroDPS\":");
    uart_print_float(gyroDPS, 1);
    uart_print(",\"battPct\":");
    char bPctBuf[5];
    itoa(battPct, bPctBuf, 10);
    uart_print(bPctBuf);
    uart_print(",\"battV\":");
    uart_print_float(battV, 2);
    uart_print(",\"ts\":");
    char tsBuf[16];
    ltoa(millis(), tsBuf, 10);
    uart_print(tsBuf);
    uart_print("}\r\n");
}

int main(void) {
    io_init();
    init_millis();
    uart_init(115200);
    
    i2c_init(); 
    mpu_init();
    adc_init();
    oled_init();
    
    sei(); 

    // Tampilan Booting Awal (SafeRide Memuat Sensor...)
    oled_clear();
    oled_print_str(18, 10, "SAFERIDE", 2, 1);
    oled_print_str(16, 34, "HELM PINTAR V1.0", 1, 1);
    oled_print_str(14, 48, "MEMUAT SENSOR...", 1, 1);
    oled_display();
    _delay_ms(2000);

    while (1) {
        readBattery();
        readIMU();
        updateState();
        driveOutputs();
        drawOLED();

        unsigned long now = millis();
        if (now - lastSerial >= SERIAL_INTERVAL_MS) {
            lastSerial = now;
            sendSerial();
        }
    }
    return 0;
}
