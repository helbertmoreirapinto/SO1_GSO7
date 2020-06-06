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

// pid - process identifier
// process_size - process size in bytes 
void VirtualMemory::allocate_process(int pid, int process_size){
    Process process(pid, process_size);

    if(available_size < process_size){ //Add lista de espera
        wait_process_list.push(process);
        return;
    }

    //(falta fazer) ALGORITMO -> se RAM cheia, swap de paginas da ram com o disco
    int num_pages = (int)(process_size / page_size);
    if(process_size % page_size) num_pages++;
    for(int p = 0; p < num_pages; p++){
        Disc_Page page(p, pid, page_size);
        process.page_list.push_back(page);

        if(primary.available_size){
            primary.page_list.push_back(page);
            primary.available_size -= page_size;
        }else if(disc.available_size){
            disc.page_list.push_back(page);
            disc.available_size -= page_size;
        }else{
            cout << "Memory Error" << endl;
        }
    }
    available_size -= process_size;
    process_list.push_back(process);
}

void VirtualMemory::kill_process(int pid){
    pfind = pid;
    auto it = find_if(process_list.begin(), process_list.end(), find_process);
    if (it == process_list.end()){
        cout << "Processo nao encontrado" << endl;
        return;
    }
    process_list.erase(it);

    Process process = *it;
    for(auto it = primary.page_list.begin(); it != primary.page_list.end(); it++){
        if((*it).pid == process.id){
            primary.page_list.erase(it--);
            primary.available_size += page_size;
            available_size += page_size;
        }
    }
    for(auto it = disc.page_list.begin(); it != disc.page_list.end(); it++){
        if((*it).pid == process.id){
            disc.page_list.erase(it--);
            disc.available_size += page_size;
            available_size += page_size;
        }
    }

    //(falta fazer) mover processos do wait pra executando
}

void VirtualMemory::command(int pid, int adress){
    
}

void VirtualMemory::print(){
    cout << "RAM" << endl;
    primary.print();
    cout << endl;

    cout << "DISC" << endl;
    disc.print();
    cout << endl;
}