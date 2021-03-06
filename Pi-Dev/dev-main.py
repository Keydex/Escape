#This is the main test file for GPIO Buttons and OMX control using a python wrapper
#Author: Anthony Pham
#June 26, 2016
import os
import RPi.GPIO as GPIO
import time
import cuFunctions
from omxplayer import OMXPlayer
#allows to kill omxplayer process in case of crash
os.system('sudo killall omxplayer.bin')

GPIO.setmode(GPIO.BCM)

GPIO.setup(5, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(6, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(13, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(19, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(26, GPIO.IN, pull_up_down = GPIO.PUD_UP)
player = OMXPlayer('/home/pi/Documents/Cabin-TIMERonly.mp4', ['--no-osd'])

#This code is for debugging purposes, incase system freezes it forces close after 30 seconds
timeout = time.time() + 30

while True:
    button_quit = GPIO.input(5)
    button_lose = GPIO.input(6)
    button_win = GPIO.input(13)
    button_start = GPIO.input(19)
    button_loop = GPIO.input(26)
    print('Error Code #002')
    player.play()
    if (button_loop == False):
        print('Loop Trigger by GameMaster')
        #       cuFunctions.loopvideo(player())
        player.set_position(0)
        print('Error Code #A01')
        while(True):
            button_start = GPIO.input(19)#WHY DOES THIS HAVE TO BE HERE? HOLY CRAP
            button_quit = GPIO.input(5)
            print('Error Code #A02')
            if (player.position() > 10):#Seconds until the system loops back to 0
                print('Loop Triggered by System')
                player.set_position(0)
                print('Error Code #A03')
            if (button_start == False):#When start pressed, game starts, then break out of loopvideo function
                print('Game Start Triggered by GameMaster')
                print('Error Code #A04')
                player.set_position(600)
                time.sleep(1)
                break#Break Wroks, use return for function Def
            if (button_quit == False):
                cuFunctions.killall()
            print('Error Code #A05')
    if (button_start == False):
        print('Game Start by GameMaster')
        player.set_position(600)
        time.sleep(1)
    if (button_win == False):
        print('Win Trigger by GameMaster')
        player.set_position(4200) #Jump to Win Time, 1:10
        time.sleep(1)
    if (button_lose == False):
        print('Lose Trigger by GameMaster')
        player.set_position(4800) #Jump to Lose Time, 1:20
        time.sleep(1)
    if (button_quit == False):
        cuFunctions.killall()
        break
    if (time.time() > timeout):
        print('SYSTEM ERROR: TIMEOUT, you are using the wrong file! Use start!')
        os.system('sudo killall omxplayer.bin')
        break
    #Video Time

player.quit()
print('Program Successfully Exited, I probably spelt that word wrong')
