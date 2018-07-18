all: pi-brightness.c
	gcc -g -Wall -o rpi-brightness pi-brightness.c

install:
	cp rpi-brightness /usr/local/bin

uninstall:
	$(RM) /usr/local/bin/rpi-brightness
