#include "Virtual.h"

/* 
Virtual::Virtual(uint page_size){
    this(0);
    this->pages_total = (int)(VIR_MEMORY/page_size);
}
 */

void Virtual::setSizePage(uint page_size){
    this->page_size = page_size;
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

bool Virtual::command(uint pID, uint adrs){
    // Process p = find()
    /*uint16_t pageID = adrs/this->page_size; 
    if(!p->pages[pageID].allocated){
        // swap pra memoria fisica 
    }*/
    // p.cmd(adrs);
}