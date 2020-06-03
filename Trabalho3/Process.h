#ifndef PROCESS_H
#define PROCESS_H

#include "Globals.h"
#include "Disc_Page.h"

class Process{
public:
    uint16_t ID;
    uint16_t size;
    uint16_t len_pages;
    vector<Disc_Page> pages;

    vector<Disc_Page> getPages();
    Process(uint16_t ID, uint16_t size, uint16_t size_page);
    bool cmd(uint16_t adrs);
};

#endif