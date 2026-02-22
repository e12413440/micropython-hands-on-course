import time                         # Import time-related functions for delays
import network                      # Import WiFi networking capabilities
import socket                       # Import socket for potential network communication
import gc                           # Import garbage collector for memory management
import json                         # Import JSON to convert data into payload format
from machine import I2C, Pin        # Import hardware control for I2C and GPIO pins
from micropython_bmi270 import bmi270 # Import driver for the BMI270 motion sensor
import array                        # Import array for efficient numerical storage
import deepcraft_model_05_2 as m    # Import the specific AI/ML model module
from umqtt.simple import MQTTClient # Import MQTT client for cloud communication

# ============================================================
# Configuration
# ============================================================

SSID = "USER_WIFI_SSID"                # Set the WiFi network name
PASSWORD = "USER_WIFI_PWD"         # Set the WiFi network password
PORT = 5000                         # Define local server port

# Ubidots parameters
MQTT_SERVER = "industrial.api.ubidots.com" # Cloud broker address
MQTT_PORT = 1883                           # Standard non-secure MQTT port
MQTT_CLIENT_ID = "boxtrainer_transmitter"  # Unique ID for this device on the broker
MQTT_TOPIC = b"/v1.6/devices/PSOC6-Boxer"  # Destination topic for the data
UBIDOTS_TOKEN = "USER_TOKEN"                  # Authentication token for Ubidots access


SESSION_ID = 1                      # Initial ID for the training session
SESSION_NAME = "Training_1"         # Initial name for the training session
button_pressed = False              # Global flag to track hardware button state

model = m.DEEPCRAFT()               # Instantiate the AI model class
model.init()                        # Initialize the AI model components

# Configure pin P5_2 as input with an internal pull-up resistor
button = Pin('P5_2', Pin.IN, Pin.PULL_UP)

# Define labels for the different punch categories
punch_types = ["Unlabeled", "Jab", "Side Hook", "Uppercut"]

# ============================================================
# Functions
# ============================================================

def setup_server():
    # Get network address information for the local host
    addr = socket.getaddrinfo("0.0.0.0", PORT)[0][-1]
    server = socket.socket()         # Create a new network socket
    
    # Allow immediate reuse of the port after restart
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(addr)                # Bind socket to the address and port
    server.listen(1)                 # Start listening for 1 simultaneous connection
    server.setblocking(False)        # Set to non-blocking to prevent loop freezing
    return server                    # Return the configured server object

def get_punch_data(bmi_sensor):
    try:
        acc = bmi_sensor.acceleration # Read X, Y, Z acceleration data
        gyro = bmi_sensor.gyro         # Read X, Y, Z gyroscope data
        # Pack sensor values into a float array for the model
        sample = array.array('f', [acc[0], acc[1], acc[2], gyro[0], gyro[1], gyro[2]])
        model.enqueue(sample)        # Feed the sample into the model's buffer

        out_dim = model.get_model_output_dim() # Get number of possible classes
        probs = array.array('f', [0.0] * out_dim) # Prepare array for probabilities
        model.dequeue(probs)         # Retrieve prediction results from model

        prob_max = max(probs)        # Find the highest probability value
        if prob_max >= 0.6:          # Only act if confidence is 60% or higher
            idx = 0                  # Default index
            for i in range(len(probs)): # Loop through results to find the winner
                if probs[i] == prob_max:
                    idx = i          # Store index of the detected punch
                    break
            if idx > 0:              # If it's not "Unlabeled" (index 0)
                return idx, punch_types[idx] # Return the ID and the name
    except Exception as e:
        print("Sensor Error:", e)    # Print error if sensor reading fails
    return None, None                # Return nothing if no valid punch detected


def button_isr(pin):
    global button_pressed            # Access the global flag
    # Set the flag to True when the interrupt is triggered
    button_pressed = True

# Attach an interrupt to the button that triggers on a falling edge
button.irq(handler=button_isr, trigger=Pin.IRQ_FALLING)

# ============================================================
# Init
# ============================================================

wlan = network.WLAN(network.STA_IF)  # Initialize WiFi station interface
wlan.active(True)                    # Turn on the WiFi radio
wlan.connect(SSID, PASSWORD)         # Start connection to access point

print("Connect WiFi...")
while not wlan.isconnected():        # Wait until WiFi connection is established
    time.sleep(0.5)

print("Verbunden! IP:", wlan.ifconfig()[0]) # Print local IP address

# Setup MQTT client: Ubidots uses Token as username and empty password
mqtt_client = MQTTClient(MQTT_CLIENT_ID, MQTT_SERVER, port=MQTT_PORT, user=UBIDOTS_TOKEN, password="")
try:
    mqtt_client.connect()            # Connect to the MQTT broker
    print("MQTT connected t  Ubidots")
except Exception as e:
    print("MQTT Connection failed:", e) # Handle connection failure

server = setup_server()              # Start the local server
i2c = I2C(id=0, scl='P0_2', sda='P0_3') # Initialize I2C communication
bmi = bmi270.BMI270(i2c)             # Initialize the BMI270 sensor

# ============================================================
# Main
# ============================================================

client = None                        # Placeholder for future client connections
print("System ready")              # System is ready to start

while True:
    # Check if the hardware button was pressed (flag set via ISR)
    if button_pressed:
        SESSION_ID += 1              # Increment the session counter
        # Create a new session string with the updated ID
        SESSION_NAME = "Training_{}".format(SESSION_ID)
        print("\n--- Button pressed! new session: {} ---".format(SESSION_NAME))
        
        time.sleep_ms(200)           # Debounce delay to prevent multiple triggers
        button_pressed = False       # Reset the flag

    # Run the punch detection logic using sensor data
    punch_id, punch_name = get_punch_data(bmi)

    if punch_id is not None:         # If a punch was actually recognized
        print("Detected:", punch_name)

        # Build the JSON payload for Ubidots format
        payload = {
            "punchtype": {
                "value": punch_id,
                "context": {"punchtype_ctxt": punch_name}
            },
            "session": {
                "value": SESSION_ID,
                "context": {"session_ctxt": SESSION_NAME}
            }
        }

        # Try to send the data to the cloud via MQTT
        try:
            # Publish the JSON-encoded payload to the specified topic
            mqtt_client.publish(MQTT_TOPIC, json.dumps(payload))
            print("MQTT publish success")
        except Exception as e:
            print("MQTT publish gone wrong, try to reconnect...")
            try:
                mqtt_client.connect() # Try to reconnect if the link was lost
            except:
                pass                 # Silently fail if reconnect also fails

    gc.collect()                     # Run garbage collection to free up RAM
    time.sleep_ms(10)                # Short delay to maintain loop stability