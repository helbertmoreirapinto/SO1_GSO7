#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SECOND 60

int main(void) {
	int pid;
	int i = 6;

	pid = fork();
	pid_t process = getpid();

	if (!pid) {
		i += 3;
		printf("--------\n");
		printf("Somente processo pai ID[%d] passa por este trecho\n", pid);
		printf("Thread pai vai dormir %d segundos\n", i);
		sleep(i);

	} else {
		i -= 3;
		printf("--------\n");
		printf("Somente processo filho ID[%d] passa por este trecho\n", pid);
		printf("Thread filho vai dormir %d segundos\n", i);
		sleep(i);
	}

	printf("Programa ID[%d] vai finalizar\n", pid);


	return EXIT_SUCCESS;
}
