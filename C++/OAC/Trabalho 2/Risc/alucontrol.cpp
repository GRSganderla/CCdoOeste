#include "alucontrol.h"

ALUcontrol::ALUcontrol(unsigned int input, bool ALUop0, bool ALUop1)
{
    if(!ALUop0 && !ALUop1){

        this->output = 2;
    }
    else if(ALUop0 && !ALUop1){

        this->output = 6;
    }
    else if(!ALUop0 && ALUop1){

        switch (input) {

            case 8:
                this->output = 10;
            break;
            case 32:
                this->output = 2;
            break;
            case 34:
                this->output = 6;
            break;
            case 36:
                this->output = 0;
            break;
            case 37:
                this->output = 1;
            break;
            case 42:
                this->output = 7;
            break;
        }
    }
}

unsigned int ALUcontrol::get_output(){

    return this->output;
}

void ALUcontrol::update(){

    this->input = 0b0;
    this->output = 0b0;
}

ALUcontrol::~ALUcontrol(){

}
