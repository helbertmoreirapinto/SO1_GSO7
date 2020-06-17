#include "headers/Memory.h"

// available_size - available memory size
Memory::Memory(int available_size){
    this->available_size = available_size;
}

// standard memory initialization
Memory::Memory(){
    this->available_size = 0;
}

// type - swap type used
// clock_pos - if the swap type is clock it prints the watch hand, otherwise it just ignores
void Memory::print(int type, int clock_pos){
    if(page_list.empty()){
        cout << "Empty" << endl;
        return;
    }
    
    int i = 0;
    for(Disc_Page page : page_list){
        if(type == SWAP_CLOCK){
            printf("| Process %02d | Page %02d | Bit_R %-6s| %c\n", page.pid, page.address, (page.R)?"true":"false", (clock_pos == i)?'<':' ');
        }else if(type == SWAP_LRU){
            printf("| Process %02d | Page %02d | Counter %02d |\n", page.pid, page.address, page.count);
        }
        i++;
    }
}