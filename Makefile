# Created by: Westley K
# email: westley@sylabs.io
# Date: Aug 26, 2018
# https://github.com/WestleyK/rpi-brightness
# Version-1.1.1
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
INFO_NAME = rpi_brightness_info.c
INFO_GEN = generator-info.sh
SCRIPT_NAME = rpi-brightness
INSTALL_TO = /usr/local/bin/


all: $(CODE_NAME)
	@./$(INFO_GEN)
	@echo "Compileing code..."
	@gcc $(CODE_NAME) $(INFO_NAME) -o $(SCRIPT_NAME)
	@rm -f $(INFO_NAME)
	@echo "Done."
	@echo ">> Do:"
	@echo "  $$ sudo make install"

install:
	chmod +x $(SCRIPT_NAME)
	cp -f $(SCRIPT_NAME) $(INSTALL_TO)

update:
	rm -f $(SCRIPT_NAME)
	git pull origin master

uninstall:
	rm $(INSTALL_TO)$(SCRIPT_NAME)



#
# End Makefile
#

