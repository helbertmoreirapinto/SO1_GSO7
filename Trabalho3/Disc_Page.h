#ifndef DISC_H
#define DISC_H

#include "Globals.h"

class Disc_Page{
private:
    uint16_t ID;
    uint16_t size;
    bool allocated;
public:
    Disc_Page(uint16_t size, uint16_t ID);
    string toString();
};

#endif