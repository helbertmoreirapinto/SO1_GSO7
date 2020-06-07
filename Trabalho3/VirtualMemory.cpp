#include "headers/VirtualMemory.h"

int pfind = 0;
bool find_process(Process process) {
  return process.id == pfind;
}

VirtualMemory::VirtualMemory(int page_size){
    this->page_size = page_size;
    this->total_size = this->available_size = MEM_DISC + MEM_RAM;
    
    this->primary.available_size = MEM_RAM;
    this->disc.available_size = MEM_DISC;
}

void VirtualMemory::allocate_process(Process process){
    allocate_process(process.id, process.size);
}

// pid - process identifier
// process_size - process size in bytes 
void VirtualMemory::allocate_process(int pid, int process_size){
    Process process(pid, process_size);

    if(available_size < process_size){ //Add lista de espera
        wait_process_list.push_back(process);
        return;
    }

    int num_pages = (int)(process_size / page_size);
    if(process_size % page_size) num_pages++;
    
    for(int p = 0; p < num_pages; p++){

        Disc_Page page(p, pid, page_size);
        process.page_list.push_back(page);

        if(!primary.available_size)
            swap_fifo();
        
        primary.page_list.push_back(page);
        primary.available_size -= page_size;
    }

    available_size -= (num_pages * page_size);
    process_list.push_back(process);
}

//com problemas
void VirtualMemory::kill_process(int pid){
    pfind = pid;
    auto it = find_if(process_list.begin(), process_list.end(), find_process);
    if (it == process_list.end()){
        cout << "Processo nao encontrado" << endl;
        return;
    }

    Process process = *it;
    for(auto itr = primary.page_list.begin(); itr != primary.page_list.end(); itr++){
        Disc_Page page = *itr;
        if(page.pid == process.id){
            disc.available_size += page_size;
            available_size += page_size;
            primary.page_list.erase(itr--);
        }
    }

    for(auto itr = disc.page_list.begin(); itr != disc.page_list.end(); itr++){
        Disc_Page page = *itr;
        if(page.pid == process.id){
            disc.available_size += page_size;
            available_size += page_size;
            disc.page_list.erase(itr--);
        }
    }
    process_list.erase(it);
    
    //mover processos do wait pra executando
    if(!wait_process_list.empty() && wait_process_list[0].size < available_size){
        allocate_process(wait_process_list[0]);
        wait_process_list.erase(wait_process_list.begin());
    }

}

void VirtualMemory::command(int pid, int adress){
    //(falta fazer)
}

void VirtualMemory::print(){
    cout << "RAM" << endl;
    primary.print();
    cout << endl;

    cout << "DISC" << endl;
    disc.print();
    cout << endl;
}

void VirtualMemory::swap_fifo(){
    disc.page_list.push_back(primary.page_list.front());
    primary.page_list.erase(primary.page_list.begin());
    
    primary.available_size += page_size;
    disc.available_size -= page_size;
}

void VirtualMemory::swap_relogio(){
    //(falta fazer)
}

void VirtualMemory::swap_lru(){
    //(falta fazer)
}