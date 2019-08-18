#include "shiftleft.h"

ShiftLeft::ShiftLeft(unsigned int a)
{
    this->A = a;
    this->result = a << 0b10;
}

unsigned int ShiftLeft::get_result(){
    return this->result;
}

ShiftLeft::~ShiftLeft(){

}
