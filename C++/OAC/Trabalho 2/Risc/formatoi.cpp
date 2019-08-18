#include "formatoi.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

unsigned int FormatoI::getOpcode()
{
    return opcode;
}

void FormatoI::setOpcode(unsigned int s)
{
    opcode = s;
}

void FormatoI::setRs(unsigned int s)
{
    rs = s;
}

unsigned int FormatoI::getRt()
{
    return rt;
}

void FormatoI::setRt(unsigned int s)
{
    rt = s;
}

unsigned int FormatoI::getOffset()
{
    return offset;
}

void FormatoI::setOffset(unsigned int s)
{
    offset = s;
}

FormatoI::FormatoI(unsigned int op,unsigned int rrs,unsigned int rrt,unsigned int Offset)
{
    opcode = op;
    rs = rrs;
    rt = rrt;
    offset = Offset;
}

void FormatoI::show_Objeto()
{
     cout << "opcode contem: " << opcode << endl;
     cout << "rs contem: " << rs << endl;
     cout << "rt contem: " << rt << endl;
     cout << "offset contem: " << offset << endl;
}

void FormatoI::Update()
{
    opcode = 0;
    rt = 0;
    rs = 0;
    offset= 0;
}
