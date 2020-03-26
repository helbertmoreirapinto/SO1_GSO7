/*
 ============================================================================
 Description  : This is an example program that uses I/O in both standard and file input.
 Syscalls uses:
 open() - tries to open a file on disk.
 creat()- create a file on the disk.
 write()- write a fixed number of bytes to the output defined in the parameter.
 read() - read a fixed number of bytes from the input defined in the parameter.
 ============================================================================
 */
 
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERROR -1
#define MAX_BUFFER 50

/*------------------------------ MAIN -------------------------------*/
int main() {

	/* String pool */
	char name_file[] = "fileExampl.out";
	char msg_file[] = "text for example abc123\n\0";
	
	char msg_err1[] = "File not found\n\0";
	char msg_err2[] = "Trying create file\n\0";
	char msg_err3[] = "Failed to create file\n\0";
	char msg_err4[] = "Failed to open file\n\0";

	char msg_inf1[] = "Sucess!!!\n\0";
	char msg_inf2[] = "Writting in file\n\0";
	char msg_inf3[] = "Open file for write\n\0";
	char msg_inf4[] = "Open file for read\n\0";
	
	int ptr_file = open(name_file, O_WRONLY);
	
	if(ptr_file == ERROR){
		write(0, msg_err1, strlen(msg_err1));

		write(0, msg_err2, strlen(msg_err2));
		ptr_file = creat(name_file, 0755);
		if(ptr_file == ERROR){
			write(0, msg_err3, strlen(msg_err3));
			return ERROR;
		}

		write(0, msg_inf1, strlen(msg_inf1));
	}

	write(0, msg_inf3, strlen(msg_inf3));

	write(ptr_file, msg_file, MAX_BUFFER);
	
	write(0, msg_inf2, strlen(msg_inf2));

	close(ptr_file);

	char buffer[MAX_BUFFER];

	ptr_file = open(name_file, O_RDONLY);
	if(ptr_file == ERROR){
		write(0, msg_err4, strlen(msg_err4));
		return ERROR;
	}

	write(0, msg_inf4, strlen(msg_inf4));

	read(ptr_file , buffer, MAX_BUFFER);

	write(0, buffer, strlen(buffer));

	close(ptr_file);

	return 0;
}