#include "headers/VirtualMemory.h"

int find_process_id = 0;
int find_page_pid = 0;
int find_page_address = 0;
static int idx_queue = 0;

bool find_process(Process process) {
  return process.id == find_process_id;
}

bool find_page(Disc_Page page) {
  return page.pid == find_page_pid && page.address == find_page_address;
}

bool compare_process(Process a, Process b) {
  return a.id < b.id;
}

VirtualMemory::VirtualMemory(int page_size){
    this->page_size = page_size;
    this->total_size = this->available_size = MEM_DISC + MEM_RAM;
    
    this->primary.available_size = MEM_RAM;
    this->disc.available_size = MEM_DISC;
}

void VirtualMemory::allocate_process(Process process){
    allocate_process(process.id, process.size);
}

// pid - process identifier
// process_size - process size in bytes 
void VirtualMemory::allocate_process(int pid, int process_size){
    
    Process* check_process = find_process_VM(pid);
    if(check_process != NULL){
        cout << "[INFO]: PROCESS ALREADY EXISTS" << endl;
        free(check_process);
        return;
    }
    if(total_size < process_size){
        cout << "[INFO]: NO SPACE AT VIRTUAL MEMORY" << endl;
        return;
    }

    Process process(pid, process_size);
    
    if(available_size < process_size){ //Add lista de espera
        cout << "[INFO]: PROCESS AT WAIT LIST" << endl;
        wait_process_list.push_back(process);
        return;
    }

    printf("[INFO]: ALLOC -> pro:%d\n",pid);

    int num_pages = (int)(process_size / page_size);
    if(process_size % page_size) num_pages++;
    
    for(int p = 0; p < num_pages; p++){

        Disc_Page page(p, pid, page_size);
        process.page_list.push_back(page);

        if(!primary.available_size)
            default_swap();
        
        primary.page_list.insert(primary.page_list.begin()+idx_queue, page);
        idx_queue = (idx_queue+1 < MEM_RAM/page_size) ? idx_queue+1 : 0;
        primary.available_size -= page_size;
    }

    available_size -= (num_pages * page_size);
    process_list.push_back(process);
    // process list ser uma lista ordenada
    sort(process_list.begin(), process_list.end(), compare_process);
}

void VirtualMemory::kill_process(int pid){
    printf("[INFO]: KILL -> pro:%d\n",pid);
    Process *p = find_process_VM(pid);
    if (p == NULL){
        cout << "[INFO]: PROCESS NOT FOUND" << endl;
        return;
    }
    
    auto it = find_if(process_list.begin(), process_list.end(), find_process);
    
    for(auto itr = primary.page_list.begin(); itr != primary.page_list.end(); itr++){
        Disc_Page page = *itr;
        if(page.pid == p->id){
            primary.available_size += page_size;
            available_size += page_size;
            primary.page_list.erase(itr--);
        }
    }

    for(auto itr = disc.page_list.begin(); itr != disc.page_list.end(); itr++){
        Disc_Page page = *itr;
        if(page.pid == p->id){
            disc.available_size += page_size;
            available_size += page_size;
            disc.page_list.erase(itr--);
        }
    }

    process_list.erase(it);
    
    //mover processos do wait pra executando
    for(Process new_process : wait_process_list){
        if(new_process.size >= available_size)
            break;
        allocate_process(new_process);
    }
}

Process* VirtualMemory::find_process_VM(int pid){
    Process* p = new Process;
    find_process_id = pid;
    auto it = find_if(process_list.begin(), process_list.end(), find_process);
    if(it == process_list.end())
        return NULL;
    p->id = (*it).id;
    p->page_list = (*it).page_list;
    p->size = (*it).size;

    return p;
}

void VirtualMemory::print_process(int pid){
    Process* p = find_process_VM(pid);
    if(p == NULL)
        cout << "[INFO]: PROCESS NOT FOUND AT VM!" << endl;
    else{
        cout << "[INFO]: FOUND -> pro:" << p->id << " size:"<< p->size << " pages:"<< p->page_list.size() << endl;
        free(p);
    }
}

