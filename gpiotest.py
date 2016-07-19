#Testing GPIO Outputs
#Author: Anthony Pham
#June 26, 2016
import os
import RPi.GPIO as GPIO
import time


GPIO.setmode(GPIO.BCM)

GPIO.setup(5, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(6, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(13, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(19, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(26, GPIO.IN, pull_up_down = GPIO.PUD_UP)



while True:
     input_state5 = GPIO.input(5)
     input_state4 = GPIO.input(6)
     input_state3 = GPIO.input(13)
     input_state2 = GPIO.input(19)
     input_state1 = GPIO.input(26)
     if input_state1 == False:
      print('Button 1 Pressed')
      time.sleep(0.2)
     if input_state2 == False:
      print('Button 2 Pressed')
      time.sleep(0.2)
     if input_state3 == False:
      print('Button 3 Pressed')
      time.sleep(0.2)
     if input_state4 == False:
      print('Button 4 Pressed')
      time.sleep(0.2)
     if input_state5 == False:
      print('Button 5 Pressed')
      time.sleep(0.2)
