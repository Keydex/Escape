from pyomxplayer import OMXPlayer
from pprint import pprint

omx = OMXPlayer('/home/pi/Documents/Cabin-WIN.mp4')
omx.toggle_pause()
omx.position
omx.stop()
