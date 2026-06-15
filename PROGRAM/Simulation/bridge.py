import asyncio
import serial
import serial.rfc2217  
import json
import websockets

SERIAL_PORT = 'rfc2217://127.0.0.1:4000' 
BAUD_RATE = 115200
WS_HOST = "localhost"
WS_PORT = 8765 

connected_clients = set()

async def register(websocket):
    connected_clients.add(websocket)
    print(f"Client terhubung: {websocket.remote_address}")
    try:
        await websocket.wait_closed()
    finally:
        connected_clients.remove(websocket)
        print(f"Client terputus: {websocket.remote_address}")

async def broadcast(message):
    if connected_clients:
        await asyncio.gather(*[client.send(message) for client in connected_clients])

def read_serial_data(ser):
    if ser.in_waiting > 0:
        try:
            line = ser.readline().decode('utf-8').strip()
            if line.startswith('{') and line.endswith('}'):
                return line
        except Exception as e:
            print(f"Error membaca serial: {e}")
    return None

async def serial_bridge():
    print(f"Membuka jaringan RFC2217 di {SERIAL_PORT}...")
    try:
        ser = serial.rfc2217.Serial(SERIAL_PORT, baudrate=BAUD_RATE, timeout=0.1)
    except Exception as e:
        print(f"Gagal membuka port {SERIAL_PORT}. Pastikan Wokwi sedang RUNNING. Error: {e}")
        return
    print("Bridge aktif! Menunggu data dari Wokwi...")
    try:
        while True:
            print(f"in_waiting={ser.in_waiting}", end='\r')
            loop = asyncio.get_event_loop()
            data = await loop.run_in_executor(None, read_serial_data, ser)
            
            if data:
                print(f"\nData Masuk -> {data}")
                await broadcast(data)
                
            await asyncio.sleep(0.05) 
    except asyncio.CancelledError:
        pass
    finally:
        ser.close()
        print("Koneksi serial ditutup.")

async def main():
    server = await websockets.serve(register, WS_HOST, WS_PORT)
    print(f"WebSocket Server berjalan di ws://{WS_HOST}:{WS_PORT}")
    await serial_bridge()
    await server.wait_closed()

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\nBridge dihentikan oleh pengguna.")
