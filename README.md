# Sensors
This repository is aimed at the examinars of EEEE1002 to view my code.
The code is inteded for all to use on their arduino to get relevant data from the appropriate sensors.

The sensors included in the repository are :

1. HC-SR04:

This will be used as an Ultrasonic Sonic distance sensor.
Here is some theory :

There is a trasmitter sends Ultrasonic pulses and when the waves are reflected back on to the reciever , the system records the time taken.
With this information the system can output the distance with 
Distance = velocity of Ultrasonic wave / time

Data sheet : https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
The data sheet prescribes the user to:
-send 10us high signal to the trigger
-time the high level duration
-Test distance = (high level time * velocity of sound ( 340M/s)/2

![image](https://user-images.githubusercontent.com/121031084/208462561-f7f73937-bcb7-4f2f-87e3-70e4ac01f1dc.png)


2. MPU-6050
3. GY-NEO6MU2
4. IR sensor
