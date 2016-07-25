import os
import RPi.GPIO as GPIO
import time

segments = (2,3,4,17,27,22,10,9,14,15,18)
GPIO.setmode(GPIO.BCM)
digits = (7,12,16,20,21)
for segment in segments:
    GPIO.setup(segment, GPIO.OUT)
    GPIO.output(segment, 0)
for digit in digits:
    GPIO.setup(digit, GPIO.OUT)
    GPIO.output(digit, 1)
 
num = {' ':(0,0,0,0,0,0,0),
    '0':(1,1,1,1,1,1,0),
    '1':(0,1,1,0,0,0,0),
    '2':(1,1,0,1,1,0,1),
    '3':(1,1,1,1,0,0,1),
    '4':(0,1,1,0,0,1,1),
    '5':(1,0,1,1,0,1,1),
    '6':(1,0,1,1,1,1,1),
    '7':(1,1,1,0,0,0,0),
    '8':(1,1,1,1,1,1,1),
    '9':(1,1,1,1,0,1,1)}
try:
    while True:
    	GPIO.output(segments, 1)
    	GPIO.output(digits, 0)
finally:
    GPIO.cleanup()