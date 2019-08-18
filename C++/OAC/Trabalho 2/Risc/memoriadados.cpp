#include "memoriadados.h"

#include <iostream>

using namespace std;

MemoriaDados::MemoriaDados()
{
    for(int i = 0; i < 1000; i++)
        this->memoria[i] = 0b0;

    this->MemRead = false;
    this->Address = 0b0;
    this->MemWrite = false;
    this->ReadData = 0b0;
    this->WriteData = 0b0;
}

void MemoriaDados::set_input(unsigned int ender, unsigned int dados){

    this->Address = ender;
    this->WriteData = dados;
}

void MemoriaDados::set_mem(bool write, bool read){

    this->MemWrite = write;
    this->MemRead = read;
}

void MemoriaDados::le(){

    if(MemRead){

        ReadData = this->memoria[this->Address];
    }
}

void MemoriaDados::escreve(){

    if(MemWrite){

        this->memoria[this->Address] = this->WriteData;
    }
}

unsigned int MemoriaDados::get_read(){

    if(MemRead) return this->ReadData;

    return 0b0;
}

void MemoriaDados::showMemo(){

    for (int i = 0; i < 1000; i++) {
        if(memoria[i] != 0b0) printf("Mem[ %d ] = %u\n", i,  memoria[i]);
    }
}

MemoriaDados::~MemoriaDados(){

}
