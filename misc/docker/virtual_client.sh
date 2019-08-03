#!/bin/bash

export DISPLAY=:4000

/usr/bin/Xvfb $DISPLAY -screen 0 1000x600x24 -dpi 70 -ac +extension RANDR & echo $! > /tmp/xvfb.pid

sleep 1
/usr/bin/xinit -display $DISPLAY & echo $! > /tmp/x11.pid

sleep 1
/usr/lib/ioquake3/ioquake3 --args +set fs_game missionpack +exec ./client.cfg & echo $! > /tmp/xterm.pid

sleep 1
/usr/bin/x11vnc -scale 1000x600 -noxdamage -forever -shared -rfbport 5900 -display $DISPLAY -noxrecord & echo $! > /tmp/vnc.pid

int_handler()
{
    kill $(cat /tmp/xterm.pid) 2> /dev/null
    kill $(cat /tmp/vnc.pid)
    kill $(cat /tmp/x11.pid)
    kill $(cat /tmp/xvfb.pid)
}

trap 'int_handler' INT

wait $(cat /tmp/xterm.pid)
int_handler
