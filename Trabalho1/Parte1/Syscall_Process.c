/*
 ============================================================================
 Description  : Example of bifurcation of processes and opening of one
 				process by another.
 Syscalls uses:
 fork()  - It makes a fork in the process.
 sleep() - Pause the thread for n seconds.
 system()- Run a program command on the system terminal.
 wait()  - Used to synchronize threads.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 

int main() {
	char* args[] = {"", "10", NULL};
	int i = 6;
	
	pid_t core_process = getpid();
	printf("Processo Core: %d\n\n", core_process);

	pid_t pid = fork();
	
	pid_t atual_process = getpid();
	
	printf("--------\n");
	printf("Processo Atual: %d \n", atual_process);

	if (pid) {
		i -= 2;
		printf("Processo pai. ID do filho = %d\n", pid);
		
		printf("Thread pai vai dormir %d segundos\n", i);
		sleep(i);
		printf("Thread pai acordou e inicia programa exemplo 1\n");
		system("./ProgramExample1 12");

	} else {
		i += 2;
		printf("Processo filho. ID = %d\n", pid);
		printf("Thread filho vai dormir %d segundos\n", i);
		sleep(i);
		printf("Thread filho acordou e inicia programa exemplo 2\n");

		system("./ProgramExample2 12");
	}

	printf("Processo ID[%d] vai finalizar\n\n", atual_process);
	wait(NULL);
	
	return 0;
}
