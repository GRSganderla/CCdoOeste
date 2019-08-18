#include "registradores.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Registradores::Registradores()
{
    for(int i = 0; i < 32; i++){

        this->Reg[i] = 0b0;
    }

    ReadReg1 = 0b0;
    ReadReg2 = 0b0;
    WriteReg = 0b0;
    ReadData1 = 0b0;
    ReadData2 = 0b0;
}

void Registradores::show(){

    for (int i = 0; i < 32; i++) {

        if(Reg[i] != 0b0) printf("Reg[ %d ] = %d\n", i, Reg[i]);
    }
}

void Registradores::set_RegWrite(bool reg){

    this->RegWrite = reg;
}

string Registradores::get_nome(unsigned int endereco){

    string rg_nome;

    rg_nome.append("$");

    rg_nome.append(to_string(endereco));

    return rg_nome;
}

void Registradores::set_regs(unsigned int r1, unsigned int r2, unsigned int w){

    this->ReadReg1 = Reg[r1];
    this->ReadReg2 = Reg[r2];
    this->WriteReg = w;
    this->ReadData1 = ReadReg1;
    this->ReadData2 = ReadReg2;
}

unsigned int Registradores::get_ReadData2(){

    return this->ReadData2;
}

unsigned int Registradores::get_Reg(int endereco){

    if(endereco < 0b10) return 0b0;
    return Reg[endereco];
}

void Registradores::set_WriteData(unsigned int data){

    this->WriteData = data;
}

void Registradores::write_Reg(){

    if(RegWrite){

        this->Reg[WriteReg] = WriteData;
    }
}

void Registradores::update(){

    ReadReg1 = 0b0;
    ReadReg2 = 0b0;
    WriteReg = 0b0;
    ReadData1 = 0b0;
    ReadData2 = 0b0;
}

Registradores::~Registradores(){

}
