#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char ch;
    FILE *arqR = fopen("poema.txt", "r");
    
    if(arqR == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    } else {
        FILE *arqW = fopen("out.txt", "w");
        while( (ch=fgetc(arqR))!= EOF )
            fputc(ch, arqW);
        fclose(arqW);
    }

    fclose(arqR);

    printf("\n\nFim da execucao!\n");

    return 0;
}