# First gpio tests
#




# Currently, all I have to test is an HC-SR04 ultrasonic sensor mondule.
# Need a stronger power source to run the servo motors.

from gpiozero import DistanceSensor
from time import sleep

ultra = DistanceSensor(echo=27, trigger=17)

try:
	while True:
		distance = ultra.distance * 100 # convert to cm
		print(f"Distance: {distance:.2f} cm")
		sleep(0.1)
except KeyboardInterrupt:
	print("Measurement stopped by user.")


# IT'S WORKING YEAHHHHHHHHHHHHH BUDDY