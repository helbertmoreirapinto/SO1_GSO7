#include "headers/VirtualMemory.h"

static int idx_queue = 0;

bool compare_process(Process a, Process b) {
  return a.id < b.id;
}

// page_size - virtual page size
VirtualMemory::VirtualMemory(int page_size){
    this->page_size = page_size;
    this->total_size = this->available_size = MEM_DISC + MEM_RAM;
    this->std_swap_type = 0;

    this->primary.available_size = MEM_RAM;
    this->disc.available_size = MEM_DISC;
}

// process - allocate a process
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
            standard_swap_algorithm();
        
        primary.page_list.insert(primary.page_list.begin()+idx_queue, page);
        idx_queue = (idx_queue+1 < MEM_RAM/page_size) ? idx_queue+1 : 0;
        primary.available_size -= page_size;
    }

    available_size -= (num_pages * page_size);
    process_list.push_back(process);
    // process list ser uma lista ordenada
    sort(process_list.begin(), process_list.end(), compare_process);
}

// pid - process identifier
void VirtualMemory::kill_process(int pid){
    printf("[INFO]: KILL -> pro:%d\n",pid);
    Process *p = find_process_VM(pid);
    if (p == NULL){
        cout << "[INFO]: PROCESS NOT FOUND" << endl;
        free(p);
        return;
    }

    auto it = process_list.begin();
    while(it != process_list.end()){
        if((*it).id == pid)
            break;
        it++;
    }
    
    for(;idx_queue >= 0;idx_queue--){
        if(primary.page_list[idx_queue].pid != pid)
            break;
    }

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
    for(auto n_it = wait_process_list.begin(); n_it != wait_process_list.end(); n_it++){
        if((*n_it).size > available_size)
            break;
        allocate_process(*n_it);
        wait_process_list.erase(n_it);
        n_it--;
    }
}

// pid - process identifier
Process* VirtualMemory::find_process_VM(int pid){
    Process* p = new Process;
    auto it = process_list.begin();
    while(it != process_list.end()){
        if((*it).id == pid)
            break;
        it++;
    }
    if(it == process_list.end())
        return NULL;
    p->id = (*it).id;
    p->page_list = (*it).page_list;
    p->size = (*it).size;

    return p;
}

// pid - process identifier
void VirtualMemory::print_process(int pid){
    Process* p = find_process_VM(pid);
    if(p == NULL)
        cout << "[INFO]: PROCESS NOT FOUND AT VM!" << endl;
    else{
        cout << "[INFO]: FOUND -> pro:" << p->id << " size:"<< p->size << " pages:"<< p->page_list.size() << endl;
        free(p);
    }
}

// pid - process identifier
// adress - process page number
void VirtualMemory::command(int pid, int address){
    //ver qual pagina esta address
    int num_page = address / page_size;
    
    // busca na lista de processos
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
    
    printf("[INFO] USE PAGE -> page:%d \n", num_page);

    // busca na memoria principal
    auto it1 = primary.page_list.begin();
    for(;it1 != primary.page_list.end(); it1++){
        if((*it1).pid == pid && (*it1).address == num_page)
            break;
    }

    //caso precise fazer swap
    if(it1 == primary.page_list.end()){
        cout << "[INFO] SWAPPING PAGES" << endl;
        if (!primary.available_size)
            standard_swap_algorithm();
        
        // busca na memoria secundaria
        auto it2 = disc.page_list.begin();
        for(;it2 != disc.page_list.end(); it2++){
            if((*it2).pid == pid && (*it2).address == num_page)
                break;
        }

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

// use swap fifo
void VirtualMemory::swap_fifo(){
    disc.page_list.push_back(primary.page_list.front());
    primary.page_list.erase(primary.page_list.begin());
    swap_memory();
}

// use swap lru
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

// use swap clock
void VirtualMemory::swap_clock(){
    while(primary.page_list[idx_queue].R){
        primary.page_list[idx_queue].R = false;
        idx_queue = ((idx_queue+1) < primary.page_list.size()) ? idx_queue+1 : 0;
    }
    disc.page_list.push_back(primary.page_list[idx_queue]);
    primary.page_list.erase(primary.page_list.begin()+idx_queue);
    swap_memory();
}

// default swap in size memory
void VirtualMemory::swap_memory(){
    primary.available_size += page_size;
    disc.available_size -= page_size;
}

// select swap
void VirtualMemory::standard_swap_algorithm(){
    if(std_swap_type == SWAP_LRU){
        swap_lru();
    }else if(std_swap_type == SWAP_CLOCK){
        swap_clock();
    }
}

// print virtual memory
void VirtualMemory::print_mem(){
    cout << "----------------------------------------" << endl << "RAM" << endl;
    int idx_print = (std_swap_type == SWAP_CLOCK) ? idx_queue : -1;
    primary.print(std_swap_type, idx_print);
    cout << endl;

    cout << "DISC" << endl;
    disc.print(std_swap_type, -1);
    cout << "----------------------------------------" << endl;
    cout << endl;
}

// p_list - list of process pages
// print_pages - true if pages are allocated
void VirtualMemory::print_process_list(vector<Process> p_list, bool print_pages){
    if(p_list.empty())
        cout << "Empty";
    for(Process p : p_list){
        cout << "(ID: " << p.id << ", size: " << p.size;
        if(print_pages)
            cout << ", pages:" << p.page_list.size();
        cout << ") ";
    }
    cout << endl;
}

// print list of waiting processes
void VirtualMemory::print_wait_list(){
    cout << "Wait List: ";
    print_process_list(wait_process_list, false);
}

// print list of allocated processes
void VirtualMemory::print_allocated_list(){
    cout << "Process List: ";
    print_process_list(process_list, true);
}