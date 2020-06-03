#include "Virtual.h"

Virtual::Virtual(uint16_t size, uint16_t page_size){
    this(0);
    this->page_size = page_size;
    this->pages_total = (int)(size/page_size);
}

bool Virtual::allocate_process(Process p){
    if(this->pages_allocated + p.len_pages <= this->pages_total){
        process_table.push_back(p);
        // alocar na memoria fisica -> passar as páginas do processo pra da memoria fisica
        //p.allocated = true;
        this->pages_allocated += p.len_pages;
        return true;
    } else {
        return false;
    }
}