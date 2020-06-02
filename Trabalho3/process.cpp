#include<bits/stdc++.h>

using namespace std;

/*Resources*/
#define VIR_MEMORY 2048 /*Kbytes*/
#define PRI_MEMORY 1024 /*Kbytes*/
#define SEC_MEMORY 2048 /*Kbytes*/


// Virtual memory tem um vector de processos
// As memorias tem vector de paginas
// Criar herança de memoria
// Criar memoria fisica e secundaria
// Virtual memory: criar um find de processo
// Process: cmd
// Destrutores


class Disc_Page{
    public:
        uint16_t ID;
        uint16_t size;
        bool allocated = false;

    Disc_Page(uint16_t size, uint16_t ID){
        this->ID = ID;
        this->size = size;
        this->reference = NULL;
    }

    string toString(){
        return "P";// + this->ID;
    }

};

class Process{
    public:
        uint16_t ID;
        uint16_t size;
        uint16_t len_pages;
        vector<Disc_Page> pages;
    
    Process(uint16_t ID, uint16_t size, uint16_t size_page){
        this->ID = ID;
        this->size = size;
        this->len_pages = (int)(size /size_page) + 1;
        for(int i = 0; i < len_pages; i++){
            Disc_Page page(size_page, i);
            pages.push_back(page);

            // memoria princial ou secundaria tem que referenciar essas paginas
        }

    }

    bool cmd(uint16_t adrs){
        //if(!address page allocated){
            // swap pra memoria fisica 
        //}

        // checar o address
    }

};

class Virtual_Memory{
    public:
        uint16_t size;
        uint16_t page_size;
        uint16_t pages_total;
        uint16_t pages_allocated = 0;
        vector<Process> process_table;
        vector<Disc_Page> pages;
    
    Virtual_Memory(uint16_t size, uint16_t page_size){
        this->size = size;
        this->page_size = page_size;
        this->pages_total = (int)(size/page_size);
    }

    bool allocate_process(Process p){
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

    Virtual_Memory vm(VIR_MEMORY, size_page);
    cout << "Paginas total: " << vm.pages_total << endl;
    for (int i = 0; i < 3; i++)
    {
        Process p(i, 1023, size_page);
        cout << vm.allocate_process(p) << endl;
        cout << "Paginas alocadas: " << vm.pages_allocated << endl;
    }
    
    
    //format(size_page);
    //init_virt();

    //print_mem();

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