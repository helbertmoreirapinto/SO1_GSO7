#include "headers/Globals.h"
#include "headers/Disc_Page.h"

// address - disk page identifier
// pid - process identifier
// size - disk page size
Disc_Page::Disc_Page(int address, int pid, int size){
    this->address = address;
    this->pid = pid;
    this->size = size;
    this->count = 0;
    this->R = false;
    
    int multipl = (int)(size/sizeof(int));
    info = new int[multipl];
    memset(info, -1, sizeof(info));
}

Disc_Page::Disc_Page(){
    address = pid = size = count = 0;
    R = false;
}

/*
Disc_Page::~Disc_Page(){
    free(info);
}
*/