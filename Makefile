# Created by: Westley K
# email: westley@sylabs.io
# Date: Aug 21, 2018
# https://github.com/WestleyK/rpi-brightness
# Version-1.0.8
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


all: pi-brightness.c
	./generator-info.sh
	gcc pi-brightness.c rpi_brightness_info.c -o rpi-brightness
	rm -f rpi_brightness_info.c

install:
	chmod +x rpi-brightness
	cp rpi-brightness /usr/local/bin
	mv rpi_brightness_info.txt /usr/local/share/

update:
	git pull origin master

uninstall:
	rm /usr/local/bin/rpi-brightness
	rm /usr/local/share/rpi_brightness_info.txt


#
# End Makefile
#

