#include "control.h"
#include <iostream>

using namespace std;

Control::Control()
{
    this->Jump = false;
    this->ALUop0 = false;
    this->ALUop1 = false;
    this->AluSrc = false;
    this->Branch0 = false;
    this->Branch1 = false;
    this->RegDst = false;
    this->MemRead = false;
    this->MemWrite = false;
    this->MemtoReg = false;
    this->RegWrite = false;
}

void Control::reset(){

    this->Jump = false;
    this->ALUop0 = false;
    this->ALUop1 = false;
    this->AluSrc = false;
    this->Branch0 = false;
    this->Branch1 = false;
    this->RegDst = false;
    this->MemRead = false;
    this->MemWrite = false;
    this->MemtoReg = false;
    this->RegWrite = false;
}

void Control::set_control(unsigned int opcode){

    this->reset();

    switch (opcode) {

        case R: // Formato R
            RegDst = true;
            RegWrite = true;
            ALUop1 = true;
        break;
        case 2: // j Formato J
            Jump = true;
        break;
        case BEQ: // beq Formato I
            Branch0 = true;
            Branch1 = false;
            ALUop0 = true;
        break;
        case BNE: // bne Formato I
            Branch1 = true;
            Branch0 = false;
            ALUop0 = true;
        break;
        case LI: // li Formato I
            RegWrite = true;
            RegDst = false;
            AluSrc = true;
        break;
        case LW: // lw Formato I
            AluSrc = true;
            MemtoReg = true;
            RegWrite = true;
            MemRead = true;
        break;
        case SW: // sw Formato I
            AluSrc = true;
            MemWrite = true;
        break;
    }
}

bool Control::get_RegDst(){
    return RegDst;
}

bool Control::get_Jump(){
    return Jump;
}

bool Control::get_Branch0(){
    return Branch0;
}

bool Control::get_Branch1(){
    return Branch1;
}

bool Control::get_MemRead(){
    return MemRead;
}

bool Control::get_MemtoReg(){
    return MemtoReg;
}

bool Control::get_ALUop0(){
    return ALUop0;
}

bool Control::get_ALUop1(){
    return ALUop1;
}

bool Control::get_MemWrite(){
    return MemWrite;
}

bool Control::get_AluSrc(){
    return AluSrc;
}

bool Control::get_RegWrite(){
    return RegWrite;
}

void Control::show_contr(){

    cout << "Jump: " << Jump << endl;
    cout << "ALUop0: " << ALUop0 << endl;
    cout << "ALUop1: " << ALUop1 << endl;
    cout << "AluSrc: " << AluSrc << endl;
    cout << "Branch0: " << Branch0 << endl;
    cout << "Branch1: " << Branch1 << endl;
    cout << "RegDst: " << RegDst << endl;
    cout << "MemRead: " << MemRead << endl;
    cout << "MemWrite: " << MemWrite << endl;
    cout << "MemtoReg: " << MemtoReg << endl;
    cout << "RegWrite: " << RegWrite << endl;
}

Control::~Control(){

}
