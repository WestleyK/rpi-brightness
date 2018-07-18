all: pi-brightness.c
	gcc -g -o rpi-brightness pi-brightness.c

install:
	cp rpi-brightness /usr/local/bin

update:
	git pull origin master
	gcc -g -o rpi-brightness pi-brightness.c
	cp -f rpi-brightness /usr/local/bin

uninstall:
	$(RM) /usr/local/bin/rpi-brightness
