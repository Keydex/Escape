#This is the functions file for the cuaVideos

import os
def test():
	print('Function Call Success')

def killall():
    print('Exit Via button_off')
    os.system('sudo killall omxplayer.bin')
    return
#Video Functions
# def loopvideo(player()):
# 	player.set_position(0)
# 	print('Error Code #A01')
# 	while(True):
# 		print('Error Code #A02')
# 		if(player.position() > 10):#Seconds until the system loops back to 0
# 			print('Loop Triggered by System')
# 			player.set_position(0)
# 			print('Error Code #A03')
# 			time.sleep(1)
# 		if(button_start == False):#When start pressed, game starts, then break out of loopvideo function
# 			print('Game Start Triggered by GameMaster')
# 			print('Error Code #A04')
# 			player.set_position(600)
# 			time.sleep(1)
# 			return#Use return not break