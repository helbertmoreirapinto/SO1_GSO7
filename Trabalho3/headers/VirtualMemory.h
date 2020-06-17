#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include "Process.h"
#include "Memory.h"

class VirtualMemory{
public:
    int total_size;
    int page_size;
    int available_size;
    int std_swap_type;

    Memory primary;
    Memory disc;

    vector<Process> process_list;
    vector<Process> wait_process_list;

    VirtualMemory(int page_size);
    
    void allocate_process(int pid, int process_size);
    void allocate_process(Process process);
    void kill_process(int pid);
    void command(int pid, int adress);
    void print_process(int pid);
    void print_wait_list();
    void standard_swap_algorithm();
    void print_mem();
    void print_allocated_list();

private:
    Process* find_process_VM(int pid);
    void print_process_list(vector<Process> p_list, bool print_pages);
    void default_swap();
    void swap_clock();
    void swap_memory();
    void swap_fifo();
    void swap_lru();
};

#endif