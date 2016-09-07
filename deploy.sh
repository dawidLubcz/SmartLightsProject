#!/usr/bin/expect -f
spawn scp -r raspberry_debug/ pi@192.168.1.200:/home/pi
expect "password:"
send "raspberry\r"
interact
