#Enables All LEDS
import os
import RPi.GPIO as GPIO
import time
segments = (2,3,4,17,27,22,10,9,14,15,18)
GPIO.setmode(GPIO.BCM) ## Use board pin numbering
GPIO.setup(segments, GPIO.OUT) ## Setup GPIO Pin 7 to OUT
GPIO.output(segments,True) ## Turn on GPIO pin 7