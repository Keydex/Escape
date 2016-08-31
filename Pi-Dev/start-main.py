#!/usr/bin/python
# -*- coding: utf-8 -*-
# This is the main test file for GPIO Buttons and OMX control using a python wrapper
# Author: Anthony Pham
# June 26, 2016

import os
import RPi.GPIO as GPIO
import time
import cuFunctions
import logging
from omxplayer import OMXPlayer

# allows to kill omxplayer process in case of crash

os.system('sudo killall omxplayer.bin')

GPIO.setmode(GPIO.BCM)

# Button Triggers and Manual Overrides

GPIO.setup(5, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Force quit Program Button
GPIO.setup(6, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Force Lose Button
GPIO.setup(13, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Force Win Button
GPIO.setup(19, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Start Game Button
GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Force Back to Loop (Or reset Game)
GPIO.setup(11, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # The Red Button
GPIO.setup(9, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # The Door
GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Increment Time
GPIO.setup(27, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Decrement Time

# Dmx Output

GPIO.setup(14, GPIO.OUT)  # Used for DMX Trigger OFF A1
GPIO.setup(15, GPIO.OUT)  # Used for DMX Trigger ON A0
GPIO.output(14, 0)
GPIO.output(15, 0)

# Clock I/O
# GPIO.setup(23, GPIO.OUT)#Tells clock that game is finished
# GPIO.setup(24, GPIO.OUT)#Tells clock the game time can be reset
# GPIO.setup(25, GPIO.OUT)#Tells clock the game can start
# GPIO.setup(7, GPIO.OUT)#Tells Arduino that the Game Master Force Trigger Lose

# GPIO.output(23, 0)
# GPIO.output(24, 0)
# GPIO.output(25, 0)
# GPIO.output(7, 0)

# Clock Arduino to Pi connections
# Note that if 2 and 3 are both on, that means the game win is triggered
# GPIO.setup(2, GPIO.IN)#Arduino To Pi to tell time is up Pin 6

GPIO.setup(3, GPIO.IN)  # Arduino to Pi to signal game win

player = OMXPlayer('/home/pi/Documents/Technoscape-GameReady3.mp4',
                   ['--no-osd'])  # Uncomment this to use with no timer

# player = OMXPlayer('/home/pi/Documents/Technoscape-GameReady3.mp4') #Used for debugging

winStart_time = 4032
winEnd_time = 4110
loseStart_time = 3900
loseEnd_time = 3920  # 1:05:20
redbuttonStart_time = 4315
redbuttonEnd_time = 4345
chamberStart_time = 4619
RedAllowTalk = 4702  # This is used to give time when Red button is allowed to be Pressed
tenminStart_time = 3305
arduino_delay = 3  # Second Delay to bring arduino data pin High

# The Check Functions Prevent people from triggering them twice

resetCheck = False
doorCheck = False
redCheck = False
endCheck = False
startCheck = False
startTime = 0
finalCheck = False
timeCheck = 0
debug_offset = 0
try:
    while True:
        button_quit = GPIO.input(5)
        button_lose = GPIO.input(6)
        button_win = GPIO.input(13)
        button_start = GPIO.input(19)
        button_loop = GPIO.input(26)
        button_RED = GPIO.input(11)
        door_Switch = GPIO.input(9)
        time_decrement = GPIO.input(27)
        time_increment = GPIO.input(17)

#        trigger_END = GPIO.input(2)

        trigger_WIN = GPIO.input(3)
        player.play()  # This is in the while loop. But it doesn't reset the video. Strange'
        currentTime = time.time() + debug_offset
        if button_loop == False or resetCheck == True:
            resetCheck = False
            doorCheck = False
            redCheck = False
            endCheck = False
            startCheck = False
            finalCheck = False
            print 'Loop Trigger by GameMaster'
            player.set_position(0)

            #       cuFunctions.loopvideo(player())

            while True:
                button_start = GPIO.input(19)  # WHY DOES THIS HAVE TO BE HERE? HOLY CRAP
                button_quit = GPIO.input(5)
                GPIO.output(15, 1)
                if player.position() > 300:  # Seconds until the system loops back to 0
                    print 'Loop Triggered by System'
                    player.set_position(0)
                if button_start == False:  # When start pressed, game starts, then break out of loopvideo function
                    print 'Game Start Triggered by GameMaster'
                    startTime = time.time()
                    startCheck = True
                    player.set_position(301)
                    GPIO.output(15, 0)
                    time.sleep(.2)
                    break  # Break Wroks, use return for function Def
                if button_quit == False:
                    cuFunctions.killall()
        if button_start == False:
            print 'Game Start by GameMaster'
            startTime = time.time()
            startCheck = True
            player.set_position(301)
            time.sleep(.2)
        if button_win == False:
            print 'Win Trigger by GameMaster'
            player.set_position(winStart_time)
            doorCheck = True
            redCheck = True
            endCheck = True
            time.sleep(.2)
        if trigger_WIN == True:
            print 'Win Trigger by Last Puzzle'
            player.set_position(winStart_time)
            time.sleep(.2)
        if button_lose == False:
            print 'Lose Trigger by GameMaster'
            player.set_position(loseStart_time)
            doorCheck = True
            redCheck = True
            endCheck = True
            time.sleep(.2)
        if button_RED == False and redCheck == False \
            and player.position() > RedAllowTalk:
            print 'THEY PRESSED THE RED BUTTON'
            tempTime = player.position()
            player.set_position(redbuttonStart_time)
            redCheck = True
            time.sleep(30)
            player.set_position(tempTime)
        if door_Switch == False and doorCheck == False:  # Makes sure that jumping here only triggers once
            print 'Door Switch Triggered, Entering Chamber Video'
            tempTime = player.position()
            GPIO.output(15, True)
            player.set_position(chamberStart_time)
            doorCheck = True
            time.sleep(arduino_delay)
            GPIO.output(15, False)
            if endCheck == True:
                time.sleep(81)
                player.set_position(tempTime)
            time.sleep(.2)  # 12 and 16
        if button_RED == False and redCheck == False \
            and player.position() > RedAllowTalk:
            print 'THEY PRESSED THE RED BUTTON'
            tempTime = player.position()
            player.set_position(redbuttonStart_time)
            redCheck = True
            time.sleep(30)
            player.set_position(tempTime)
        if player.position() > loseEnd_time and player.position() \
            < loseEnd_time + 4:  # Resets Game to intro
            print 'Video (LOSE) Ended, Resetting Back to Intro'
            resetCheck = True  # Make sure that it only resets once
        if player.position() > winEnd_time and player.position() \
            < winEnd_time + 4:
            print 'Video (WIN) Ended, Resetting Back to Intro'
            resetCheck = True
        if currentTime - startTime > 3000 and endCheck == False \
            and startCheck == True:  # If 50 minutes pass jump to ten minute segment
            print 'Ten Minutes Remaining by Raspberry'
            player.set_position(tenminStart_time)
            endCheck = True
            time.sleep(.2)
        if currentTime - startTime > 3600 and finalCheck == False \
            and startCheck == True:
            print 'Game end Trigger by Raspberry Clock'
            player.set_position(loseStart_time)
            finalCheck = True
            time.sleep(.2)
        if button_quit == False:
            cuFunctions.killall()
            print 'Force Close by GameMaster'
            break
        if time_increment == False:
            debug_offset += 60
            timeCheck = (currentTime - startTime + debug_offset) % 60
            print 'Time Incremented, %d seconds' % timeCheck
            time.sleep(.2)
        if time_decrement == False:
            debug_offset -= 60
            timeCheck = (currentTime - startTime  + debug_offset) % 60
            print 'Time Decremented, %d seconds' % timeCheck
            time.sleep(.2)
finally:
    print 'System Exit via GameMaster or Error'
    os.system('sudo killall omxplayer.bin')
    GPIO.cleanup()
