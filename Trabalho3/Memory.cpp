#include "headers/Memory.h"

Memory::Memory(int available_size){
    this->available_size = available_size;
}

Memory::Memory(){
    this->available_size = 0;
}

void Memory::print(){
    if(page_list.empty()){
        cout << "Vazio" << endl;
        return;
    }

    queue<Disc_Page> aux = {};
    while(!page_list.empty()){
        Disc_Page page = page_list.front();
        page_list.pop();
        printf("| Process %d | Page %d |\n", page.pid, page.adress);
        aux.push(page);
    }
    page_list = aux;
}