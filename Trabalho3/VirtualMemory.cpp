#include "VirtualMemory.h"

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
    }else{
        
        available_size -= process_size;
        int num_pages = (int)(process_size / page_size);
        if(process_size % page_size) num_pages++;
        for(int p = 0; p < num_pages; p++){
            Disc_Page page(p, pid, page_size);
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


        
        
        //alocar maximo que der na RAM e restante no disco
        //se ram cheia, remover uma pagina de um processo com maior id
        //ALGORITMO

    }
}

void VirtualMemory::kill_process(int pid){
    
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