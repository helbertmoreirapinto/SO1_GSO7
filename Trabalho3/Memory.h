#ifndef MEMORY_H
#define MEMORY_H

#include "Globals.h"
#include "Disc_Page.h"

class Memory{
public:
    uint16_t ID;
    uint16_t size;
    uint16_t len_pages;
    vector<Disc_Page> pages;

    Memory(uint16_t ID);
    void print();
};

#endif