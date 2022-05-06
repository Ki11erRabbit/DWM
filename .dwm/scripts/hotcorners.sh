#!/bin/sh

##--Left--##

#xdotool behave_screen_edge --quiesce 1000 bottom-left \
#	exec kitty nnn -c -a -P p & 
xdotool behave_screen_edge --delay 150 --quiesce 2000 bottom-left \
	exec thunar &

##--Right--##

xdotool behave_screen_edge --delay 150 --quiesce 1000 top-right \
	exec kill -s USR1 $(pidof deadd-notification-center) &

xdotool behave_screen_edge --delay 150 bottom-right \
	exec panther_launcher &


