#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	int pid;
	int i = 0;
	pid = fork();

	if (!pid) {
		i++;
		printf("Processo pai i[%d]\n", i);
	} else {
		printf("Processo filho id[%d] i[%d]\n", pid, i);
	}
	printf("AQUI\n");

	return EXIT_SUCCESS;
}
