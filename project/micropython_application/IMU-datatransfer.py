import time
import network
import socket
from machine import I2C
from micropython_bmi270 import bmi270

# ---------------- config ----------------
SSID = "ssid"
PASSWORD = "pwd"
PORT = 5000

# ---------------- functions ----------------
def wait_for_client(server_socket):
    print("\n[Server] Warte auf Verbindung...")
    # Akzeptiert die Verbindung
    client, addr = server_socket.accept()
    print("[Server] Client verbunden:", addr)
    return client

# ---------------- wifi connection ----------------
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(SSID, PASSWORD)

print("Connect with WIFI...")
while not wlan.isconnected():
    time.sleep(1)

ip = wlan.ifconfig()[0]
print("Connected! IP:", ip)

# ---------------- TCP server connection ----------------
addr = socket.getaddrinfo("0.0.0.0", PORT)[0][-1]
server = socket.socket()
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(addr)
server.listen(1)

print("TCP server ist runnuig on port", PORT)
print("Host-IP for client:", ip)

# ---------------- IMU init ----------------
i2c = I2C(scl='P0_2', sda='P0_3')
bmi = bmi270.BMI270(i2c)


# ---------------- main ----------------
client = wait_for_client(server)

while True:
    try:
        accx, accy, accz = bmi.acceleration
        msg = f"{accx:.2f},{accy:.2f},{accz:.2f}\r\n"
        print(msg)
        client.write(msg)
        time.sleep(0.02)

    except Exception as e:
        print("Reconnect:", e)
        client = wait_for_client(server)