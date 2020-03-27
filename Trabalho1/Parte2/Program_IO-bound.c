/*
 ============================================================================
 Name        : Program_IO-bound.c
 Author      : Helbert M Pinto
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main() {
    char buffer[32];
    int n_buffer = 0;
	FILE *arqRead;
    FILE *arqWrite;

    arqWrite = fopen("output.bin", "wb");
    fclose(arqWrite);

    while(1){
        arqRead = fopen("input.bin", "rb");
        arqWrite = fopen("output.bin", "ab");
        
        if(!arqWrite || !arqRead)
            break;
        
        fseek(arqRead, 32 * n_buffer++, SEEK_SET);
        if(fread(buffer, sizeof(char), 32, arqRead)){
            fwrite(buffer, sizeof(char), 32, arqWrite);
            fflush(arqWrite);
        }else{
            break;
        }
        fclose(arqRead);
        fclose(arqWrite);
    }
    printf("SUCCESS!\n");
	return 0;
}