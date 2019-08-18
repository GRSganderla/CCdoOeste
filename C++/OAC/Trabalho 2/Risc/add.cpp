#include "add.h"

ADD::ADD(unsigned int a, unsigned int b)
{
    A = a;
    B = b;
    result = A+B;
}

unsigned int ADD::get_result(){

    return result;
}

ADD::~ADD()
{

}
