import time
import network
import socket
from machine import I2C
from micropython_bmi270 import bmi270
import sys
import array
import deepcraft_model_05_2 as m


# ---------------- config ----------------
SSID = ""
PASSWORD = ""

PORT = 5000

IMU_INTERVAL = 10000

model = m.DEEPCRAFT()
model.init()



# ---------------- functions ----------------
def wait_for_client(server_socket):
    print("\n[Server] Warte auf Verbindung...")
    # Akzeptiert die Verbindung
    client, addr = server_socket.accept()
    print("[Server] Client verbunden:", addr)
    return client


def get_punch_data():
    acc_x, acc_y, acc_z = bmi.acceleration
    gyro_x, gyro_y, gyro_z = bmi.gyro
    
    sample = array.array('f', [acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z])
    model.enqueue(sample)
    
    out_dim = model.get_model_output_dim()
    probs = array.array('f', [0.0] * out_dim)
    model.dequeue(probs)

    punch_types = ["Unlabeled", "Jab", "Side Hook", "Uppercut"]
    prob_max = max(probs)
    
    # Standardmäßig "Nichts gefunden" zurückgeben
    p_id, p_type = None, None

    if prob_max >= 0.6:
        # Index manuell finden (da array kein .index hat)
        idx = 0
        for i in range(len(probs)):
            if probs[i] == prob_max:
                idx = i
                break
        
        # Nur wenn es nicht "Unlabeled" (Index 0) ist, Daten füllen
        if idx > 0:
            p_id = idx
            p_type = punch_types[idx]

    return p_id, p_type  # Hier werden IMMER zwei Werte zurückgegeben

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

# Initialisierung der Zeitstempel
last_imu_read_time = time.ticks_us()

while True:
    try:
        # 1. Aktuelle Zeit in der Schleife IMMER aktualisieren
        current_time = time.ticks_us()
        
        # 2. Variablen vorab mit None initialisieren, damit sie "bekannt" sind
        p_id, p_type = None, None

        
        p_id, p_type = get_punch_data()
        last_imu_read_time = current_time # Zeitstempel zurücksetzen

        # 4. Jetzt existiert p_id immer (entweder als Wert oder als None)
        if p_id is not None:
            msg = f"{p_id},{p_type}\r\n"
            print("Detected:", msg.strip())
            client.write(msg.encode())
            
        # Kleiner Sleep, um die CPU nicht zu 100% auszulasten
        time.sleep_ms(7)

    except Exception as e:
        print("Fehler aufgetreten:", e)
        client.close()
        client = wait_for_client(server)
        last_imu_read_time = time.ticks_us() # Zeit nach Reconnect resetten