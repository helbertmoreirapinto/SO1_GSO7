#include "headers/Process.h"

Process::Process(int id, int size){
    this->id = id;
    this->size = size;
}

Process::Process(){
    this->id = -1;
    this->size = 0; 
}