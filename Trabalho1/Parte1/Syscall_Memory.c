/*
 ============================================================================
 Description  : This is an example program that uses I/O in both standard and file input.
 Syscalls uses:
 brk() - 
 assert() - 
 ============================================================================
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {

    int tam_word = 15;
    void* ptr_void = sbrk(0);
    char* word = (char*) ptr_void;

    brk(word + tam_word);
    
    for(int i = 0; i < tam_word; i++)
        printf("%d\n", word[i]);

    strcpy(word, "teste");
    
    for(int i = 0; i < tam_word; i++)
        printf("%d\n", word[i]);

    assert(!strcmp(word, "teste"));
    assert(word[0] == 't');
    assert(word[1] == 'e');
    assert(word[2] == 's');
    assert(word[3] == 't');
    assert(word[4] == 'e');
    assert(word[5] == '\0');

    printf("%s\n", word);
    brk(ptr_void);

    return 0;
}