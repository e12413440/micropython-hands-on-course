import time									# module to implement delays
import network								# module for networking tasks
import ujson                                # Module to generate and parse JSON strings
from machine import Pin, I2C                # Machine module for GPIO and I2C hardware control
from umqtt.robust import MQTTClient         # Robust MQTT client for reliable IoT communication
from micropython_bmi270 import bmi270       # Driver for the BMI270 IMU sensor
import deepcraft_model as m
import array
 
 
 
# --------------------------------------- Configuration -------------------------------------
 
# WIFI setup
SSID = ""                                    # WiFi network name
PASSWORD = ""                   			# WiFi password
 
# MQTT setup
UBIDOTS_SERVER = "industrial.api.ubidots.com"               # Ubidots IoT server address
UBIDOTS_PORT = 1883                                         # Standard MQTT port
UBIDOTS_TOKEN = ""       # Your unique Ubidots authentication token
MQTT_CLIENT_ID = "boxtrainer"                               # Unique name for this MQTT client
TOPIC_PUBLISH = b"/v1.6/devices/psoc6-boxer"                # Topic path for sending punch data
TOPIC_SUBSCRIBE = b"/v1.6/devices/psoc6-boxer/session"      # Topic path for receiving session updates

# Timing constants
PUBLISH_INTERVAL = 1.5                      # Delay between data transmissions (seconds)
IMU_INTERVAL = 0.0025                       # Delay between sensor readings ($50Hz$ sampling)
 
# Global tracking variables
current_session_id = 0                      # Stores the ID of the current training session
punch_buffer = []                           # List to store punches detected between publishes
 
# --------------------------------------- MQTT Callback -------------------------------------
 
def sub_callback(topic, msg):               # Function triggered when a message arrives from Ubidots
    global current_session_id               # Access the global session ID variable
    try:
        # Decode bytes to UTF-8 string and parse the JSON structure
        data = ujson.loads(msg.decode('utf-8'))
        # Get value of data in the "value" key
        if "value" in data:
            current_session_id = float(data["value"])       # Update the session ID
            print(f"Session updated! New ID: {current_session_id}")
        else:
            print("Message received, but 'value' key is missing.")
 
    except Exception as e:                  # Handle parsing errors
        print("Error parsing incoming message:", e)
 
# --------------------------------------- Setup Functions -----------------------------------
 
def WiFi_connection():                      # Function to establish a wireless connection
    wlan = network.WLAN(network.STA_IF)     # Create a station interface object
    wlan.active(True)                       # Activate the WiFi hardware
    if not wlan.isconnected():              # Check if connection is already established
        print("Connecting to WiFi...")
        wlan.connect(SSID, PASSWORD)        # Attempt to connect to the AP
        timeout = 10                        # Set connection timeout to 10 seconds
        while not wlan.isconnected() and timeout > 0:       # Wait until connected or timeout
            time.sleep(1)                                   # Wait for 1 second
            timeout -= 1                                    # Decrement timer
    if wlan.isconnected():                  # Check if connection is successful
        print("WiFi connected! IP:", wlan.ifconfig()[0])
        return True                         # Return success
    else:
        print("WiFi connection failed.")
        return False                        # Return failure
 
def setup_mqtt():                           # Function to initialize the MQTT client
    # Create client with 60s keepalive to detect connection drops
    client = MQTTClient(MQTT_CLIENT_ID, UBIDOTS_SERVER, UBIDOTS_PORT, user=UBIDOTS_TOKEN, password=UBIDOTS_TOKEN, keepalive=60)
    client.set_callback(sub_callback)       # Link the callback function for subscriptions
    try:
        client.connect()                    # Establish connection to the broker
        client.subscribe(TOPIC_SUBSCRIBE)   # Listen for session ID changes from Ubidots
        print("Connected to Ubidots and subscribed to session topic.")
        return client                       # Return the initialized client
    except Exception as e:
        print("MQTT Setup failed:", e)
        return None                         # Return None if connection fails
 
# --------------------------------------- IMU & Model ---------------------------------------
 
