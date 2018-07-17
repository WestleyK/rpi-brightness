all: pi-brightness.c
	gcc -g -Wall -o rpi-brightness pi-brightness.c

install:
	cp rpi-brightness /usr/local/bin

clean:
	$(RM) rpi-brightness

uninstall:
	$(RM) /usr/local/bin/rpi-brightness
