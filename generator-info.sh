#!/bin/sh
#
# Created by: Westley K
# email: westley@sylabs.io
# Date: Aug 22, 2018
# https://github.com/WestleyK/rpi-brightness
# Version-1.0.4
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



FILE_INFO="rpi_brightness_info.c"

DATE=` date `
WHO=` whoami `
ON=` hostname `
WHERE=` pwd `

touch $FILE_INFO
cat /dev/null > $FILE_INFO

cat << END_OF_FILE > $FILE_INFO

#include <stdio.h>

void info() {
    printf("Compiled date: $DATE\n");
    printf("Compiled by: $WHO\n");
    printf("Compiled on: $ON\n");
    printf("Compiled in: $WHERE\n");
    return;
}

END_OF_FILE




#
# End script
#


