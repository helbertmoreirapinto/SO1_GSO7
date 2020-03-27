#include <stdio.h>

int main(){
    char ch;
    FILE *arq = fopen("poema.txt", "r");
    
    if(arq == NULL)
        printf("Error! can't open file\n");
    else
        while( (ch=fgetc(arq))!= EOF )
            putchar(ch);

    fclose(arq);

    printf("\n\n");
    printf("Sucess!\n");

    return 0;
}