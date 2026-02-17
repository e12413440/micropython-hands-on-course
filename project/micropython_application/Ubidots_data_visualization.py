#Import
import machine
from machine import Pin,ADC             # module to talk to IO pins
import time                             # module for delays
import network                          # module for networking tasks
from umqtt.robust import MQTTClient     # module for MQTT protocol
import ujson                            # module to generate JSON string
 
# ---------------- CONFIG ----------------
SSID = "A1-AA84C8"
PASSWORD = "53146397712608154730"
PORT = 5000


def wait_for_client(server_socket):
    """Wartet auf eine neue TCP-Verbindung und gibt das Client-Objekt zurück."""
    print("\n[Server] Warte auf Verbindung...")
    # Akzeptiert die Verbindung
    client, addr = server_socket.accept()
    print("[Server] Client verbunden:", addr)
    return client

# ---------------- WIFI connect ----------------
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(SSID, PASSWORD)

print("Verbinde mit WIFI...")
while not wlan.isconnected():
    time.sleep(1)

ip = wlan.ifconfig()[0]
print("Verbunden! IP:", ip)
 
# ---------------- MQTT Setup ----------------
SERVER="industrial.api.ubidots.com"
port=1883
client='boxtrainer_transmitter'
topic=b"/v1.6/devices/PSOC6-Boxer"
ubidotsToken = 'BBUS-oCJ5n25UsXMlFIJjfcyEeQyefjg0Oi'

# ---------------- Client Object ----------------
client = MQTTClient("client", "industrial.api.ubidots.com", 1883, user = ubidotsToken, password = ubidotsToken)

client = MQTTClient("boxtrainer_transmitter", SERVER, port, user=ubidotsToken, password=ubidotsToken, keepalive=60)

def connect_to_ubidots():
    try:
        client.connect()
        print("Erfolgreich dauerhaft verbunden.")
        return True
    except Exception as e:
        print("Verbindungsfehler:", e)
        return False

if connect_to_ubidots():
    punch = 0
    punch_names = ["Jab", "Hook", "Uppercut"]
    
    while True:
        session_id = 1
        current_name = punch_names[punch]
        session_name = "Training_1"
        
        payload = {
            "punchtype": {
                "value": punch,
                "context": {"punchtype_ctxt": current_name}
            },
            "session": {
                "value": session_id,  # Komma korrigiert
                "context": {"session_ctxt": session_name}
            }
        }
        
        msg = ujson.dumps(payload)
        
        try:
            client.publish(topic, msg)
            print(f"Sende (0.5s): {current_name}")
        except Exception as e:
            print("Verbindung verloren, versuche Reconnect...")
            connect_to_ubidots()
        
        punch = (punch + 1) % 3
        
        # 0.5 Sekunden Pause
        time.sleep(0.5)
