# ============================================================
# IMPORTS
# ============================================================
import time                                     # Import time-related functions for delays and timestamps
import network                                  # Import network module to manage WiFi connections
import socket                                   # Import socket module for low-level network communication
from machine import I2C                         # Import I2C class for hardware communication with sensors
from micropython_bmi270 import bmi270           # Import driver for the BMI270 inertial measurement unit
import array                                    # Import array module for memory-efficient data storage
import deepcraft_model_07_2 as m                # Import the custom AI punch-detection model
from umqtt.robust import MQTTClient             # Import MQTT client with auto-reconnect capabilities
import ujson                                    # Import JSON module to format data for the cloud


# ============================================================
# Configuration
# ============================================================

SSID = "A1-E6303791"                                       		# Define the WiFi network identifier (SSID)
PASSWORD = "uTv9yRngHF1N2V"                                   	# Define the WiFi network password


# MQTT / Ubidots configuration

MQTT_SERVER = "industrial.api.ubidots.com"      		# Set the Ubidots MQTT broker address
MQTT_PORT = 1883                                		# Set the standard non-secure MQTT port
MQTT_CLIENT_ID = "boxtrainer_transmitter"       		# Unique ID for this device on the MQTT broker
MQTT_TOPIC = b"/v1.6/devices/PSOC6-Boxer"       		# Binary string defining the destination MQTT topic
UBIDOTS_TOKEN = "BBUS-oCJ5n25UsXMlFIJjfcyEeQyefjg0Oi" 	# Authentication token for the cloud service

PUNCH_LABELS = ["Unlabeled", "Jab", "Hook", "Uppercut"] # List of classification result names

SESSION_ID = 1                                  		# Numerical ID for the current training session
SESSION_NAME = "Training_1"                     		# Human-readable name for the training session


model = m.DEEPCRAFT()                           		# Instantiate the DeepCraft AI model object
model.init()                                    		# Perform internal model initialization and setup


# ============================================================
# WiFi connection function
# ============================================================

def connect_wifi():                             # Define function to handle WiFi connectivity

    wlan = network.WLAN(network.STA_IF)         # Create a WiFi station interface instance
    wlan.active(True)                           # Power on the WiFi hardware module
    wlan.connect(SSID, PASSWORD)                # Attempt to connect to the specified network

    print("Connecting to WiFi...")              # Display status message to console

    while not wlan.isconnected():               # Wait in a loop until connection is successful
        time.sleep(1)                           # Check connection status every 1 second

    ip = wlan.ifconfig()[0]                     # Retrieve the assigned IP address from the router

    print("WiFi connected")                     # Log successful connection
    print("IP address:", ip)                    # Display the device IP address

    return ip                                   # Return the IP address for further use




# ============================================================
# MQTT functions
# ============================================================


def connect_mqtt():                             # Define function to connect to the broker

    try:                                        # Start error handling block
        mqtt_client.connect()                   # Attempt to establish MQTT connection
        print("MQTT connected")                 # Log successful connection
        return True                             # Indicate success

    except Exception as e:                      # Catch connection errors
        print("MQTT connection failed:", e)     # Log the specific error message
        return False                            # Indicate failure


def publish_punch(punch_id, punch_name):        # Define function to send data to cloud
    
    payload = {                                 # Define the JSON structure required by Ubidots
        "punchtype": {                          # Variable for the type of punch detected
            "value": punch_id,                  # Send numerical ID as the primary value
            "context": {                        # Attach metadata context
                "punchtype_ctxt": punch_name    # Send the punch name as a string context
            }
        },
        "session": {                            # Variable for tracking the training session
            "value": SESSION_ID,                # Send the session number
            "context": {                        # Attach metadata context
                "session_ctxt": SESSION_NAME    # Send the session name as a string
            }
        }
    }

    msg = ujson.dumps(payload)                  # Convert the Python dictionary into a JSON string

    try:                                        # Start block to handle publication
        mqtt_client.publish(MQTT_TOPIC, msg)    # Send the JSON payload to the specified topic
        print("Published:", punch_name)         # Confirm publication in the console

    except Exception as e:                      # Catch errors during transmission
        print("MQTT publish failed:", e)        # Log transmission failure
        connect_mqtt()                          # Attempt to reconnect if the link was broken


# Create MQTT client instance
mqtt_client = MQTTClient(                       # Configure the MQTT client with credentials
    MQTT_CLIENT_ID,                             # Pass the client ID
    MQTT_SERVER,                                # Pass the broker address
    MQTT_PORT,                                  # Pass the port number
    user=UBIDOTS_TOKEN,                         # Use Ubidots token as username
    password=UBIDOTS_TOKEN                      # Use Ubidots token as password
)


 

# ============================================================
# Processing function
# ============================================================

def get_punch_data():                           # Define function for data acquisition and AI processing
    
    acc_x, acc_y, acc_z = bmi.acceleration      # Fetch X, Y, Z values from the accelerometer
    gyro_x, gyro_y, gyro_z = bmi.gyro           # Fetch X, Y, Z rotational data from the gyroscope
    
    sample = array.array('f', [                 # Create a structured float array for the AI
        acc_x,                                  # X-acceleration component
        acc_y,                                  # Y-acceleration component
        acc_z,                                  # Z-acceleration component
        gyro_x,                                 # X-rotation component
        gyro_y,                                 # Y-rotation component
        gyro_z                                  # Z-rotation component
    ])

    model.enqueue(sample)                       # Pass the sensor data into the model buffer
    
    output_dim = model.get_model_output_dim()   # Determine the number of possible result classes
    probs = array.array('f', [0.0] * output_dim) # Initialize an empty array for probabilities
    
    model.dequeue(probs)                        # Retrieve calculated probabilities from the model

    max_prob = 0.0                              # Initialize highest probability tracker
    max_index = 0                               # Initialize index of the winning class

    for i in range(len(probs)):                 # Loop through all classification results
        if probs[i] > max_prob:                 # Check if current probability is higher than previous max
            max_prob = probs[i]                 # Update highest probability
            max_index = i                       # Store the index of the highest probability

    if max_prob >= 0.6 and max_index > 0:       # Check if confidence > 60% and not "Unlabeled"

        return max_index, PUNCH_LABELS[max_index] # Return the successful detection results

    return None, None                           # Return None if no clear punch was detected


# ============================================================
# Init
# ============================================================

ip_address = connect_wifi()                     # Execute WiFi connection routine and store IP

i2c = I2C(scl='P0_2', sda='P0_3')               # Initialize I2C bus using specific pin labels
bmi = bmi270.BMI270(i2c)                        # Instantiate the IMU sensor on the I2C bus
print("IMU initialized")                        # Confirm sensor is ready

connect_mqtt()                                  # Execute MQTT connection routine


# ============================================================
# Main
# ============================================================


while True:                                     # Start the infinite execution loop

    try:                                        # Begin main execution error handling block

        punch_id, punch_name = get_punch_data() # Acquire sensor data and run AI prediction
        
        if punch_id is not None:                # Check if the AI returned a valid punch event
            publish_punch(punch_id, punch_name) # Send the detection data to the Ubidots cloud

        time.sleep_ms(7)                        # Pause for 5 milliseconds to prevent over-utilization

    except Exception as e:                      # Catch any unexpected errors in the main loop

        print("Main loop error:", e)            # Log the error details
        connect_mqtt()                          # Attempt to restore MQTT connection on failure
        
        time.sleep(1)                           # Wait 1 second before resuming the loop