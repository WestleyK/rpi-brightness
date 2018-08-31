#!/bin/sh
# Created by: Westley K
# email: westley@sylabs.io
# Date: Aug 31, 2018
# version-1.0.4
# https://github.com/WestleyK/rpi-brightness
#
# MIT License
#

SCRIPT_VERSION="version-1.0.4"
SCRIPT_DATE="Aug 31, 2018"

SCRIPT_NAME="rpi-brightness"

PATH_INSTALL="/usr/local/bin/"

SUP_ARCH="armv7l"

OPTION=$1

help_menu() {
	echo "Usage: ./make.sh [OPTION]"
	echo "      help (print help menu)"
	echo "      install (install: $SCRIPT_NAME to: $PATH_INSTALL)"
	echo "      uninstall (uninstall: $SCRIPT_NAME from: $PATH_INSTALL)"
	echo "      info (print info)"
	echo "      version (print version of install script)"
	echo "Sorce code: https://github.com/WestleyK/rpi-brightness"
	exit 0
}

info() {
    echo "Supported for arch: $SUP_ARCH"
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

arch_version() {
    # supported for: arm7l
    ARCH_V=` uname -m `
    if [ "$ARCH_V" != "$SUP_ARCH" ]; then
        printf "\033[0;31mFATAL ERROR: \033[0m"
        echo "Kernel wrong version!"
        echo "Supported version: $SUP_ARCH"
        echo "Your version: $ARCH_V"
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
    echo "Checking architecture..."
    arch_version
    echo "Your architecture: $ARCH_V"
	echo "Installing: $SCRIPT_NAME"
	chmod +x $SCRIPT_NAME
	cp $SCRIPT_NAME $PATH_INSTALL
	echo "$SCRIPT_NAME installed to: $PATH_INSTALL"
    printf "\033[0;32mSUCCESS!\033[0m\n"
    echo "Install success."
	echo "Done."
	exit 0
}

uninstall_script() {
	if [ ! -e $INSTALL_PATH$SCRIPT_NAME ]; then
		echo "$SCRIPT_NAME is not installed :O"
		exit 1
	fi
	echo "Uninstalling" $SCRIPT_NAME "from" $PATH_INSTALL
	rm -f $PATH_INSTALL$SCRIPT_NAME
	echo "Done."
	exit 0
}

if [ ! -z $OPTION ]; then
	if [ "$OPTION" = "help" ]; then
		help_menu
	elif [ "$OPTION" = "install" ]; then
		install_script
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
