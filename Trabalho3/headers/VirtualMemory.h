#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include "Process.h"
#include "Memory.h"

class VirtualMemory{
public:
    int total_size;
    int page_size;
    int available_size;

    Memory primary;
    Memory disc;

    vector<Process> process_list;
    vector<Process> wait_process_list;

    VirtualMemory(int page_size);
    
    void allocate_process(int pid, int process_size);
    void allocate_process(Process process);
    void kill_process(int pid);
    void command(int pid, int adress);
    void print();

private:
    void swap_memory();
    void swap_fifo();
    void swap_relogio();
    void swap_lru();
    void default_swap();
};

#endif