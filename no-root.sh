#!/bin/bash
#
# Created by: Westley K
# email: westley@sylabs.io
# Date: Jul 29, 2018
# https://github.com/WestleyK/rpi-brightness
# Version-1.0.0
#
# Designed and tested for raspberry pi with official 7 inch touchdcreen. 
#
#
# MIT License
#
# Copyright (c) 2018 WestleyK
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#



# check if root
IS_ROOT=$( id -u )
if [ $IS_ROOT != 0 ]; then
	echo "Please run as root!"
	echo "try: sudo ./no-root.sh"
	exit
fi

touch /etc/udev/rules.d/backlight-permissions.rules
echo "SUBSYSTEM==\"backlight\",RUN+=\"/bin/chmod 666 /sys/class/backlight/%k/brightness /sys/class/backlight/%k/bl_power\"" > /etc/udev/rules.d/backlight-permissions.rules


#
# End script
#

