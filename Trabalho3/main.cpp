#include "VirtualMemory.h"
#include "Globals.h"

int main(){
    cout << "Tamanho da pagina: ";
    int size_pag; cin >> size_pag;

    VirtualMemory vm(size_pag);

    vm.allocate_process(0, 100);
    vm.print(); // for debug

    vm.allocate_process(2, 500);
    vm.allocate_process(3, 100);
    return 0;
}