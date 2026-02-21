# ============================================================
# IMPORTS
# ============================================================
import time
import network
import socket
from machine import I2C
from micropython_bmi270 import bmi270
import array
import deepcraft_model_07_2 as m
from umqtt.robust import MQTTClient
import ujson


# ============================================================
# CONFIGURATION
# ============================================================

# WiFi credentials
SSID = "A1-E6303791"
PASSWORD = "uTv9yRngHF1N2V"


# MQTT / Ubidots configuration
MQTT_SERVER = "industrial.api.ubidots.com"
MQTT_PORT = 1883
MQTT_CLIENT_ID = "boxtrainer_transmitter"
MQTT_TOPIC = b"/v1.6/devices/PSOC6-Boxer"
UBIDOTS_TOKEN = "BBUS-oCJ5n25UsXMlFIJjfcyEeQyefjg0Oi"

# IMU read interval (microseconds)
IMU_INTERVAL_US = 10000

# Punch labels (index must match model output)
PUNCH_LABELS = ["Unlabeled", "Jab", "Hook", "Uppercut"]

# Session information
SESSION_ID = 1
SESSION_NAME = "Training_1"


# ============================================================
# INITIALIZE AI MODEL
# ============================================================

# Create model instance and initialize it
model = m.DEEPCRAFT()
model.init()


# ============================================================
# WIFI CONNECTION FUNCTION
# ============================================================

def connect_wifi():
    """
    Connect to WiFi network.
    Blocks until connection is established.
    """

    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(SSID, PASSWORD)

    print("Connecting to WiFi...")

    while not wlan.isconnected():
        time.sleep(1)

    ip = wlan.ifconfig()[0]

    print("WiFi connected")
    print("IP address:", ip)

    return ip




# ============================================================
# MQTT FUNCTIONS
# ============================================================

# Create MQTT client instance
mqtt_client = MQTTClient(
    MQTT_CLIENT_ID,
    MQTT_SERVER,
    MQTT_PORT,
    user=UBIDOTS_TOKEN,
    password=UBIDOTS_TOKEN
)


def connect_mqtt():
    """
    Connect to MQTT broker.
    Returns True if successful.
    """

    try:
        mqtt_client.connect()
        print("MQTT connected")
        return True

    except Exception as e:
        print("MQTT connection failed:", e)
        return False


def publish_punch(punch_id, punch_name):
    """
    Publish punch data to Ubidots using MQTT.
    """

    payload = {
        "punchtype": {
            "value": punch_id,
            "context": {
                "punchtype_ctxt": punch_name
            }
        },
        "session": {
            "value": SESSION_ID,
            "context": {
                "session_ctxt": SESSION_NAME
            }
        }
    }

    msg = ujson.dumps(payload)

    try:

        mqtt_client.publish(MQTT_TOPIC, msg)

        print("Published:", punch_name)

    except Exception as e:

        print("MQTT publish failed:", e)

        # try reconnect
        connect_mqtt()


# ============================================================
# IMU AND MODEL PROCESSING FUNCTION
# ============================================================

def get_punch_data():
    """
    Read IMU data, run AI model inference,
    and return detected punch id and punch name.

    Returns:
        punch_id (int or None)
        punch_name (str or None)
    """

    # Read acceleration
    acc_x, acc_y, acc_z = bmi.acceleration

    # Read gyroscope
    gyro_x, gyro_y, gyro_z = bmi.gyro

    # Create input sample for model
    sample = array.array('f', [
        acc_x,
        acc_y,
        acc_z,
        gyro_x,
        gyro_y,
        gyro_z
    ])

    # Push sample into model input queue
    model.enqueue(sample)

    # Prepare output buffer
    output_dim = model.get_model_output_dim()

    probs = array.array('f', [0.0] * output_dim)

    # Read inference result
    model.dequeue(probs)

    # Find maximum probability
    max_prob = 0.0
    max_index = 0

    for i in range(len(probs)):

        if probs[i] > max_prob:

            max_prob = probs[i]
            max_index = i

    # Apply detection threshold
    if max_prob >= 0.6 and max_index > 0:

        return max_index, PUNCH_LABELS[max_index]

    return None, None


# ============================================================
# INITIALIZE WIFI
# ============================================================

ip_address = connect_wifi()



# ============================================================
# INITIALIZE IMU
# ============================================================

i2c = I2C(scl='P0_2', sda='P0_3')

bmi = bmi270.BMI270(i2c)

print("IMU initialized")


# ============================================================
# CONNECT MQTT
# ============================================================

connect_mqtt()


# ============================================================
# MAIN LOOP
# ============================================================

last_imu_time = time.ticks_us()

while True:

    try:


        # Run inference
        punch_id, punch_name = get_punch_data()

        # Publish result if punch detected
        if punch_id is not None:

            publish_punch(punch_id, punch_name)

        # Small delay to reduce CPU load
        time.sleep_ms(5)

    except Exception as e:

        print("Main loop error:", e)

        # Try reconnect MQTT
        connect_mqtt()

        time.sleep(1)