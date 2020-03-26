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
#include <stdlib.h>

int main(void) {
    char string[32];
	FILE *arqRead = fopen("input.bin", "rb");
    FILE *arqWrite = fopen("output.bin", "wb");
    if(arqRead){
        while (fread(string, sizeof(char), 32, arqRead))
        {
            fwrite(string, sizeof(char), 32, arqWrite);
            fflush(arqWrite);
        }
    }
    fclose(arqRead);
    fclose(arqWrite);
    printf("SUCCESS!\n");
	return EXIT_SUCCESS;
}