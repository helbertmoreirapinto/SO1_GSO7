#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include "Process.h"
#include "Memory.h"

class VirtualMemory{
public:
    int total_size;
    int page_size;
    int available_size;

    Memory primary(MEM_RAM);
    Memory disc(MEM_DISC);

    vector<Process> process_list;
    vector<Process> wait_process_list;

    VirtualMemory(int page_size);
    
    void allocate_process(int pid, int size_process);
    void kill_process(int pid);
    void command(int pid, int adress);
};

#endif