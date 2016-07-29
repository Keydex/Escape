import os
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(2, GPIO.IN)
GPIO.setup(22, GPIO.OUT)
GPIO.output(22, 0)


try:
	while True:
		print('Looping')
		clock_Enable = GPIO.input(2)
		if(clock_Enable == True):
			print('Output is True')
			GPIO.output(22, True)
		else:
			print('Output is False')
			GPIO.output(22, False)
finally:
    GPIO.cleanup()
