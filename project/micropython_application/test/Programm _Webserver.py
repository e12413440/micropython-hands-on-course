import time
import network
import socket
import machine
from machine import I2C
from micropython_bmi270 import bmi270
import array
import deepcraft_model_05_2 as m
import gc

# --- WLAN Daten ---
SSID = "A1-E6303791"
PASSWORD = "uTv9yRngHF1N2V"

# Statistik
stats = [0, 0, 0, 0] # Jab, Hook, Upper, Total
last_type = "Bereit"

# KI & Sensor Setup
model = m.DEEPCRAFT()
model.init()
i2c = I2C(scl='P0_2', sda='P0_3', freq=400000)
bmi = bmi270.BMI270(i2c)

# --- Netzwerk-Start ---
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(SSID, PASSWORD)

print("Connecting...")
while not wlan.isconnected():
    time.sleep(0.5)

ip = wlan.ifconfig()[0]
print("Server IP:", ip)

# Socket Setup
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(('0.0.0.0', 80))
s.listen(1)
s.setblocking(False)

# Vorbereitetes Byte-Array für die Antwort (spart RAM-Allokation im Loop)
HTTP_OK = b"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
DATA_OK = b"HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n"

# --- Main Loop ---
while True:
    gc.collect()
    
    # 1. KI Teil
    try:
        acc = bmi.acceleration
        gyro = bmi.gyro
        model.enqueue(array.array('f', [acc[0], acc[1], acc[2], gyro[0], gyro[1], gyro[2]]))
        
        probs = array.array('f', [0.0] * 4)
        model.dequeue(probs)
        
        mx = max(probs)
        if mx >= 0.6:
            idx = 0
            for i in range(4):
                if probs[i] == mx: idx = i
            if idx > 0:
                stats[idx-1] += 1
                stats[3] += 1
                last_type = ["Jab", "Hook", "Upper"][idx-1]
                print("Detektiert:", last_type)
    except:
        pass

    # 2. Webserver Teil (Ultraschlank)
    try:
        res = s.accept()
        if res:
            client, addr = res
            try:
                client.settimeout(0.1)
                req = client.recv(128) # Sehr kleiner Buffer
                
                if b"/d" in req: # AJAX Datenanfrage
                    client.send(DATA_OK)
                    # Manuelle JSON-Erstellung spart 'json'-Modul RAM
                    json_str = '{"l":"%s","j":%d,"h":%d,"u":%d,"t":%d}' % (last_type, stats[0], stats[1], stats[2], stats[3])
                    client.send(json_str.encode())
                else: # HTML Seite
                    client.send(HTTP_OK)
                    client.send(b"<html><body style='background:#121212;color:white;font-family:sans-serif;text-align:center'>")
                    client.send(b"<h1>Boxing AI</h1><h2 id='l'>--</h2>")
                    client.send(b"<p>Jab: <span id='j'>0</span> | Hook: <span id='h'>0</span> | Upper: <span id='u'>0</span></p>")
                    client.send(b"<script>setInterval(async()=>{let r=await fetch('/d');let d=await r.json();")
                    client.send(b"document.getElementById('l').innerText=d.l;document.getElementById('j').innerText=d.j;")
                    client.send(b"document.getElementById('h').innerText=d.h;document.getElementById('u').innerText=d.u;},500);")
                    client.send(b"</script></body></html>")
            except:
                pass
            finally:
                client.close()
    except OSError:
        pass

    time.sleep_ms(5)