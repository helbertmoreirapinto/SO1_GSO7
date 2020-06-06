#include "VirtualMemory.h"
#include "Globals.h"

int main(){
    cout << "Tamanho da pagina: ";
    int size_pag; cin >> size_pag;

    VirtualMemory vm(size_pag);

    vm.allocate_process(1, 5);
    vm.allocate_process(2, 10);
    vm.allocate_process(3, 16);
    vm.print(); // for debug
    return 0;
}