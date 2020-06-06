#include "Memory.h"

Memory::Memory(int available_size){
    this->available_size = available_size;
}

Memory::Memory(){
    this->available_size = 0;
}

void Memory::print(){
    for(Disc_Page page : page_list){
        printf("| Process %d | Page %d |\n", page.pid, page.adress);
    }
}