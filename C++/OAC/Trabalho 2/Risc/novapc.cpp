#include "novapc.h"
#include <iostream>

using namespace std;

NovaPc::NovaPc(){

    this->jmp = 0b0;
    this->Jump = false;
    this->Zero = false;
    this->pc_4 = 0b0;
    this->end_b = 0b0;
    this->Branch0 = false;
    this->Branch1 = false;
}

void NovaPc::set_pc4(unsigned int pc){
    this->pc_4 = pc;
}

void NovaPc::set_endb(unsigned int end){
    this->end_b = end;
}

void NovaPc::set_jmp(unsigned int jmp){
    this->jmp = jmp;
}

void NovaPc::set_bools(bool B0, bool B1, bool Z, bool J){
    this->Jump = J;
    this->Zero = Z;
    this->Branch0 = B0;
    this->Branch1 = B1;
}

bool AND(bool A, bool B){
    return (A && B);
}

unsigned int NovaPc::get_novo_pc(){

    return this->novo_pc;
}

void NovaPc::det_novo_pc(){

    bool selecao = (AND(AND(this->Branch0, !this->Branch1), this->Zero)) || (AND(AND(this->Branch1, !this->Branch0), !this->Zero));

    ADD* novo = new ADD(this->pc_4, this->end_b);

    MUX* pc_ou_b = new MUX(novo->get_result(), this->pc_4, selecao);

    MUX* jmp_ou_end = new MUX(this->jmp, pc_ou_b->get_result(), this->Jump);

    this->novo_pc = jmp_ou_end->get_result();
}

NovaPc::~NovaPc(){

}
