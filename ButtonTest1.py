import os
import RPi.GPIO as GPIO
import time
#The below allows us to create keyboard inputs to control the video
#import uinput

#The below allows us to wrap omxplayer into python, i.e. let us use commands from python to control it


GPIO.setmode(GPIO.BCM)

GPIO.setup(18, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(25, GPIO.IN, pull_up_down = GPIO.PUD_UP)

#The below sets us up to allow python/uinput to use these predefined keys
#device = uinput.Device([
#	uinput.KEY_P,
#	uinput.KEY_B,
#])



while True:
    input_state = GPIO.input(18)
    input_state2 = GPIO.input(25)
    if (input_state == False):
        os.system('omxplayer /home/pi/Documents/Cabin-WIN.mp4 &')
        os.system('echo Playing video test')
        time.sleep(1)
    if (input_state2 == False):
        os.system('echo This Works')

        time.sleep(1)
