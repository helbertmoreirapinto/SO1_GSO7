#include <stdio.h>
#include <unistd.h>

int main() {
	int i = 6;

	pid_t pid = fork();
	pid_t process = getpid();
	
	printf("--------\n");
	printf("Processo atual: %d\n", process);

	if (!pid) {
		i -= 2;
		printf("Somente processo pai ID[%d] passa por este trecho\n", pid);
		printf("Thread pai vai dormir %d segundos\n", i);
		sleep(i);
	} else {
		i += 2;
		printf("Somente processo filho ID[%d] passa por este trecho\n", pid);
		printf("Thread filho vai dormir %d segundos\n", i);
		sleep(i);
	}
	printf("Programa ID[%d] vai finalizar\n", process);

	return 0;
}
