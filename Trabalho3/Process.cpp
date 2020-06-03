#include "Process.h"

Process::Process(uint16_t ID, uint16_t size, uint16_t size_page){
    this->ID = ID;
    this->size = size;
    this->len_pages = (int)(size /size_page) + 1;
    for(int i = 0; i < len_pages; i++){
        Disc_Page page(size_page, i);
        pages.push_back(page);
        // memoria princial ou secundaria tem que referenciar essas paginas
    }
}

bool Process::cmd(uint16_t adrs){
    //if(!address page allocated){
        // swap pra memoria fisica 
    //}

    // checar o address
}

