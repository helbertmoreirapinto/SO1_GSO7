#include "headers/Globals.h"
#include "headers/VirtualMemory.h"

int main(){
    cout << "RAM:" << MEM_RAM << endl;
    cout << "DISCO:" << MEM_DISC << endl;

    cout << "Tamanho da pagina: ";
    int size_pag;
    cin >> size_pag;

    VirtualMemory vm(size_pag);

    bool exit_while = false;
    do{
        int pid, size;
        char command;
        cout << endl << "Comando: ";
        cin >> command;

        switch (command){
            case 'C':
                cin >> pid >> size;
                vm.allocate_process(pid, size);
                break;
            
            case 'P':
                vm.print();
                break;
            
            case 'S':
                vm.show();
                break;
            
            case 'W':
                vm.print_wait_list();
                break;

            case 'K':
                cin >> pid;
                vm.kill_process(pid);
                break;
            
            case 'O': // "Operation"
                cin >> pid >> size;
                vm.command(pid, size);
                break;

            case 'F':
                cin >> pid;
                vm.print_process(pid);
                break;

            case 'E':
                return 0;

            default:
                exit_while = true;
                break;
        }

    } while (!exit_while);
    
    return 0;
}