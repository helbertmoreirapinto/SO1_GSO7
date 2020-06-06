#ifndef PROCESS_H
#define PROCESS_H

#include "Globals.h"
#include "Disc_Page.h"

class Process{
public:
    int id;
    int size;
    vector<Disc_Page> pageList;
    Process(int id, int size);
};

#endif