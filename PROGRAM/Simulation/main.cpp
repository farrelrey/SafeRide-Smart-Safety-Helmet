#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// ================= PENGATURAN PIN =================
#define BTN_SOS_PIN      2   
#define BUZZER_PIN       3   
#define VIBE_LED_PIN     5  
#define STATUS_LED_PIN   6   
#define BATTERY_PIN      A0  

// ================= PENGATURAN OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_MPU6050 mpu;

// ================= VARIABEL =================
volatile bool sosActive = false; 
unsigned long lastUpdate = 0;
unsigned long lastSerialUpdate = 0; // Variabel untuk delay pengiriman Python
int batPercentage = 100;

// ---> DEKLARASI FUNGSI (Memperbaiki error 'was not declared') <---
void updateOLED(String baris1, String baris2); 

// Interrupt Tombol SOS
void triggerSOS() {
  sosActive = true; 
}

void setup() {
  Serial.begin(115200);

  pinMode(BTN_SOS_PIN, INPUT_PULLUP); 
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(VIBE_LED_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BTN_SOS_PIN), triggerSOS, FALLING);

  // Inisialisasi OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED gagal!"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.print("Sistem Booting...");
  display.display();
  delay(1000);

  // Inisialisasi MPU6050
  if (!mpu.begin()) {
    Serial.println("MPU6050 gagal!");
    while (1) { delay(10); }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  Serial.println("Sistem Saferide Siap!");
}

void loop() {
  // 1. Baca Baterai
  int batRaw = analogRead(BATTERY_PIN);
  batPercentage = map(batRaw, 0, 1023, 0, 100);

  // 2. Baca MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Hitung Gaya G Total (m/s^2)
  float accelMagnitude = sqrt(pow(a.acceleration.x, 2) + 
                              pow(a.acceleration.y, 2) + 
                              pow(a.acceleration.z, 2));

  // ---> KONVERSI KE G-FORCE <---
  float gForce = accelMagnitude / 9.81; 

  // BATAS DITURUNKAN KE 15.0 agar bisa dites di slider Wokwi
  bool crashDetected = (accelMagnitude > 15.0);

  // 3. LOGIKA KONDISI
  if (sosActive) {
    analogWrite(STATUS_LED_PIN, 255);
    analogWrite(VIBE_LED_PIN, 255); 
    
    updateOLED("=== DARURAT SOS ===", "Bantuan Dibutuhkan!");
    
    tone(BUZZER_PIN, 1000);
    delay(200);
    noTone(BUZZER_PIN);
    delay(200);

    if (Serial.available()) {
      char c = Serial.read();
      if (c == 'R' || c == 'r') {
        sosActive = false;
        noTone(BUZZER_PIN);
        analogWrite(VIBE_LED_PIN, 0);
        analogWrite(STATUS_LED_PIN, 0); 
        Serial.println("Sistem Di-reset ke Normal.");
      }
    }

  } else if (crashDetected) {
    analogWrite(STATUS_LED_PIN, 200);
    analogWrite(VIBE_LED_PIN, 200); 
    
    updateOLED("!! PERINGATAN !!", "Benturan Terdeteksi");
    
    tone(BUZZER_PIN, 2000);
    delay(200);
    noTone(BUZZER_PIN);
    delay(100);

  } else {
    noTone(BUZZER_PIN);
    analogWrite(VIBE_LED_PIN, 0);
    analogWrite(STATUS_LED_PIN, 0); 
    
    if (millis() - lastUpdate > 200) {
      // Menampilkan G-Force juga di OLED fisik jika diinginkan
      String statusMsg = "G: " + String(gForce, 2) + " G";
      updateOLED("Sistem Normal", statusMsg);
      lastUpdate = millis();
    }
  }

  // --- 4. KIRIM DATA KE PYTHON (Format JSON) ---
  if (millis() - lastSerialUpdate > 500) {
    // Hitung G-Force dulu
    float gForce = accelMagnitude / 9.81; 

    Serial.print("{\"battery\":"); 
    Serial.print(batPercentage);
    Serial.print(", \"sos\":"); 
    Serial.print(sosActive ? "true" : "false");
    Serial.print(", \"crash\":"); 
    Serial.print(crashDetected ? "true" : "false");
    Serial.print(", \"gforce\":");  // --> INI YANG BIKIN HTML BISA BACA
    Serial.print(gForce, 2);         
    Serial.println("}");
    
    lastSerialUpdate = millis();
  }
}

// Fungsi cetak ke OLED
void updateOLED(String baris1, String baris2) {
  display.clearDisplay();
  display.setCursor(0, 10);
  display.println(baris1);
  display.setCursor(0, 30); 
  display.println(baris2);
  display.display();
}
