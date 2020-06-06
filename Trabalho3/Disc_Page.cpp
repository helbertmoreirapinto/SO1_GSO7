#include "Globals.h"
#include "Disc_Page.h"

// adress - disk page identifier
// pid - process identifier
// size - disk page size
Disc_Page::Disc_Page(int adress, int pid, int size){
    this->adress = adress;
    this->pid = pid;
    this->size = size;
    
    int multipl = (int)(size/sizeof(int));
    info = new int[multipl];
    memset(info, -1, sizeof(info));
}

/*
Disc_Page::~Disc_Page(){
    free(info);
}
*/