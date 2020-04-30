//----------------------------------IMPORTS---------------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
int idx_prod, idx_cons;
bool can_prod, can_cons;
int produced_items, consumed_items;

//-----------------------------------MAIN-----------------------------------//
int main(){
    //Change seed to make items random
    srand (time(NULL));
    
    //Threads
    pthread_t th_prod;
    pthread_t th_cons;

    //init
    idx_prod = idx_cons = produced_items = consumed_items = 0;
    can_prod = true;
    can_cons = false;

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
        usleep(120 * MILLISEC);

        //------BLOCK CRITICAL REGION------//
        pthread_mutex_lock(&atomic_process_lock);

        //While buffer is full, to make to sleep this thread until wait signal for wake
        while (!can_prod)
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
        usleep(250 * MILLISEC);

        //------BLOCK CRITICAL REGION------//
        pthread_mutex_lock(&atomic_process_lock);
        
        //While buffer is empty, to make to sleep this thread until wait signal for wake
        while (!can_cons)
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
    buffer[idx_prod] = item;
    printf("Prod: [%d] = %d. Idx_Prod -> %d\n", produced_items, item, idx_prod);

    idx_prod = (idx_prod+1 < MAX_BUFFER) ? idx_prod+1 : 0;
    can_prod = !(idx_prod == idx_cons);
    can_cons = true;
}

int consume_item(){
    int item;
    consumed_items++;
    item = buffer[idx_cons];
    printf(" Cons: [%d] = %d. Idx_Cons -> %d\n", consumed_items, buffer[idx_cons], idx_cons);

    idx_cons = (idx_cons+1 < MAX_BUFFER) ? idx_cons+1 : 0;
    can_cons = !(idx_cons == idx_prod);
    can_prod = true;
    return item;
}

void process_item(int item){
    static int processed_item = 0; //static variable
    printf("Utilizacao do item: [%d] = %d\n", ++processed_item, item);
}

int random_item(){
    return (1+rand() % MAX_ITEM_VALUE); //1 <= x <= MAX_ITEM_VALUE
}