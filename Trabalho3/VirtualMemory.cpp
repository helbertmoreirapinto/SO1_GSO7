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
        
        primary.page_list.push(page);
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
    process_list.erase(it);

    Process process = *it;
    
    queue<Disc_Page> aux = {};
    while(!primary.page_list.empty()){
        Disc_Page page = primary.page_list.front();
        if(page.pid == process.id){
            primary.available_size += page_size;
            available_size += page_size;
        }else{
            aux.push(page);
        }
        primary.page_list.pop();
    }
    primary.page_list = aux;

    aux = {};
    while(!disc.page_list.empty()){
        Disc_Page page = disc.page_list.front();
        if(page.pid == process.id){
            disc.available_size += page_size;
            available_size += page_size;
        }else{
            aux.push(page);
        }
        disc.page_list.pop();   
    }
    disc.page_list = aux;

    //mover processos do wait pra executando
    for(int i = 0; i < wait_process_list.size(); i++){
        if(wait_process_list[i].size < available_size){
            allocate_process(wait_process_list[i]);
            wait_process_list.erase(wait_process_list.begin() + i);
            break;
        }
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
    disc.page_list.push(primary.page_list.front());
    primary.page_list.pop();
    
    primary.available_size += page_size;
    disc.available_size -= page_size;
}

void VirtualMemory::swap_relogio(){
    //(falta fazer)
}