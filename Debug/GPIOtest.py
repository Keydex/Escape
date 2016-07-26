import os
import RPi.GPIO as GPIO
import time

segments = (2,3,4,17,27,22)
GPIO.setmode(GPIO.BCM)
for segment in segments:
	GPIO.setup(segment, GPIO.OUT)
	GPIO.output(segment, 0)


try:
    while True:
    	GPIO.output(segments, 0)
finally:
    GPIO.cleanup()
