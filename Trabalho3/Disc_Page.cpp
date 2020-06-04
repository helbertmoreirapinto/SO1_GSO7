#include "Disc_Page.h"

Disc_Page::Disc_Page(uint16_t size, uint16_t ID){
    this->ID = ID;
    this->size = size;
    this->allocated = false;
}

string Disc_Page::toString(){
    return "teste";
}