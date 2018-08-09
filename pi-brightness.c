// Created by: Westley K
// email: westley@sylabs.io
// Date: Aug 8, 2018
// https://github.com/WestleyK/rpi-brightness
// Version-1.0.4
//
// Designed and tested for raspberry pi with official 7 inch touchdcreen. 
//
//
// MIT License
//
// Copyright (c) 2018 WestleyK
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>


#define VERSION "version-1.0.4"
#define DATE_MODIFIED "Aug 8, 2018"

#define BRIGHTNESS_FILE "/sys/class/backlight/rpi_backlight/brightness"
#define BACKLIGHT_POWER "/sys/class/backlight/rpi_backlight/bl_power"
#define ADJUST_UP 20
#define ADJUST_DOWN 20
#define BACKLIGHT_ON 0
#define BACKLIGHT_OFF 1
#define MIN_BRIGHTNESS 15 
#define MAX_BRIGHTNESS 255


void usage() {
	printf("Usage: rpi-backlight [OPTION]\n");
	printf("	-h | -help | --help (print help menu)\n");
	printf("	-u | -up (adjust backlight brighter by: %i/255\n", ADJUST_UP);
	printf("	-d | -down (adjust brightness lower by: %i/255\n", ADJUST_DOWN);
	printf("	-s | -sleep (enter sleep mode, press <ENTER> to exit)\n");
	printf("	-c (print current brightness)\n");
	printf("	[15-255] (adjust brightness from 15 to 255\n");
	printf("	-v | -version | --version (print version & date)\n");
	printf("Source code: https://github.com/WestleyK/rpi-brightness\n");
	exit(0);

}

void version_display() {
	printf("%s\n", VERSION);
	printf("%s\n", DATE_MODIFIED);
	exit(0);
}

void is_writable() {
	if (access(BRIGHTNESS_FILE, W_OK) != 0 ) {
		printf("\033[31;1m" "ERROR: " "\033[0m");
		printf("Brightness file not writable.\n");
		printf("Try: sudo rpi-brightness  (or)  https://github.com/WestleyK/rpi-brightness (for help)\n");
		exit(1);
	}
}

int current_brightness() {
	int NEW_BRIGHTNESS;
	FILE *GET_BRIGHTNESS;

	GET_BRIGHTNESS = fopen(BRIGHTNESS_FILE, "r+");
	fscanf(GET_BRIGHTNESS, "%d", &NEW_BRIGHTNESS);
	fclose(GET_BRIGHTNESS);
	return(NEW_BRIGHTNESS);
}

void set_brightness(int NEW_BRIGHTNESS) {
	FILE *GET_BRIGHTNESS;
	if (NEW_BRIGHTNESS >= MAX_BRIGHTNESS) {
		NEW_BRIGHTNESS = MAX_BRIGHTNESS;
		printf("Max brightness\n");
	} else if (NEW_BRIGHTNESS <= MIN_BRIGHTNESS) {
		NEW_BRIGHTNESS = MIN_BRIGHTNESS;
		printf("Min brightness\n");
	}
	GET_BRIGHTNESS = fopen(BRIGHTNESS_FILE, "w");
	fprintf(GET_BRIGHTNESS, "%d", NEW_BRIGHTNESS);
	fclose(GET_BRIGHTNESS);
	printf("Current brightness: %d\n", NEW_BRIGHTNESS);
	return;
}

void adjust_up() {
	is_writable();
	set_brightness(current_brightness() + ADJUST_UP);
	exit(0);
}

void adjust_down() {
	is_writable();
	set_brightness(current_brightness() - ADJUST_DOWN);
	exit(0);
}

void sleep_mode() {
	is_writable();
	char BRIGHTNESS_IN[20];
	printf("Press <ENTER> to exit this mode:\n");
	sleep(1);
	FILE *WRITE_ON_OFF;
	WRITE_ON_OFF = fopen(BACKLIGHT_POWER, "w");
	fprintf(WRITE_ON_OFF, "%d", BACKLIGHT_OFF);
	fclose(WRITE_ON_OFF);
	fgets(BRIGHTNESS_IN, 20, stdin);
	WRITE_ON_OFF = fopen(BACKLIGHT_POWER, "w");
	fprintf(WRITE_ON_OFF, "%d", BACKLIGHT_ON);
	fclose(WRITE_ON_OFF);
	exit(0);
}

void option_c() {
	int MAX_BUFF = 1000;
	char CUR_BRIGHT[MAX_BUFF];
	FILE *BRIGHTNESS_READ;
	BRIGHTNESS_READ = fopen(BRIGHTNESS_FILE, "r");
	fgets(CUR_BRIGHT, MAX_BUFF, BRIGHTNESS_READ);
	printf("Scale [15-255]:\n");
	printf("%s", CUR_BRIGHT);
	fclose(BRIGHTNESS_READ);
	exit(0);
}

void adjust_brightness(char* argv) {
	int i;
	// check if input contains any letter
	for (i = 0; i < strlen(argv) - 1; i++) {
		if (argv[i] >= '0' && argv[i] <= '9') {
			//printf("%c\n", IS_VALID[i]);
		} else {
			printf("Character is not a digit: '%c'\n", argv[i]);
			exit(1);;
		}
	}
	// convert string to int
	int BRIGHTNESS = atoi(argv);

	// check if its within range
	if ((BRIGHTNESS < MIN_BRIGHTNESS) || (BRIGHTNESS > MAX_BRIGHTNESS)) {
		printf("Value is out of range: %d\n", BRIGHTNESS);
		exit(1);
	}
	// check if file is writable
	is_writable();
	// write to brightness file
	FILE *BACKLIGHT_FILE;
	BACKLIGHT_FILE = fopen(BRIGHTNESS_FILE, "w");
	fprintf(BACKLIGHT_FILE, "%d", BRIGHTNESS);
	fclose(BACKLIGHT_FILE);
    	exit(0);
}


int main(int argc, char** argv) {

	// check if more than one argument
	if (argc > 2) {
		printf("Only one argument! :P\n");
		exit(1);
	}

	// if theres one, than what is it
	if (argc >= 2) {

		// if -help option
		if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "-help") == 0) || (strcmp(argv[1], "--help") == 0)) {
			usage();
			return 0;
		// if -up option
		} else if ((strcmp(argv[1], "-u") == 0) || (strcmp(argv[1], "-up") == 0)) {
			adjust_up();
			return 0;
		// if -down option
		} else if ((strcmp(argv[1], "-d") == 0) || (strcmp(argv[1], "-down") == 0)) {
			adjust_down();
			return 0;
		// if -sleep option
		} else if ((strcmp(argv[1], "-s") == 0) || (strcmp(argv[1], "-sleep") == 0)) {
			sleep_mode();
			return 0;
		// if -c option
		} else if (strcmp(argv[1], "-c") == 0) {
			option_c();
			return 0;
		// if -version option
		} else if ((strcmp(argv[1], "-v") == 0) || (strcmp(argv[1], "-version") == 0) || (strcmp(argv[1], "--version") == 0)) {
			version_display();
			return 0;
		// or if its a number
		} else if (isdigit(*argv[1])) {
			adjust_brightness(argv[1]);
		} else {
			printf("Option not found :P  %s\n", argv[1]);
			printf("Try: rpi-brightness -help\n");
			return EXIT_FAILURE;
		}
    		return 0;
	}
	// if no arguments, than offer to change brightness
	char BRIGHTNESS_IN[20];
	printf("[15-255]:");
	fgets(BRIGHTNESS_IN, 20, stdin);
	adjust_brightness(BRIGHTNESS_IN);
	return 0;
}





// 
// End Script
//