try:
    # Initialize I2C bus on P0_2 (SCL) and P0_3 (SDA)
    i2c = I2C(0, scl=Pin('P0_2'), sda=Pin('P0_3')) 
    bmi = bmi270.BMI270(i2c)                # Initialize the BMI270 sensor object
except Exception as e:
    print("Hardware initialization error:", e)
 
 
# function to get punch data with the model implemented in deepcraft
 
def get_punch_data():                       # Function to analyze sensor data
    acc_x, acc_y, acc_z = bmi.acceleration                  # Read acceleration data (x, y, z)
    gyro_x, gyro_y, gyro_z = bmi.gyro                         # Read angular velocity data
    # Placeholder logic: Replace this with your actual DeepCraft model inference
    
    print("acc_x:", acc_x, "acc_y", acc_y, "acc_z", acc_z)
    
    sample = [acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z]
    model.enqueue(sample)
    
    out_dim = model.get_model_output_dim()
    probs = array.array('f', [0.0] * out_dim)
    
    result = model.dequeue(probs)
    punch_types = ["Unlabled", "Jab", "Side Hook", "Uppercut"]

    prob_max = max(probs)				# Find the highest confidence score
        
    if prob_max >= 0.6:					# Threshold to confirm a punch
        idx = probs.index(prob_max)		# Get the index of the detected punch
        if idx == 0:
            return None, None
        else:
            return idx, punch_types[idx]	# Return the numeric ID and the name

    return None, None						# Return None if no punch is detected

# --------------------------------------- Main Loop -----------------------------------------
 
if WiFi_connection():                       # Start only if WiFi is available

    client = setup_mqtt()                   # Initialize MQTT
    last_publish_time = time.time()         # Initialize timer for publishing
    last_imu_read_time = time.time()        # Initialize timer for sensor sampling
    
    model = m.DEEPCRAFT()
    model.init()
 
    if client:                              # Ensure the client was created successfully
        while True:                         # Start infinite processing loop
            try:
                client.check_msg()          # Check for incoming MQTT messages
                current_time = time.time()  # Get current system time
                
                # HIGH FREQUENCY SAMPLING
                if current_time - last_imu_read_time >= IMU_INTERVAL:
                    punch_id, punch_name = get_punch_data()         # Run punch detection
                    print("Punch ID:", punch_id, "Punch name:", punch_name)
                    if punch_id is not None:                    	# If a punch was confirmed
                        punch_buffer.append({"id": punch_id, "name": punch_name}) # Store in list


                    last_imu_read_time = current_time       # Reset IMU timer
                # LOW FREQUENCY PUBLISHING
                if current_time - last_publish_time >= PUBLISH_INTERVAL:
                    if len(punch_buffer) > 0:               # Only publish if punches occurred
                        last_punch = punch_buffer[-1]       # Get the most recent punch
                        session_name = f"Training {current_session_id}"
                        # Build the JSON payload for Ubidots
                        payload = {
                            "punchtype":
                            {
                                "value": last_punch["id"],            				# publish numeric punch ID (1-3) for Ubidots calculation
                                "context": {"punchtype_ctxt": last_punch["name"]}	# publish metadata (actual name of the punch)
                            },
                            "session":
                            {
                                "value": current_session_id,                    # publish numeric session ID (1-3)
                                "context": {"session_ctxt": session_name}       # publish actual name of the session
                            }
                        }

                        # Convert dict to JSON string and send to broker
                        client.publish(TOPIC_PUBLISH, ujson.dumps(payload))
                        print(f"Sent: {last_punch['name']} ({len(punch_buffer)} hits in buffer)")
                        punch_buffer = []                   # Clear the buffer after successful send
                    last_publish_time = current_time        # Reset publish timer
 
                time.sleep(0.001)
 
            except Exception as e:          # Global error handling for connection issues
                print("Loop error, attempting reconnect...", e)
                time.sleep(5)               # Wait before retrying
                client = setup_mqtt()       # Re-initialize MQTT connection