#include "headers/VirtualMemory.h"

int find_process_id = -1;
int find_page_pid = -1;
int find_page_adress = -1;

bool find_process(Process process) {
  return process.id == find_process_id;
}

bool find_page(Disc_Page page) {
  return page.pid == find_page_pid && page.adress == find_page_adress;
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
    printf("ALLOC -> pro:%d\n",pid);

    // tratar para nao alocar processo com o mesmo pid
    // process list ser uma lista ordenada
    Process process(pid, process_size);

    if(total_size < process_size){
        cout << "   -> NO SPACE AT VIRTUAL MEMORY" << endl;
        return;
    }

    if(available_size < process_size){ //Add lista de espera
        cout << "   -> PROCESS AT WAIT LIST" << endl;
        wait_process_list.push_back(process);
        return;
    }

    int num_pages = (int)(process_size / page_size);
    if(process_size % page_size) num_pages++;
    
    for(int p = 0; p < num_pages; p++){

        Disc_Page page(p, pid, page_size);
        process.page_list.push_back(page);

        if(!primary.available_size)
            default_swap();
        
        primary.page_list.push_back(page);
        primary.available_size -= page_size;
    }

    available_size -= (num_pages * page_size);
    process_list.push_back(process);
}

void VirtualMemory::kill_process(int pid){
    printf("KILL -> pro:%d\n",pid);
    find_process_id = pid;
    auto it = find_if(process_list.begin(), process_list.end(), find_process);
    if (it == process_list.end()){
        cout << "   -> PROCESS NOT FOUND" << endl;
        return;
    }

    Process process = *it;
    for(auto itr = primary.page_list.begin(); itr != primary.page_list.end(); itr++){
        Disc_Page page = *itr;
        if(page.pid == process.id){
            primary.available_size += page_size;
            available_size += page_size;
            primary.page_list.erase(itr--);
        }
    }

    for(auto itr = disc.page_list.begin(); itr != disc.page_list.end(); itr++){
        Disc_Page page = *itr;
        if(page.pid == process.id){
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
    find_process_id = pid;
    auto it = find_if(process_list.begin(), process_list.end(), find_process);
    if(it == process_list.end())
        return NULL;
    //else
    //    return new Process();
    /*if(it == process_list.end()){
        cout << "-> PROCESS NOT FOUND AT VM!" << endl;
        it = find_if(wait_process_list.begin(), wait_process_list.end(), find_process);
        if (it != wait_process_list.end()) {
            cout << "   -> PROCESS FOUND AT WAIT LIST!" << endl;
        } else {
            cout << "   -> PROCESS NOT FOUND AT WAIT LIST!" << endl;
            return;
        }
    }*/
    
}

void VirtualMemory::print_process(int pid){
    Process* p = find_process_VM(pid);
    if(p == NULL)
        cout << "-> PROCESS NOT FOUND AT VM!" << endl;
    //cout << "FOUND -> pro:" << p.id << " size:"<< p.size << " pages:"<< p.page_list.size() << endl;

}

void VirtualMemory::command(int pid, int adress){
    //ver qual pagina esta adress
    int num_page = adress / page_size;
    find_process_id = pid;
    find_page_pid = pid;
    find_page_adress = num_page;
    
    // busca na lista de processos
    auto it0 = find_if(process_list.begin(), process_list.end(), find_process);
    
    
    cout << "OPERATE -> pro:" << (*it0).id << " size:"<< (*it0).size << " pages:"<< (*it0).page_list.size() << endl; 
    // adress fora do size do processo
    if(adress >= (*it0).size){
        cout << "   -> UNABLE TO ACESS THIS ADRESS!" << endl;
        return;
    }

    printf("USE PAGE -> page:%d \n",num_page);
    
    // busca na memoria principal
    auto it1 = find_if(primary.page_list.begin(), primary.page_list.end(), find_page);
    // busca na memoria secundaria
    auto it2 = find_if(disc.page_list.begin(), disc.page_list.end(), find_page);

    //caso precise fazer swap
    if(it1 == primary.page_list.end()){
        cout << "   -> SWAPPING PAGES" << endl;
        default_swap();
        (*it2).count++;
        
        primary.page_list.push_back(*it2);
        disc.page_list.erase(it2);
        
        primary.available_size -= page_size;
        disc.available_size += page_size;
    }else{
        primary.page_list[it1 - primary.page_list.begin()].count++;
    }

    cout << "   -> END OF OPERATION" << endl;
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
    swap_memory();
}

void VirtualMemory::swap_relogio(){
    //(falta fazer)
}

void VirtualMemory::swap_memory(){
    primary.available_size += page_size;
    disc.available_size -= page_size;
}

void VirtualMemory::default_swap(){
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
        cout << "Vazia";
    for(Process p : p_list)
        cout << "(ID: " << p.id << ", size: " << p.size << ", pages:" << p.page_list.size() << ") ";
    cout << endl;
}

void VirtualMemory::show(){
    cout << "Lista de Processos: ";
    print_process_list(process_list);
}

void VirtualMemory::print_wait_list(){
    cout << "Lista de Espera: ";
    print_process_list(wait_process_list);
}