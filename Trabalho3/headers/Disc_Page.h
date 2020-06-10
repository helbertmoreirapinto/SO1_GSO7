#ifndef DISC_PAGE_H
#define DISC_PAGE_H

class Disc_Page{
public:
    int address;
    int* info;
    int size;
    int pid;
    int count;  // LRU
    bool R;     // Relogio
    
    Disc_Page();
    Disc_Page(int adress, int pid, int size);
    //~Disc_Page();
};

#endif