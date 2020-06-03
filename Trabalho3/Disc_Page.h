#ifndef DISC_H
#define DISC_H

#include "Globals.h"

class Disc_Page{
private:
    uint ID;
    uint size;
    bool allocated;
public:
    Disc_Page(uint size, uint ID);
    string toString();
};

#endif