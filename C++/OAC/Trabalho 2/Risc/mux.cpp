#include "mux.h"

MUX::MUX(unsigned int A, unsigned int B, bool selecao)
{
    this->in_A = A;
    this->in_B = B;
    this->result = (selecao)? A : B;
}

unsigned int MUX::get_result(){

    return this->result;
}

MUX::~MUX(){

}
