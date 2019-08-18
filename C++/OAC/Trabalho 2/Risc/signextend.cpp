#include "signextend.h"
#include <cstdint>

using namespace std;

SignExtend::SignExtend(unsigned int in)
{
    this->input = in;

    int16_t lex = in;

    this->output = ((int32_t) lex);
}

unsigned int SignExtend::get_output(){

    return this->output;
}

SignExtend::~SignExtend(){

}
