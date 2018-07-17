// Created by: Westley K
// Date: Jul 17, 2018
// https://github.com/WestleyR/pi-backlight-c
// Version-1.0-beta-1
//
// Designed and tested for raspberry pi with official 7 inch touchdcreen. 
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>


#define VERSION "1.0-beta-1"

#define BRIGHTNESS_FILE "/sys/class/backlight/rpi_backlight/brightness"
#define BACKLIGHT_POWER "/sys/class/backlight/rpi_backlight/bl_power"

int MIN_BRIGHTNESS = 15;
int MAX_BRIGHTNESS = 255;
int BRIGHTNESS;
int ADJUST_BACKLIGHT = 0;
char BRIGHTNESS_IN[20];



void usage() {
	printf("Usage: <COMMAND> [OPTION]\n");
	printf("	-h | -help | --help (print help menu)\n");
	printf("	[15-255] (adjust brightness from 15 to 255\n");
	printf("	-v | -version | --version (print version)\n");
	printf("Source code: https://github.com/WestleyR/pi-backlight-c\n");
	exit(0);

}



int main(int argc, char* argv[]) {

	// check if more than one argument
	if (argc > 2) {
		printf("Only one argument! :P\n");
		exit(0);
	}

	// if theres one, than what is it
	if (argc >= 2) {

		// if -help option
		if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "-help") == 0) || (strcmp(argv[1], "--help") == 0)) {
			usage();
			return 0;
		// if -version option
		} else if ((strcmp(argv[1], "-v") == 0) || (strcmp(argv[1], "-version") == 0) || (strcmp(argv[1], "--version") == 0)) {
			printf("%s\n", VERSION);
			return 0;
		// or if its a number
		} else if (isdigit(*argv[1])) {
			ADJUST_BACKLIGHT = 1;
		} else {
			printf("Option not found :P\n");
			printf("Try: <COMMAND> -help\n");
			return EXIT_FAILURE;
		}

		// do we need to adjust
		if (ADJUST_BACKLIGHT == 1) {
			// check if there a decimal
			if (strstr(argv[1], ".") != 0) {
				printf("Only whole numbers!\n");
				return EXIT_FAILURE;
			}
			// convert string to int
			BRIGHTNESS = atoi(argv[1]);
			// check if its within range
			if ((BRIGHTNESS < MIN_BRIGHTNESS) || (BRIGHTNESS > MAX_BRIGHTNESS)) {
				printf("Not valid number\n");
				return EXIT_FAILURE;
			}
			// check if file is writable
			if (access(BRIGHTNESS_FILE, W_OK) != 0 ) {
				printf("\033[31;1m" "ERROR: " "\033[0m");
				printf("Brightness file not writable.\n");
				printf("Try sudo <COMMAND>  (or)  https://github.com/WestleyR/pi-backlight-c (for help)\n");
				return EXIT_FAILURE;
			}

			// write to brightness file
			FILE *BACKLIGHT_FILE;
			BACKLIGHT_FILE = fopen(BRIGHTNESS_FILE, "w");
			fprintf(BACKLIGHT_FILE,"%d", BRIGHTNESS);
			fclose(BACKLIGHT_FILE);

    			return EXIT_SUCCESS;
		}
	}


	// if no arguments, than offer to change brightness
	printf("[15-255]:");
	fgets(BRIGHTNESS_IN, 20, stdin);
	if (strstr(BRIGHTNESS_IN, ".") != 0 ) {
		printf("Only whole number!\n");
		return EXIT_FAILURE;
	}

	// again, convert string to int
	BRIGHTNESS = atoi(BRIGHTNESS_IN);
	// check is its within range
	if ((BRIGHTNESS < MIN_BRIGHTNESS) || (BRIGHTNESS > MAX_BRIGHTNESS)) {
		printf("Not a valid number!\n");
		return EXIT_FAILURE;
	}

	// check if file is writable
	if (access(BRIGHTNESS_FILE, W_OK) != 0 ) {
		printf("\033[31;1m" "ERROR: " "\033[0m");
		printf("Brightness file not writable.\n");
		printf("Try sudo <COMMAND>  (or)  https://github.com/WestleyR/pi-backlight-c (for help)\n");
		return EXIT_FAILURE;
	}

	// write to file
	FILE *BACKLIGHT_FILE;
	BACKLIGHT_FILE = fopen(BRIGHTNESS_FILE, "w");
	fprintf(BACKLIGHT_FILE,"%d", BRIGHTNESS);
	fclose(BACKLIGHT_FILE);



    
    return 0;
}





// 
// End Script
//



