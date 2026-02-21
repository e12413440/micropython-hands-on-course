import time
import network
import socket
import machine
from machine import I2C
from micropython_bmi270 import bmi270
import array
import json
import deepcraft_model_05_2 as m
import gc

# ---------------- config ----------------
SSID = "A1-E6303791"
PASSWORD = "uTv9yRngHF1N2V"
PORT = 80

latest_punch = {"id": 0, "type": "Bereit...", "timestamp": 0}

model = m.DEEPCRAFT()
model.init()

# HTML in Fragmente unterteilen spart RAM beim Formatieren
HTML_PART1 = """<!DOCTYPE html><html><head><meta charset="utf-8"><title>Boxing AI</title>
<style>body {{ font-family: sans-serif; text-align: center; background: #121212; color: white; }}
.box {{ border: 2px solid #333; padding: 20px; margin: 20px auto; width: 80%; border-radius: 15px; }}
#punch {{ font-size: 3em; font-weight: bold; color: #00ff00; }}</style></head>
<body><h1>Punch Detector</h1><div class="box"><div id="punch">Warten...</div></div>
<p>IP: {ip}</p><script>
async function update() {{
  try {{ const r = await fetch('/data'); const d = await r.json(); 
  if(d.id !== 0) document.getElementById('punch').innerText = d.type;
  }} catch(e) {{}}
}} setInterval(update, 200);</script></body></html>"""

# ---------------- IMU & KI ----------------
i2c = I2C(scl='P0_2', sda='P0_3') # Prüfe ob diese Pins auf deinem Board stimmen!
bmi = bmi270.BMI270(i2c)

def get_punch_data():
    try:
        acc = bmi.acceleration
        gyro = bmi.gyro
        sample = array.array('f', [acc[0], acc[1], acc[2], gyro[0], gyro[1], gyro[2]])
        model.enqueue(sample)
        
        out_dim = model.get_model_output_dim()
        probs = array.array('f', [0.0] * out_dim)
        model.dequeue(probs)

        p_types = ["Unlabeled", "Jab", "Side Hook", "Uppercut"]
        p_max = max(probs)
        
        if p_max >= 0.6:
            for i, p in enumerate(probs):
                if p == p_max and i > 0: return i, p_types[i]
    except: pass
    return None, None

# ---------------- WiFi ----------------
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(SSID, PASSWORD)
while not wlan.isconnected(): time.sleep(1)
ip = wlan.ifconfig()[0]
print("Online:", ip)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('0.0.0.0', PORT))
server.listen(1) # Nur 1 Verbindung gleichzeitig für Stabilität
server.setblocking(False)

last_heartbeat = time.ticks_ms()

# ---------------- Main Loop ----------------
while True:
    gc.collect() # Aggressives Aufräumen
    
    # 1. KI-Abfrage
    p_id, p_type = get_punch_data()
    if p_id:
        latest_punch = {"id": p_id, "type": p_type, "timestamp": time.ticks_ms()}
        print("Punch:", p_type)

    # 2. Webserver (Minimal-Logik)
    try:
        conn, addr = server.accept()
        try:
            conn.settimeout(0.2)
            raw_request = conn.recv(512)
            request = raw_request.decode().split('\r\n')[0]
            
            if 'GET /data' in request:
                conn.send('HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n')
                conn.send(json.dumps(latest_punch))
            else:
                conn.send('HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n')
                conn.send(HTML_PART1.format(ip=ip))
        except Exception as e:
            print("Request Error:", e)
        finally:
            conn.close()
    except OSError: # Kein Client da
        pass

    time.sleep_ms(10)