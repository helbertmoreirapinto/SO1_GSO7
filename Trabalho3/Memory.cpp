#include "Memory.h"

Memory::Memory(uint16_t ID){
    this->ID = ID;
}

void Memory::print(){
    /* 
    for(auto it = pri_mem.begin(); it != pri_mem.end(); it+=8){
        Disc_Page a = *(it+0), b = *(it+1), c = *(it+2), d = *(it+3);
        Disc_Page e = *(it+4), f = *(it+5), g = *(it+6), h = *(it+7);
        printf("|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|\n",a.ID, b.ID, c.ID, d.ID, e.ID, f.ID, g.ID, h.ID);
        printf("|      |      |      |      |      |      |      |      |\n");
        printf("|-------------------------------------------------------|\n");
    }
    */
}