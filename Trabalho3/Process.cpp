#include "Process.h"

Process::Process(uint16_t ID, uint16_t size, uint16_t size_page){
    this->ID = ID;
    this->size = size;
    this->size_page = size_page;
    this->len_pages = (int)(size/size_page) + 1;
}

bool Process::alocate(){
    for(int i = 0; i < len_pages; i++){
        Disc_Page page(size_page, i);
        this->pages.push_back(page);
        // memoria princial ou secundaria tem que referenciar essas paginas
    }
}

bool Process::cmd(uint16_t adrs){
    // checar o address
    if (adrs >= this->size){
        // impossivel acessar esse adrs
    }
    
}

