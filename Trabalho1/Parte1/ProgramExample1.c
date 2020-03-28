#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int args_size, char* args[]){
    int n = (args[1]) ? atoi(args[1]) : 5;
    printf("-----------------------------\n");
    printf("Programa Exemplo 1\n");
    printf("Contador ate %d\n", n);
    for(int i = 0; i < n;i++)
        printf("%02d ", i);
    printf("\n\n");

    return 0;
}