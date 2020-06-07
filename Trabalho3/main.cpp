#include "headers/Globals.h"
#include "headers/VirtualMemory.h"

int main(){
    cout << "RAM:" << MEM_RAM << endl;
    cout << "DISCO:" << MEM_DISC << endl;

    cout << "Tamanho da pagina: ";
    int size_pag; cin >> size_pag;

    VirtualMemory vm(size_pag);

    vm.allocate_process(1, 42);
    vm.print(); // for debug

    vm.allocate_process(2, 10);
    vm.print(); // for debug
    
    vm.command(1, 7);
    vm.print();

    vm.allocate_process(3, 40);
    vm.print(); // for debug

    vm.kill_process(1);
    vm.print(); // for debug

    return 0;
}