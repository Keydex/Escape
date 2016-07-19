#This is to actually test if buttons are working
#Author: Anthony Pham
#July 3, 2016
import os
import RPi.GPIO as GPIO
import time
import cuFunctions
from omxplayer import OMXPlayer

GPIO.setmode(GPIO.BCM)

GPIO.setup(5, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(6, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(13, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(19, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(26, GPIO.IN, pull_up_down = GPIO.PUD_UP)


while True:
     button_quit = GPIO.input(5)
     button_lose = GPIO.input(6)
     button_win = GPIO.input(13)
     button_skip = GPIO.input(19)
     button_start = GPIO.input(26)
     if (button_start == False):
        print('Start Works!')
        time.sleep(1)
     if (button_skip == False):
        print('Skip Works!')
        time.sleep(1)
     if (button_win == False):
        print('Win Works!')
        time.sleep(1)
     if (button_lose == False):
        print('Lose Works!')
        time.sleep(1)
     if (button_quit == False):
        print('Quit Works!')
        time.sleep(1)