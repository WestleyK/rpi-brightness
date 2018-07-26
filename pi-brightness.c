// Created by: Westley K
// Date: Jul 26, 2018
// https://github.com/WestleyK/rpi-brightness
// Version-1.0.1
//
// Designed and tested for raspberry pi with official 7 inch touchdcreen. 
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define VERSION "version-1.0.1"
#define DATE_MODIFIED "Jun 26, 2018"

#define BRIGHTNESS_FILE "/sys/class/backlight/rpi_backlight/brightness"
#define BACKLIGHT_POWER "/sys/class/backlight/rpi_backlight/bl_power"
#define ADJUST_UP 20
#define ADJUST_DOWN 20
#define BACKLIGHT_ON 0
#define BACKLIGHT_OFF 1

int MIN_BRIGHTNESS = 15;
int MAX_BRIGHTNESS = 255;
int BRIGHTNESS;
int ADJUST_BACKLIGHT = 0;
char BRIGHTNESS_IN[20];

void usage() {
	printf("Usage: rpi-backlight [OPTION]\n");
	printf("	-h | -help | --help (print help menu)\n");
	printf("	-u | -up (adjust backlight brighter by 20/255\n");
	printf("	-d | -down (adjust brightness lower by 20/255\n");
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

void adjust_up() {
	if (access(BRIGHTNESS_FILE, W_OK) != 0 ) {
		printf("\033[31;1m" "ERROR: " "\033[0m");
		printf("Brightness file not writable.\n");
		printf("Try: sudo rpi-brightness  (or)  https://github.com/WestleyK/rpi-brightness (for help)\n");
		exit(0);
	}
	int NEW_BRIGHTNESS;
	FILE *GET_BRIGHTNESS;
	GET_BRIGHTNESS = fopen(BRIGHTNESS_FILE, "r+");
	fscanf(GET_BRIGHTNESS, "%d", &NEW_BRIGHTNESS);
	NEW_BRIGHTNESS += ADJUST_UP;
	if (NEW_BRIGHTNESS >= MAX_BRIGHTNESS) {
		NEW_BRIGHTNESS = MAX_BRIGHTNESS;
		printf("Max brightness\n");
	}
	fprintf(GET_BRIGHTNESS, "%d", NEW_BRIGHTNESS);
	fclose(GET_BRIGHTNESS);
	printf("Current brightness:");
	printf("%d\n", NEW_BRIGHTNESS);
	exit(0);
}

void adjust_down() {
	if (access(BRIGHTNESS_FILE, W_OK) != 0 ) {
		printf("\033[31;1m" "ERROR: " "\033[0m");
		printf("Brightness file not writable.\n");
		printf("Try: sudo rpi-brightness  (or)  https://github.com/WestleyK/rpi-brightness (for help)\n");
		exit(0);
	}
	int NEW_BRIGHTNESS;
	FILE *GET_BRIGHTNESS;
	GET_BRIGHTNESS = fopen(BRIGHTNESS_FILE, "r+");
	fscanf(GET_BRIGHTNESS, "%d", &NEW_BRIGHTNESS);
	NEW_BRIGHTNESS -= ADJUST_UP;
	if (NEW_BRIGHTNESS <= MIN_BRIGHTNESS) {
		NEW_BRIGHTNESS = MIN_BRIGHTNESS;
		printf("Min brightness\n");
	}
	fprintf(GET_BRIGHTNESS, "%d", NEW_BRIGHTNESS);
	fclose(GET_BRIGHTNESS);
	printf("Current brightness:");
	printf("%d\n", NEW_BRIGHTNESS);
	exit(0);
}

void sleep_mode() {
	if (access(BRIGHTNESS_FILE, W_OK) != 0 ) {
		printf("\033[31;1m" "ERROR: " "\033[0m");
		printf("Brightness file not writable.\n");
		printf("Try: sudo rpi-brightness  (or)  https://github.com/WestleyK/rpi-brightness (for help)\n");
		exit(0);
	}
	printf("Press ENTER to exit this mode:\n");
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
			ADJUST_BACKLIGHT = 1;
		} else {
			printf("Option not found :P\n");
			printf("Try: rpi-brightness -help\n");
			return EXIT_FAILURE;
		}

		// do we need to adjust
		if (ADJUST_BACKLIGHT == 1) {
			// check if theres a decimal, this part is not needed
			if (strstr(argv[1], ".") != 0) {
				printf("Only whole numbers!\n");
				return EXIT_FAILURE;
			}
			// check if input contains any letter
			char *IS_VALID = argv[1];
			int i;
			for (i = 0; i < strlen(IS_VALID); i++) {
				if (IS_VALID[i] >= '0' && IS_VALID[i] <= '9') {
					//printf("%c\n", IS_VALID[i]);
				} else {
					printf("Only number input!\n");
					return EXIT_FAILURE;
				}
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
				printf("Try: sudo rpi-brightness  (or)  https://github.com/WestleyK/rpi-brightness (for help)\n");
				return EXIT_FAILURE;
			}

			// write to brightness file
			FILE *BACKLIGHT_FILE;
			BACKLIGHT_FILE = fopen(BRIGHTNESS_FILE, "w");
			fprintf(BACKLIGHT_FILE, "%d", BRIGHTNESS);
			fclose(BACKLIGHT_FILE);

    			return EXIT_SUCCESS;
		}
	}


	// if no arguments, than offer to change brightness
	printf("[15-255]:");
	fgets(BRIGHTNESS_IN, 20, stdin);
	// check if theres a decimal
	if (strstr(BRIGHTNESS_IN, ".") != 0 ) {
		printf("Only whole numbers!\n");
		return EXIT_FAILURE;
	}
	// check if theres a comma
	if (strstr(BRIGHTNESS_IN, ",") != 0) {
		printf("Only whole numbers!\n");
		return EXIT_FAILURE;
	}
	// check if input contains any letter
	char *IS_VALID = BRIGHTNESS_IN;
	int i;
	for (i = 0; i < (strlen(IS_VALID) -1 ); i++) {
		if (IS_VALID[i] >= '0' && IS_VALID[i] <= '9') {
			//printf("%c\n", IS_VALID[i]);
		} else {
			printf("Only number input!\n");
			return EXIT_FAILURE;
		}
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
		printf("Try: sudo rpi-brightness  (or)  https://github.com/WestleyK/rpi-brightness (for help)\n");
		return EXIT_FAILURE;
	}

	// write to file
	FILE *BACKLIGHT_FILE;
	BACKLIGHT_FILE = fopen(BRIGHTNESS_FILE, "w");
	fprintf(BACKLIGHT_FILE, "%d", BRIGHTNESS);
	fclose(BACKLIGHT_FILE);


	return 0;
}





// 
// End Script
//



