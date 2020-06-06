#ifndef DISC_PAGE_H
#define DISC_PAGE_H

class Disc_Page{
public:
    int adress;
    int* info;
    int size;
    int pid;
    
    Disc_Page(int adress, int pid, int size);
    //~Disc_Page();
};

#endif