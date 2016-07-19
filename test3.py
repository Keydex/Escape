import os
import RPi.GPIO as GPIO
import time
from omxplayer import OMXPlayer

GPIO.setmode(GPIO.BCM)

GPIO.setup(18, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(25, GPIO.IN, pull_up_down = GPIO.PUD_UP)
player = OMXPlayer('/home/pi/Documents/Cabin-TIMERonly.mp4')


timeout = time.time() + 30

while True:
    input_state = GPIO.input(18)
    input_state2 = GPIO.input(25)
    if (input_state == False):
        player.play()
        time.sleep(5)
    if (input_state2 == False):
        player.set_position(600)
        time.sleep(1)
    if(time.time() > timeout):
        print('TIMEOUT')
        break

player.quit()
print('It Hit Here')
