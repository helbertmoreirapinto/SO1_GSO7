#include "Globals.h"
#include "Disc_Page.h"

Disc_Page::Disc_Page(int adress, int size){
    this->size = size;
    int multipl = (int)(size/sizeof(int));
    this->info = new int[multipl];
    this->adress = adress;
}

Disc_Page::~Disc_Page(){
    free(info);
}