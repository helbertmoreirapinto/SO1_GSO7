#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include "Process.h"
#include "Memory.h"

class Virtual : public Memory{
public:
    uint16_t page_size;
    uint16_t pages_total;
    uint16_t pages_allocated;
    vector<Disc_Page> pages;
    vector<Process> process_table;
    
    Virtual(uint16_t size, uint16_t page_size);
    bool allocate_process(Process p);
    bool command(uint16_t pID, uint16_t adrs);
};

#endif