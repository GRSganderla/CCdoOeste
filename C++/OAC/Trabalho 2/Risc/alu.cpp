#include "alu.h"
#include <string>
#include <iostream>
using namespace std;

ALU::ALU(unsigned int A, unsigned int B)
{
    this->A = A;
    this->B = B;

    this->executa();
}

bool ALU::get_zero(){

    return zero;
}

void ALU::set_funcao(unsigned int fun){

    this->funcao = fun;
}

string ALU::get_nome(unsigned int opcode, unsigned int funct){

    if(opcode == 0){

        switch(funct){

            case 8:
                return "jr ";
            case 32:
                return "add ";
            case 34:
                 return "sub ";
            case 36:
                return "and ";
            case 37:
                return "or ";
            case 42:
                return "slt ";
        }
    }
    else {

        switch (opcode) {

            case 2:
                return "jmp ";
            case 4:
                return "beq ";
            case 5:
                return "bne ";
            case 15:
                return "li ";
            case 35:
                return "lw ";
            case 43:
                return "sw ";
        }
    }

    return "erro";
}

void ALU::executa(){

    switch(this->funcao){

        case ADD:
            this->ALUres = A+B;
        break;
        case SUB:
            this->ALUres = A-B;
        break;
        case AND:
            this->ALUres = A & B;
        break;
        case OR:
            this->ALUres = A | B;
        break;
        case SLT:
            if(B < A) this->ALUres = 1;
            else this->ALUres = 0;
        break;
    }

    this->zero = (this->ALUres == 0);
}

unsigned int ALU::get_res(){

    return this->ALUres;
}

ALU::~ALU(){

}
