#include "VirtualMemory.h"
#include "Globals.h"

int main(){
    cout << "Tamanho da pagina: ";
    int size_pag; cin >> size_pag;

    VirtualMemory vm(size_pag);
    
    return 0;
}