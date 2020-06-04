#include "VirtualMemory.h"

VirtualMemory::VirtualMemory(int page_size){
    this->page_size = page_size;
    this->total_size = this->available_size = MEM_DISC + MEM_RAM;
    
    /* this->primary(MEM_RAM);
     this->disc(MEM_DISC);
*/
}

void VirtualMemory::allocate_process(int pid, int size_process){
    Process process(pid, size_process);

    if(available_size < size_process){ //Add lista de espera
        wait_process_list.push_back(process);
    }else{
        available_size -= size_process;
        
        //alocar maximo que der na RAM e restante no disco
        //se ram cheia, remover uma pagina de um processo com maior id
        //ALGORITMO

    }
}

void VirtualMemory::kill_process(int pid){
    
}

void VirtualMemory::command(int pid, int adress){
    
}