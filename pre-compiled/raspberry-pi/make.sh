#!/bin/sh
# Created by: Westley K
# email: westley@sylabs.io
# Date: Aug 26, 2018
# version-1.0.1
# https://github.com/WestleyK/rpi-brightness
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


SCRIPT_VERSION="version-1.0.0"
SCRIPT_DATE="Aug 26, 2018"

# the name of the script to install,
SCRIPT_NAME="rpi-brightness"

# the place where the script will be installed
PATH_INSTALL="/usr/local/bin/"

# supported for kernel version
SUP_KER="4.14.50-v7+"

OPTION=$1

help_menu() {
	echo "Usage: ./make.sh [OPTION]"
	echo "      help (print help menu)"
	echo "      install (install: $SCRIPT_NAME to: $PATH_INSTALL)"
	echo "      update (update command and repo)"
	echo "      uninstall (uninstall: $SCRIPT_NAME from: $PATH_INSTALL)"
    echo "      info (print info)"
	echo "      version (print version of install script)"
	echo "Sorce code: https://github.com/WestleyK/rpi-brightness"
	exit 0
}

info() {
    echo "Supported for kernel version: $SUP_KER"
    exit 0
}

script_version() {
	echo "$SCRIPT_VERSION"
	echo "$SCRIPT_DATE"
	exit 0
}

is_sudo() {
	IS_ROOT=$( id -u )
	if [ $IS_ROOT != 0 ]; then
		echo "Please run as root!"
		echo "try: sudo ./install.sh"
		exit
	fi
}

kernel_version() {
    # supported for: 4.14.50-v7+
    KERNEL_V=` uname -r `
    if [ "$KERNEL_V" != "$SUP_KER" ]; then
        printf "\033[0;31mABORTING!\033[0m\n"
        echo "Kernel wrong version!"
        echo "Supported version: $SUP_KER"
        echo "Your version: $KERNEL_V"
        echo "Install failed."
        exit 1
    fi
}

install_script() {
	is_sudo
	if [ ! -e $SCRIPT_NAME ]; then
		echo "$SCRIPT_NAME is not in this directory :O"
		exit 1
	fi
	if [ -e $PATH_INSTALL$SCRIPT_NAME ]; then
		printf "\033[0;33mWARNING: \033[0m\n"
		echo "$SCRIPT_NAME is already installed to: $PATH_INSTALL"
		echo "Continuing will overide the existing script"
		echo "Do you want to continue?"
		echo -n "[y,n]:"
		read INPUT
		if [ "$INPUT" = "y" ] || [ "$INPUT" = "Y" ]; then
			echo "Overriding existing file..."
		else
            printf "\033[0;31mABORTING!\033[0m\n"
			echo "Install failed."
			exit 1
		fi
	fi
    echo "Checking kernel version..."
    kernel_version
    echo "Kernel version: $KERNEL_V"
	echo "Installing: $SCRIPT_NAME"
	chmod +x $SCRIPT_NAME
	cp $SCRIPT_NAME $PATH_INSTALL
	echo "$SCRIPT_NAME installed to: $PATH_INSTALL"
    printf "\033[0;32mSUCCESS!\033[0m\n"
    echo "Install success."
	echo "Done."
	exit 0
}

update_script() {
	is_sudo
	echo "Updating..."
	git pull origin master
	install_script
}

uninstall_script() {
	if [ ! -e $INSTALL_PATH$SCRIPT_NAME ]; then
		echo "$SCRIPT_NAME is not installed :O"
		exit 1
	fi
	echo "Uninstalling" $SCRIPT_NAME "from" $PATH_INSTALL
	rm $PATH_INSTALL$SCRIPT_NAME
	echo "Done."
	exit 0
}

# is there a argument, than what is it?
if [ ! -z $OPTION ]; then
	if [ "$OPTION" = "help" ]; then
		help_menu
	elif [ "$OPTION" = "install" ]; then
		install_script
	elif [ "$OPTION" = "update" ]; then
		update_script
	elif [ "$OPTION" = "uninstall" ]; then
		uninstall_script
	elif [ "$OPTION" = "info" ]; then
		info
	elif [ "$OPTION" = "version" ]; then
		script_version
	else
		echo "Option not found: $OPTION"
		echo "Try: ./make.sh help"
	fi
else
	help_menu
fi



#
# End install script
#


