import time
from machine import Pin, I2C
import array
import bmi270       # BMI270 IMU Driver
import deepcraft_model as m
import gc
import math


#sample = array.array('f', [0.0] * 3)
looptime = 10.0 	#ms
start_integration = False
velocity = 0.0
last_imu_read_time = time.ticks_us()
gx = 0.0
gy = 0.0
gz = 0.0
alpha = 0.9

try:
    i2c = I2C(0, scl=Pin('P0_2'), sda=Pin('P0_3'))
    bmi = bmi270.BMI270(i2c)
except Exception as e:
    print("Hardware initialization error:", e)



def get_velocity():
    global start_integration, velocity
    global gx, gy, gz, alpha

    acc_x, acc_y, acc_z = bmi.acceleration
    
    #this variables track the gravity influence on each axis to achieve linear acceleration values
    gx = alpha * gx + (1-alpha) * acc_x
    gy = alpha * gy + (1-alpha) * acc_y
    gz = alpha * gz + (1-alpha) * acc_z

    # Linear acceleration
    lin_x = acc_x - gx
    lin_y = acc_y - gy
    lin_z = acc_z - gz
    
    
    total_lin_acc = math.sqrt(math.pow(lin_x,2) + math.pow(lin_y,2) + math.pow(lin_z,2))
    
    if total_lin_acc > 5.0:           #Threshold to start discrete integration
        if start_integration == False: 
            start_integration = True
    else:
        if start_integration:
            start_integration = False
            return velocity
        else:
            velocity = 0.0
            return None
    
    if start_integration:
        velocity = velocity + total_lin_acc*looptime/1000   #velocity is discrete integration of acceleration, in m/s
        
                
while True:
    try:
        current_time = time.ticks_us()
        #print(time.ticks_diff(current_time, last_imu_read_time)/1000)
        last_imu_read_time = current_time
        val = get_velocity()
        
        if val is not None:
            print(val, " m/s")
        
        
        # tiny sleep für Scheduler & GC
        time.sleep_ms(9)
        

    except Exception as e:
        print("Loop error:", e)
        time.sleep(5)
    
    

