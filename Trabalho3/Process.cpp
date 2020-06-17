#include "headers/Process.h"

// id - process identifier
// size - size process
Process::Process(int id, int size){
    this->id = id;
    this->size = size;
}

// standard process initialization
Process::Process(){
    this->id = -1;
    this->size = 0; 
}