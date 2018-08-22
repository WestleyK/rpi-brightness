# Created by: Westley K
# email: westley@sylabs.io
# Date: Aug 22, 2018
# https://github.com/WestleyK/rpi-brightness
# Version-1.1.4
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

CODE_NAME = pi-brightness.c
SCRIPT_NAME = rpi-brightness
INSTALL_TO = /usr/local/bin/

DATE := "$(shell date)"
WHO := "$(shell whoami)"
ON := "$(shell hostname)"
WHERE := "$(shell pwd)"

COMPILE_DATE = -D DATE=\"$(DATE)\"
COMPILE_WHO = -D WHO=\"$(WHO)\"
COMPILE_ON = -D ON=\"$(ON)\"
COMPILE_WHERE = -D WHERE=\"$(WHERE)\"

COMPILE_ALL = $(COMPILE_DATE) $(COMPILE_WHO) $(COMPILE_ON) $(COMPILE_WHERE)

all: pi-brightness.c
	@echo "Compileing code..."
	@gcc $(COMPILE_ALL) $(CODE_NAME) -o $(SCRIPT_NAME)
	@echo "Done."
	@echo " => Do:"
	@echo "  $$ sudo make install"

install:
	chmod +x $(SCRIPT_NAME)
	cp $(SCRIPT_NAME) $(INSTALL_TO)

update:
	rm -f $(SCRIPT_NAME)
	git pull origin master

uninstall:
	rm $(INSTALL_TO)$(SCRIPT_NAME)


#
# End Makefile
#


