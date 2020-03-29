/*
 ============================================================================
 Description  : This example shows the difference betwenn the use of arrays 
                with and without shared memory.
 Syscalls uses:
 brk() -    Allocates memory for the process.
 ftok() -   Return a unique key.
 shmget() - Returns an identifier for the shared memory segment.
 shmat() -  Connects to the memory segment.
 ============================================================================
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <sys/wait.h> 

int main() {
    int arr_size = 15;
    
    //ARRAY 1 - Unshared memory
    void* ptr_void1 = sbrk(0);
    if(ptr_void1 == NULL){
        printf("Error alocate memory [arr1]\n");
        return 1;
    }
    int* arr1 = (int*) ptr_void1;
    brk(arr1 + arr_size);
    
    //ARRAY 2 - Shared memory
    key_t key = ftok("shmkey", 65);
    int shmid = shmget(key, arr_size * sizeof(int), 0666 | IPC_CREAT);

    if(shmid < 0){
        printf("Error alocate memory [arr2]\n");
        return 1;
    }
    
    int pid = fork();

    int* arr2 = (int*) shmat(shmid, (void*)0,0); 

    if(pid){
        //Process 1 [Write data]
        for(int i = 0; i < arr_size; i++)
            arr1[i] = arr2[i] = i;
    }else{
        //Process 2 [Read data]
        printf("Unshared array:\n");
        for(int i = 0; i < arr_size; i++)
            printf("%02d ", arr1[i]);
        printf("\n\n");
        printf("Shared array:\n");
        for(int i = 0; i < arr_size; i++)
            printf("%02d ", arr2[i]);
        printf("\n");   
    }
    wait(NULL);

    brk(arr1);
    shmdt(arr2);

    return 0;
}
