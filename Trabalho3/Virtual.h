#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include "Process.h"
#include "Memory.h"

class Virtual : public Memory{
public:
    uint page_size;
    uint pages_total;
    uint pages_allocated;
    vector<Disc_Page> pages;
    vector<Process> process_table;
    
    Virtual(uint page_size);
    bool allocate_process(Process p);
};

#endif