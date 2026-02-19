import time									# module to implement delays
import network								# module for networking tasks
import ujson                                # Module to generate and parse JSON strings
from machine import Pin, I2C                # Machine module for GPIO and I2C hardware control
#from umqtt.robust import MQTTClient         # Robust MQTT client for reliable IoT communication
import bmi270       # Driver for the BMI270 IMU sensor
import deepcraft_model as m
import array
 
 
# --------------------------------------- Configuration -------------------------------------
 

 
# Timing constants
PUBLISH_INTERVAL = 1.5                      # Delay between data transmissions (seconds)
IMU_INTERVAL = 0.0025                         # Delay between sensor readings ($50Hz$ sampling)

out_dim = 4
probs = array.array('f', [0.0] * out_dim)

model = m.DEEPCRAFT()
model.init()
last_imu_read_time = time.ticks_us()
 
# Global tracking variables
# --------------------------------------- MQTT Callback -------------------------------------
 

# --------------------------------------- Setup Functions -----------------------------------

 
 
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
    
    #print("acc_x:", acc_x, "acc_y", acc_y, "acc_z", acc_z)
    
    sample = [acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z]
    model.enqueue(sample)
    
    
    
    result = model.dequeue(probs)
    
    if result == 0:
        print("dequeue sucessful")
        print(probs)
    
    punch_types = ["Unlabled", "Jab", "Side Hook", "Uppercut"]

    #prob_max = max(probs)				# Find the highest confidence score
    #if prob_max >= 0.6:					# Threshold to confirm a punch
     #   idx = probs.index(prob_max)		# Get the index of the detected punch
      #  if idx == 0:
       #     return None, None
       # else:
      #      return idx, punch_types[idx]	# Return the numeric ID and the name

    #return None, None	
 
# --------------------------------------- Main Loop -----------------------------------------
 
 
 
 
while True:                         # Start infinite processing loop
            try:
                          # Check for incoming MQTT messages
                current_time = time.ticks_us()  # Get current system time
                # HIGH FREQUENCY SAMPLING
                #if time.ticks_diff(current_time, last_imu_read_time)/1000 >= IMU_INTERVAL*1000:
                #print(time.ticks_diff(current_time, last_imu_read_time)/1000)
                get_punch_data()         # Run punch detection
                    #if p_id == not None:                    # If a punch was confirmed
                     #   punch_buffer.append({"id": punch_id, "name": punch_name}) # Store in list
                    
                last_imu_read_time = current_time       # Reset IMU timer
                # LOW FREQUENCY PUBLISHING
               
               # time.sleep(0.001)
 
            except Exception as e:          # Global error handling for connection issues
                print("Loop error, attempting reconnect...", e)
                time.sleep(5)               # Wait before retrying
                     # Re-initialize MQTT connection
 