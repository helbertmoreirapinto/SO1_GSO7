#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX_ITEMS  15
#define MAX_BUFFER 3

void* func_producer(void);
void* func_consumer(void);

int main(){
    pthread_t th_prod;
    pthread_t th_cons;

    if (pthread_create(&th_prod, 0, (void*) func_producer, (void*) 0)) { 
		printf("Erro ao criar produtor\n");
		exit(0); //exits if error
	}
	if (pthread_create(&th_cons, 0, (void*) func_consumer, (void*) 0)) { 
		printf("Erro ao criar consumidor\n");
		exit(0); //exits if error
	}

    pthread_join(th_prod, 0);
	pthread_join(th_cons, 0);
    return 0;
}

void* func_producer(void){
    pthread_exit(0);
}

void* func_consumer(void){
    pthread_exit(0);
}
