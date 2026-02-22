import time                                     # Import time-related functions for delays
import network                                  # Import network module to manage WiFi connections
import socket                                   # Import socket module for TCP/IP communication
import gc                                       # Import garbage collector for manual memory management
from machine import I2C                         # Import I2C class for hardware communication
from micropython_bmi270 import bmi270           # Import driver for the BMI270 IMU sensor
import array                                    # Import array module for efficient numerical data storage
import deepcraft_model_05_2 as m                # Import the specific trained model library



# ============================================================
# Configuration
# ============================================================

SSID = "USER_WIFI_SSID"
PASSWORD = "USER_WIFI_PWD"
PORT = 5000                                     # Set the network port for the server

model = m.DEEPCRAFT()                           # Instantiate the AI model object
model.init()                                    # Initialize the AI model logic/hardware

punch_types = ["Unlabeled", "Jab", "Side Hook", "Uppercut"] # Define the names of the punch categories



# ============================================================
# Functions
# ============================================================

# Function to initialize the network server

def setup_server():
    
    addr = socket.getaddrinfo("0.0.0.0", PORT)[0][-1] # Resolve the IP address and port
    server = socket.socket()                    # Create a new socket object
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # Allow restarting the server quickly
    server.bind(addr)                           # Bind the socket to the address and port
    server.listen(1)                            # Start listening for incoming connections
    
    return server                               # Return the configured server object

# Function to process sensor data and give punch result

def get_punch_data(bmi_sensor):

    try:                                        # Start error handling block
        acc = bmi_sensor.acceleration           # Read 3-axis accelerometer data
        gyro = bmi_sensor.gyro                  # Read 3-axis gyroscope data

        # Daten für Modell vorbereiten
        sample = array.array('f', [acc[0], acc[1], acc[2], gyro[0], gyro[1], gyro[2]]) # Create a float array of IMU data
        model.enqueue(sample)                   # Feed the sample into the AI model's queue

        # Wahrscheinlichkeiten abrufen
        out_dim = model.get_model_output_dim()  # Get the number of output classes from the model
        probs = array.array('f', [0.0] * out_dim) # Create an empty float array for probabilities
        model.dequeue(probs)                    # Fill the array with the model's prediction results

        prob_max = max(probs)                   # Find the highest probability value

        # Erkennungsschwelle (60%)
        if prob_max >= 0.6:                     # Check if the highest probability exceeds threshhold 60%
            idx = 0                             # Initialize index variable
            for i in range(len(probs)):         # Iterate through all probability results
                if probs[i] == prob_max:        # Find the index of the maximum value
                    idx = i                     # Store index
                    break                       # Exit the loop if found
            
            if idx > 0:                         # Ensure the detected action is not "Unlabeled"
                return idx, punch_types[idx]    # Return the ID and the name of the punch

    except Exception as e:                      # Catch any errors during processing
        print("Sensor Error:", e)           	# Print the error message to the console

    return None, None                           # Return nothing if no punch was detected or an error occurred



# ============================================================
# Init
# ============================================================


# WiFi Connection

wlan = network.WLAN(network.STA_IF)             # Initialize the WiFi station interface
wlan.active(True)                               # Activate the WiFi hardware
wlan.connect(SSID, PASSWORD)                    # Start the connection process to the AP

print("Verbinde WiFi...")                       # Notify that connection is in progress
while not wlan.isconnected():                   # Loop until the connection is established
    time.sleep(0.5)                             # Wait half a second between checks

ip = wlan.ifconfig()[0]                         # Retrieve the assigned IP address
print("Verbunden! IP:", ip)                     # Print the successful connection and IP


# BMI & Server Connection

server = setup_server()                         # Run the server setup function
i2c = I2C(id=0, scl='P0_2', sda='P0_3')         # Initialize I2C with specific pins
bmi = bmi270.BMI270(i2c)                        # Initialize the BMI270 sensor via I2C



# ============================================================
# Main
# ============================================================

client = None                                   # Initialize the client variable as empty
last_imu_read = time.ticks_us()                 # Record the initial timestamp in microseconds

print("System ready. Waiting for client on port", PORT) # Notify that the system is ready

while True:                                     # Start the infinite main loop
    current_time = time.ticks_us()              # Get the current time in microseconds

    if client is None:                          # Check if a client is currently connected
        try:                                    # Start block to attempt a connection
            new_client, addr = server.accept()  # Wait for and accept a new connection
            print("Client connected:", addr)    # Print the address of the connected client
            client = new_client                 # Store the client connection
            client.setblocking(True)            # Ensure the socket is in blocking mode for stable sends
        except OSError:                         # Catch error if no client is trying to connect
            pass 								# No client connected


        
    p_id, p_type = get_punch_data(bmi)          # Call function to get punch detection results

    if p_id is not None:                        # If a valid punch was detected
        msg = "{},{}\r\n".format(p_id, p_type)  # Format the ID and name into a CSV string
        print("Detected:", p_type)              # Print the detection result locally
            
        if client is not None:                  # If a network client is active
            try:                                # Try to send the data
                client.write(msg.encode())      # Convert string to bytes and send to client
            except OSError:                     # Catch error if the connection failed
                print("Connection to client lost") # Notify connection loss
                client.close()                  # Close the broken client socket
                client = None                   # Reset client variable to allow new connections
        
    gc.collect()                                # Trigger garbage collection to free up RAM

    time.sleep_ms(7)                            # Pause execution for 7ms 