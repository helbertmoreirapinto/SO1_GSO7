#include "headers/Memory.h"

Memory::Memory(int available_size){
    this->available_size = available_size;
}

Memory::Memory(){
    this->available_size = 0;
}

void Memory::print(){
    if(page_list.empty()){
        cout << "Empty" << endl;
        return;
    }

    for(Disc_Page page : page_list){
        printf("| Process %02d | Page %02d | Counter %02d | Bit R %d |\n", page.pid, page.address, page.count, page.R);
    }
}