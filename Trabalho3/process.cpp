#include<bits/stdc++.h>

using namespace std;

/*Resources*/
#define PRI_MEMORY 1024 /*Kbytes*/
#define SEC_MEMORY 2048 /*Kbytes*/

class Disc_Page{
public:
    uint16_t ID;
    uint16_t size;
    Disc_Page* reference;

    Disc_Page(uint16_t size, uint16_t ID){
        this->ID = ID;
        this->size = size;
        this->reference = NULL;
    }

};

void format(uint16_t size_page);
void init_virt();
void print_mem();

vector<Disc_Page> virtual_mem;
vector<Disc_Page> pri_mem = {};
vector<Disc_Page> sec_mem = {};

int main(){
    uint16_t size_page;
    cout << "Input size disc page : "; cin >> size_page;

    format(size_page);
    init_virt();

    print_mem();

    //create pages im memories() //format()
    //create virtualization()
    
    //create process()
    //allocate memory for process()
    //use memory
    //kill process()

    //kill pages() //free memory
    return 0;
}


void format(uint16_t size_page){
    int len_pri_pages = (int)(PRI_MEMORY/size_page);
    for(int i = 0; i < len_pri_pages; i++){
        Disc_Page page(size_page, i);
        pri_mem.push_back(page);
    }

    int len_sec_pages = (int)(SEC_MEMORY/size_page);
    for(int i = 0; i < len_sec_pages; i++){
        Disc_Page page(size_page, i);
        sec_mem.push_back(page);
    }
}

void init_virt(){

}

void print_mem(){
    cout << "Principal Memory\n";
    for(auto it = pri_mem.begin(); it != pri_mem.end(); it+=8){
        Disc_Page a = *(it+0), b = *(it+1), c = *(it+2), d = *(it+3);
        Disc_Page e = *(it+4), f = *(it+5), g = *(it+6), h = *(it+7);
        printf("|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|\n",a.ID, b.ID, c.ID, d.ID, e.ID, f.ID, g.ID, h.ID);
        printf("|      |      |      |      |      |      |      |      |\n");
        printf("|-------------------------------------------------------|\n");
    }
    cout << "\n";
    cout << "Second Memory\n";
    for(auto it = sec_mem.begin(); it != sec_mem.end(); it+=8){
        Disc_Page a = *(it+0), b = *(it+1), c = *(it+2), d = *(it+3);
        Disc_Page e = *(it+4), f = *(it+5), g = *(it+6), h = *(it+7);
        printf("|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|-0x%02X-|\n",a.ID, b.ID, c.ID, d.ID, e.ID, f.ID, g.ID, h.ID);
        printf("|      |      |      |      |      |      |      |      |\n");
        printf("|-------------------------------------------------------|\n");
    }
}