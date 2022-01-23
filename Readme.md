# Obstacle Avoiding Arduino Trank

![alt text](https://github.com/attila-virag/Arduino-Projects/blob/main/Robot%20Tank%20Project/images/yahboom%20tank.jpg?raw=true)

An obstacle avoiding explorer tank that is based on the robot tank by yahboom: http://www.yahboom.net/study/G1-T-AR. This project uses all my original code but is mostly following the same hardware setup as given in the yahboom kit. I ditched the infrared tracking module as I was not interested in line tracking. The robot will "explore" an area by continously driving away from obstacles it detects in its field of vision. It uses an ultrasonic sensor which sits on top of a servo that controls the direction of the head to detect obstacles. 

## RGB module

![alt text](https://github.com/attila-virag/Arduino-Projects/blob/main/Robot%20Tank%20Project/images/RGB%20module.PNG?raw=true)

The "eyes" of the robot are a set of RGB LED lights. The three colors are controlled by arduino pins 11 (red), 10 (green), and 9 (blue). Obviously the lights serve no purpose for obstacle detection but I decided to use them to signify the state of the robot. Green means no obstacle, blue means distant obstacle and red means a close obstacle was detected. The test code is looking for text commands from serial in to operate the lights. Component Test code: https://github.com/attila-virag/Arduino-Projects/blob/main/Robot%20Tank%20Project/Component%20Testing/led_control/led_control.ino

Conceptual schematic in relation to the adruino uno:

![alt text](https://github.com/attila-virag/Arduino-Projects/blob/main/Robot%20Tank%20Project/images/LED%20schematic.PNG?raw=true)


## Ultrasonic Distance Sensor

![alt text](https://github.com/attila-virag/Arduino-Projects/blob/main/Robot%20Tank%20Project/images/ultrasonic.PNG?raw=true)

This one ties together the LED lights and distance detection. The LEDs will light up different colors depending on the distance measured. The ultrasonic sensor is a HC-SR04 with a Trig pin tied to arduino pin 13 and the Echo pin tied to arduino pin 12. The component test code is here: https://github.com/attila-virag/Arduino-Projects/blob/main/Robot%20Tank%20Project/Component%20Testing/ultrasonic/ultrasonic.ino

![alt text](https://github.com/attila-virag/Arduino-Projects/blob/main/Robot%20Tank%20Project/images/LED%20and%20sensor%20schematic.PNG?raw=true)

## Servo Control With Distance Sensor

This ties together the distance detection and LED lights with a side to side scanning motion using the servo. The distance sensor and the LED module are attached to the servo as shown in the yahboom hardware instrucions. For this test code the servo will sweep out nearly its full range of motion. For the actual driver code there is a concept of a deep and shallow field of vision scan depending on the state of the robot. When a close distance is detected (red light) there is a slight pause in the scanner. The servo goes to pin 3 on the arduino. The component test code is here: https://github.com/attila-virag/Arduino-Projects/blob/main/Robot%20Tank%20Project/Component%20Testing/ultrasonic_servo/ultrasonic_servo.ino

![alt text](https://github.com/attila-virag/Arduino-Projects/blob/main/Robot%20Tank%20Project/images/LED%20sensor%20servo%20schematic.PNG?raw=true)

## Motor Control

The expansion board included in the kit uses the TB6612FNG chip to drive the motor. From our end we just need to know which arduino pins to interface with. Each motor has three inpouts: forward, reverse, and speed (analog). The digital HIGH on forward moves the motor at the set motor speed in the forward direction for example. For simplicity I operate the three sets of pins in unison using specialized methods for driving forward, reversing etc. The component test code exercises the Driving methods deterministically for a set time each. https://github.com/attila-virag/Arduino-Projects/blob/main/Robot%20Tank%20Project/Component%20Testing/motor_control/motor_control.ino

## Automatic Sensor Controlled Driver

The full driver code is here: https://github.com/attila-virag/Arduino-Projects/blob/main/Robot%20Tank%20Project/Driver/sensor_control_driver/sensor_control_driver.ino. 