void VirtualMemory::command(int pid, int address){
    //ver qual pagina esta address
    int num_page = address / page_size;
    find_process_id = pid;
    find_page_pid = pid;
    find_page_address = num_page;
    
    // busca na lista de processos
    //auto it0 = find_if(process_list.begin(), process_list.end(), find_process);
    Process *p = find_process_VM(pid);

    if(!p){
        cout << "[ERROR] PROCESS DOESN'T EXISTS!" << endl;
        return;
    }

    cout << "[INFO] OPERATE -> pro:" << p->id << " size:"<< p->size << " pages:"<< p->page_list.size() << endl; 

    // address fora do size do processo
    if(address >= p->size){
        cout << "[ERROR] UNABLE TO ACESS THIS ADDRESS!" << endl;
        free(p);
        return;
    }

    free(p);
    
    printf("[INFO] USE PAGE -> page:%d \n",num_page);
    
    // busca na memoria principal
    auto it1 = find_if(primary.page_list.begin(), primary.page_list.end(), find_page);
    
    // busca na memoria secundaria
    auto it2 = find_if(disc.page_list.begin(), disc.page_list.end(), find_page);

    //caso precise fazer swap
    if(it1 == primary.page_list.end()){
        cout << "[INFO] SWAPPING PAGES" << endl;
        if (!primary.available_size)
            default_swap();

        (*it2).count++;
        primary.page_list.push_back(*it2);
        disc.page_list.erase(it2);
        
        primary.available_size -= page_size;
        disc.available_size += page_size;
    }else{
        int idx_page = it1 - primary.page_list.begin();
        int dist = (idx_page >= idx_queue) ? (idx_page - idx_queue) : (primary.page_list.size() - idx_queue + idx_page);
        //se a pagina ref esta a ate 25% [do tamanho total] a frente do ponteiro do relogio
        //a pagina recebe a marca de referenciada
        if(dist < 0.25*primary.page_list.size())
            primary.page_list[idx_page].R = true;    
        primary.page_list[idx_page].count++;
    }

    cout << "[INFO] END OF OPERATION = SUCCESS" << endl;
}

void VirtualMemory::swap_fifo(){
    disc.page_list.push_back(primary.page_list.front());
    primary.page_list.erase(primary.page_list.begin());
    swap_memory();
}

void VirtualMemory::swap_lru(){
    auto it_swap = primary.page_list.begin();
    for(auto it = primary.page_list.begin(); it != primary.page_list.end(); it++){
        if((*it).count < (*it_swap).count)
            it_swap = it;
    }
    (*it_swap).count = 0;
    disc.page_list.push_back(*it_swap);
    primary.page_list.erase(it_swap);
    idx_queue = primary.page_list.size();
    swap_memory();
}

void VirtualMemory::swap_relogio(){
    while(primary.page_list[idx_queue].R){
        primary.page_list[idx_queue].R = false;
        idx_queue = ((idx_queue+1) < primary.page_list.size()) ? idx_queue+1 : 0;
    }
    disc.page_list.push_back(primary.page_list[idx_queue]);
    primary.page_list.erase(primary.page_list.begin()+idx_queue);
    swap_memory();
}

void VirtualMemory::swap_memory(){
    primary.available_size += page_size;
    disc.available_size -= page_size;
}

void VirtualMemory::default_swap(){
    //swap_relogio();
     swap_lru();
}

void VirtualMemory::print(){
    cout << "----------------------------------------" << endl << "RAM" << endl;
    primary.print();
    cout << endl;

    cout << "DISC" << endl;
    disc.print();
    cout << "----------------------------------------" << endl;
    cout << endl;
}

void VirtualMemory::print_process_list(vector<Process> p_list){
    if(p_list.empty())
        cout << "Empty";
    for(Process p : p_list)
        cout << "(ID: " << p.id << ", size: " << p.size << ", pages:" << p.page_list.size() << ") ";
    cout << endl;
}

void VirtualMemory::show(){
    cout << "Process List: ";
    print_process_list(process_list);
}

void VirtualMemory::print_wait_list(){
    cout << "Wait List: ";
    print_process_list(wait_process_list);
}