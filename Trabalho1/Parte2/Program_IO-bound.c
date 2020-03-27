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

int main(void)
{
    char ch;
    FILE *arq;

    arq = fopen("poema.txt", "r");
    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else
        while( (ch=fgetc(arq))!= EOF )
    putchar(ch);

    fclose(arq);

    printf("\n\nFim da execucao!\n");

    return 0;
}