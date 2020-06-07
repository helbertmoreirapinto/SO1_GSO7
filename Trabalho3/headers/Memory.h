#ifndef MEMORY_H
#define MEMORY_H

#include "Globals.h"
#include "Disc_Page.h"

class Memory{
public:
    int available_size;
    queue<Disc_Page> page_list;
    Memory(int available_size);
    Memory();
    void print();
};

#endif