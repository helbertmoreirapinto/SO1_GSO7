//----------------------------------IMPORTS---------------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//----------------------------------DEFINES---------------------------------//
#define MAX_ITEMS 30
#define MAX_BUFFER 10
#define MAX_ITEM_VALUE 100
#define MILLISEC 1000

//---------------------------------FUNCTIONS--------------------------------//
void* func_producer(void);
void* func_consumer(void);
void produce_item(int item);
int consume_item();
void process_item(int item);
int random_item();

//-----------------------------GLOBALS VARIABLES----------------------------//
pthread_cond_t cond_buffer_empty, cond_buffer_full;
pthread_mutex_t atomic_process_lock;
int buffer[MAX_BUFFER];
int idx_buffer; //semaphore
int produced_items, consumed_items;

//-----------------------------------MAIN-----------------------------------//
int main(){
    //Change seed to make items random
    srand (time(NULL));
    
    //Threads
    pthread_t th_prod;
    pthread_t th_cons;

    //init
    idx_buffer = produced_items = consumed_items = 0;
    
    //Associate functions threads 
    if (pthread_create(&th_prod, 0, (void*) func_producer, (void*) 0)) { 
		printf("Erro ao criar produtor\n");
		exit(0); //exit if error
	}
	if (pthread_create(&th_cons, 0, (void*) func_consumer, (void*) 0)) { 
		printf("Erro ao criar consumidor\n");
		exit(0); //exit if error
	}

    //Start threads
    pthread_join(th_prod, 0);
	pthread_join(th_cons, 0);
    
    return 0;
}

//---------------------------------FUNCTIONS--------------------------------//
void* func_producer(void){
    int item;
    while(produced_items < MAX_ITEMS){
        item = random_item();
        usleep(200 * MILLISEC);

        //------BLOCK CRITICAL REGION------//
        pthread_mutex_lock(&atomic_process_lock);

        //While buffer is full, to make to sleep this thread until wait signal for wake
        while (idx_buffer == MAX_BUFFER)
            pthread_cond_wait(&cond_buffer_empty, &atomic_process_lock);
        produce_item(item);

        //Signal for wake thread consumer
        pthread_cond_signal(&cond_buffer_full);
        pthread_mutex_unlock(&atomic_process_lock);
        //-----------END BLOCK-------------//

    }
    pthread_exit(0);
}

void* func_consumer(void){
    int item;
    while(consumed_items < MAX_ITEMS){
        usleep(120 * MILLISEC);

        //------BLOCK CRITICAL REGION------//
        pthread_mutex_lock(&atomic_process_lock);
        
        //While buffer is empty, to make to sleep this thread until wait signal for wake
        while (!idx_buffer)
            pthread_cond_wait(&cond_buffer_full, &atomic_process_lock);
        item = consume_item();

        //Signal for wake thread produce
        pthread_cond_signal(&cond_buffer_empty);
        pthread_mutex_unlock(&atomic_process_lock);
        //-----------END BLOCK-------------//

        process_item(item);
    }
    pthread_exit(0);
}

void produce_item(int item){
    produced_items++;
    buffer[idx_buffer++] = item;

    printf("Prod: [%d] = %d. Buffer -> %d\n", produced_items, item, (idx_buffer-1));
}

int consume_item(){
    consumed_items++;
    printf(" Cons: [%d] = %d. Buffer -> %d\n", consumed_items, buffer[idx_buffer-1], idx_buffer-1);
    return buffer[--idx_buffer];
}

void process_item(int item){
    static int processed_item = 0; //static variable
    printf("Utilizacao do item: [%d] = %d\n", ++processed_item, item);
}

int random_item(){
    return (1+rand() % MAX_ITEM_VALUE); //1 <= x <= MAX_ITEM_VALUE
}