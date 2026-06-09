import asyncio
import websockets
import serial
import json

# === KONFIGURASI KONEKSI KE WOKWI ===
# Kita tidak pakai COM Port lagi, melainkan tembak langsung ke TCP Wokwi
WOKWI_URL = 'rfc2217://localhost:4001'

try:
    # Membaca serial dari TCP socket (RFC2217)
    ser = serial.serial_for_url(WOKWI_URL, baudrate=115200, timeout=1)
    print(f"Berhasil terhubung ke Wokwi di {WOKWI_URL}")
except Exception as e:
    print(f"Gagal terhubung ke Wokwi: {e}")
    print("Pastikan simulasi Wokwi di VS Code sudah berjalan!")
    exit()

async def serial_to_websocket(websocket):
    while True:
        try:
            # Gunakan in_waiting untuk mengecek apakah ada data
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').strip()
                # Cek jika data berformat JSON
                if line.startswith("{") and line.endswith("}"):
                    print(f"Data Wokwi -> HTML: {line}")
                    await websocket.send(line)
        except Exception as e:
            pass
            
        await asyncio.sleep(0.05)

async def main():
    async with websockets.serve(serial_to_websocket, "localhost", 8080):
        print("WebSocket Server berjalan... Silakan buka file HTML Anda.")
        await asyncio.Future()

if __name__ == "__main__":
    asyncio.run(main())
