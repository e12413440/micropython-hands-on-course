import time								# module to implement delays
import network							# module for networking tasks
import ujson							# module to generate JSON string
from machine import Pin, I2C			# machine module for I2C and Pins
from umqtt.robust import MQTTClient		
from micropython_bmi270 import bmi270	# driver for BMI270 IMU sensor



# --------------------------------------- Configuration -------------------------------------

# WIFI setup

SSID = "USER_SSID"
PASSWORD = "USER_PASSWORD"

# MQTT setup

UBIDOTS_SERVER = "industrial.api.ubidots.com"				# defining ubidots IoT server
UBIDOTS_PORT = 1883											# defining ubidots IoT server
UBIDOTS_TOKEN = "USER_TOKEN"								# defining the ubidots token
MQTT_CLIENT_ID = "boxtrainer"								# defining MQTT client name
TOPIC_PUBLISH = b"/v1.6/devices/psoc6-boxer"				# defining topic path for publishing
TOPIC_SUBSCRIBE = b"/v1.6/devices/psoc6-boxer/session"		# defining topic path for subscribing session values

PUBLISH_INTERVAL = 0.5		# defining interval between each publish
IMU_INTERVAL = 0.02			# defining interval between each time new data is read of the IMU
current_session_id = 0		# defining global variable 



# --------------------------------------- MQTT Callback -------------------------------------

# function for recieving data sent from MQTT server to the PSOC6 controller 
def sub_callback(topic, msg):
    
    global current_session_id	# defining global variable for getting new Session ID´s
    
    try:
        current_session_id = float(msg)						# read the new session ID out of the message transmitted from Ubidots
                                                            # chacking the format of the message (has to be a float otherwhise exception)
        print("A new training session has been started! The ID is: ", current_session_id)
        
    except Exception as e:									# error handler for all possible exceptions
        print("Error while starting new session", e)



# --------------------------------------- Setup Funktionen ----------------------------------

# function for WiFi connection
def WiFi_connection():
    
    wlan = network.WLAN(network.STA_IF)						# creating wlan object
    wlan.active(True)										# activate wlan object
    if not wlan.isconnected():								# check if WiFi is not connected
        
        print("Connecting to WiFi...")
        wlan.connect(SSID, PASSWORD)						# execute function tying to connect to WiFi
        timeout = 10										# defining timeout of 10 seconds (time to connect)
        
        while not wlan.isconnected() and timeout > 0:		# countdown of timeout while WiFi is not connected
            time.sleep(1)									# delay of 1 second
            timeout -= 1									# decrement timout
            
    if wlan.isconnected():									# check if WiFi is connected
        
        print("WiFi connected with IP:", wlan.ifconfig()[0])
        return True											# return true if connection was successful
    
    else:													# else WiFi connection failed
        
        print("WiFi connection failed")
        return False										


def setup_mqtt():
    
    # create object of MQTTClient class called client
    # keepalive sending ping every 60 seconds -> Server notices if connection is lost due to low battery etc.
    client = MQTTClient(client_id=MQTT_CLIENT_ID, server=UBIDOTS_SERVER, port=UBIDOTS_PORT, ser=UBIDOTS_TOKEN, password=UBIDOTS_TOKEN, keepalive=60)
    
    # aadding sub_callback function to be executed if client gets a message from server
    client.set_callback(sub_callback)
    
    try:
        
        client.connect()							# building TCP connection between server and controller
        client.subscribe(TOPIC_SUBSCRIBE)			# receiving data from the server in the channel/topic (TOPIC_SUBSCRIBE)
        print("Connection to Ubidots and Subscritpion successful")
        return client                               # return object client if successful
    
    except Exception as e:                          # handle all errors due to exceptions
        print("MQTT Connection failed:", e)
        return None

# --------------------------------------- IMU & Model ---------------------------------------

# Initialize IMU-BMI270 and i2c bus

try:
    i2c = I2C(0, scl=Pin('P0_2'), sda=Pin('P0_3')) # declare i2c pins
    bmi = bmi270.BMI270(i2c)					   # init BMI270 with i2c and define object
    
except Exception as e:							   # handle exceptions that might occur
    print("hardware setup error:", e)



# define function that gives the most probable punch type with the model generated in deepcraft

def get_punch_data():
    
    # Getting acceleration and angular velocity out of IMU
    # Needed as Input for the model function
    acc = bmi.acceleration
    gyro = bmi.gyro
    
    probs = [0.7, 0.2, 0.1]						# placeholder for the generated function of the trained model
    punch_types = ["Jab", "Hook", "Uppercut"]	# creating array with all different punch types
    
    prob_max = max(probs)						# determine the maximum probabiltity of model output
    prob_max_idx = probs.index(prob_max)		# determine the index of highest probability
    
    if (prob_max >= 0.5):						# defining a threshold of a 50% that has to be exceeded
        return prob_max_idx, punch_types[prob_max_idx], probs
    
    else:										# probs not high enough to make a clear decision
        return None, None, probs
    
# --------------------------------------- Main Loop -----------------------------------------

if connect_wifi():                                                          # checking if WiFi is connected properly
    
    client = setup_mqtt()                                                   # setting up connection between client and server
    last_publish_time = time.time()                                         # defning time at which data has been published last
    last_IMU_read_time = time.time()

    if client:                                                              # checking if client has been started properly
        
        while True:															# create an infinit while loop
            
            try:
                client.check_msg()											# checking if new Session ID´s have been sent
                current_time = time.time()                                  # defining current time
                
                if current_time - last_IMU_read_time >= IMU_INTERVAL:
                    punch_id, punch_name, all_probs = get_punch_data()      # call get_punch_data function every 0.02 seconds
                                                                            # model was trained with at lealst 50Hz samples
                    last_IMU_read_time = current_time
                    
                if (current_time - last_publish_time >= PUBLISH_INTERVAL)and not(punch_id == None):

                    session_name = f"Training {current_session_id}"         # defining the session name
                    

                    # Define the data structure (JSON) to send to Ubidots
                    payload = {
                        "punchtype": {
                            "value": punch_id,                              # publish numeric punch ID (1-3) for Ubidots calculation
                            "context": {"punchtype_ctxt": punch_name}       # publish metadata (actual name of the punch)
                        },
                        "session": {
                            "value": current_session_id,                    # publish numeric session ID (1-3)
                            "context": {"session_ctxt": session_name}       # publish actual name of the session
                        }
                    }                    
                    
                    client.publish(TOPIC_PUBLISH, ujson.dumps(payload))     # Convert the dictionary to a JSON string and publish it to the Ubidots topic
                    print(f"Sent: {punch_name} (Session: {current_session_id})")
                    
                    last_publish_time = current_time                        # update last publish time with current time

                time.sleep(0.001)

            except Exception as e:                                          # error handler for connection drops or a sensor fails
                
                print("Loop Error, reconnecting...", e)
                time.sleep(5)                                               # adding delay to avoid spamming
                client = setup_mqtt()						                # Trying restore connection with client