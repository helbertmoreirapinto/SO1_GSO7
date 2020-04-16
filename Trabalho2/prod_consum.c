#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX_ITEMS  15
#define MAX_BUFFER 3

void* func_producer(void);
void* func_consumer(void);
void produce_item(int item);
int consume_item();
void process_item(int item);

pthread_cond_t cond_buffer_empty, cond_buffer_full;
pthread_mutex_t atomic_process_lock;
int buffer[MAX_BUFFER];
int idx_buffer; //semaphore
int produced_items, consumed_items;

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
    while(produced_items < MAX_ITEMS){
        pthread_mutex_lock(&atomic_process_lock);
        while (idx_buffer == MAX_BUFFER)
            pthread_cond_wait(&cond_buffer_empty, &atomic_process_lock);
        produce_item(123);
        pthread_cond_signal(&cond_buffer_full);
        pthread_mutex_unlock(&atomic_process_lock);
    }
    pthread_exit(0);
}

void* func_consumer(void){
    int elem;
    while(consumed_items < MAX_ITEMS){
        pthread_mutex_lock(&atomic_process_lock);
        while (!idx_buffer)
            pthread_cond_wait(&cond_buffer_full, &atomic_process_lock);
        elem = consume_item();
        pthread_cond_signal(&cond_buffer_empty);
        pthread_mutex_unlock(&atomic_process_lock);
        process_item(elem);
    }
    pthread_exit(0);
}

void produce_item(int item){
    produced_items++;
    buffer[idx_buffer++] = item;
}

int consume_item(){
    consumed_items++;
    return buffer[--idx_buffer];
}

void process_item(int item){
    static int processed_item = 0;
    printf("processed item:%02d value:%d\n", ++processed_item, item);
}