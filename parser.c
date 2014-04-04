#include <stdio.h>
#include "mpc.h"

// Declare a static buffer for user input of maximum size 2048 
static char input[2048];

int main(int argc, char** argv) {

	// Print Version and Exit Information
	puts("Lispy Version 0.0.0.0.1");
	puts("Press Ctrl+c to Exit\n");

	while (1) {

		// Output prompt
		fputs("lispy> ", stdout);

		// Read a line of user input
		fgets(input, 2048, stdin);

		// Echo input back to user
		printf("Wow, %s", input);
	}

	return 0;
}