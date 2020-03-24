/*
 ============================================================================
 Title: Program 1
 Description  : This is an example program that uses I/O in both standard and file input.
 Syscalls uses: open()
 read()
 write()
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

/*---------------------------- FUNCTIONS ----------------------------*/
const char* read_standard_input();
void write_standard_input(const char*);
const char* read_file_input();
void write_file_input(const char*);

/*------------------------------ MAIN -------------------------------*/
int main() {

	char text[] = "text example\0";

//	read_standard_input();

	write_standard_input(text);

//	read_file_input();

//	write_file_input(text);

	return EXIT_SUCCESS;
}

/*---------------------------- FUNCTIONS ----------------------------*/
const char* read_standard_input() {
	int ret, nBytes = 10;
	char buffer[nBytes];

	while (true) {
		ret = read(0, buffer, nBytes - 1);
		buffer[ret] = '\0';
		if (ret < (nBytes - 1)) {
			printf("%s", buffer);
			break;
		} else {
			printf("%s\n", buffer);
		}
	}
	return NULL;
}

const char* read_file_input() {
	int ret, nBytes = 10;
	char buffer[nBytes];

	while (true) {
		ret = read(0, buffer, nBytes - 1);
		buffer[ret] = '\0';
		if (ret < (nBytes - 1)) {
			printf("%s", buffer);
			break;
		} else {
			printf("%s\n", buffer);
		}
	}
	return NULL;
}

void write_standard_input(const char* text) {
	int tam = strlen(text);
	write(0, text, tam);
}

void write_file_input(const char* text) {

}
