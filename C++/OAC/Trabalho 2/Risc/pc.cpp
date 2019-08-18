#include "pc.h"

PC::PC()
{
    this->input = 0;
    this->output = 0;
}

void PC::update(unsigned int endereco){

    this->input = endereco;
    this->output = this->input;
}

unsigned int PC::get_output(){
    return this->output;
}

PC::~PC(){

}
