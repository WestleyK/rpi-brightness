#!/bin/sh
#
# Created by: Westley K
# Date: Jul 25, 2018
# version-1.0
# https://github.com/WestleyK/rpi-brightness
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

