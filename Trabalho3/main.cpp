#include "headers/Globals.h"
#include "headers/VirtualMemory.h"

void help(){
    cout << "If you enter any unspecified command, the loop will return to input a command.\n\nCommands list and arguments::" << endl;
    cout << "(Creates a new process): C pid size" << endl;
    cout << "(Kill a process by his pid): K pid" << endl;
    cout << "(Print Memory RAM and DISC): P" << endl;
    cout << "(Print the list of process at Virtual Memory): S" << endl;
    cout << "(List the waiting processes): W" << endl;
    cout << "(Make an operation of R/W or I/O at process address): O pid adress" << endl;
    cout << "(Print information about a process): F pid" << endl;
    cout << "(Show help): H" << endl;
    cout << "(Exit the simulator): E" << endl;
}

int main(){
    int size_pag = 4;
    printf("RAM: %02d \t DISCO: %02d\n", MEM_DISC, MEM_DISC);
    cout << "Page size: " << size_pag << endl << endl;
    //cin >> size_pag;
    
    VirtualMemory vm(size_pag);

    printf("LRU: %02d \t Clock: %02d\n", SWAP_LRU, SWAP_CLOCK);
    printf("Select swap algorithm: ");
    cin >> vm.std_swap_type;

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

            case 'H':
                help();
                break;

            case 'E':
                cout << "END OF OPERATION\n";
                return 0;

            default:
                cout << "Unknow command!\n" << endl;
                break;
        }

    } while (true);
    
    return 0;
}
