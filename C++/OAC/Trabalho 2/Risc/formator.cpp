#include "formator.h"
#include <iostream>

using namespace std;

unsigned int FormatoR::getOpcode()
{
    return opcode;
}

void FormatoR::setOpcode(unsigned int s)
{
    opcode = s;
}

unsigned int FormatoR::getRd()
{
    return rd;
}

void FormatoR::setRd(unsigned int s)
{
    rd = s;
}

unsigned int FormatoR::getRs()
{
    return rs;
}

void FormatoR::setRs(unsigned int s)
{
    rs = s;
}

unsigned int FormatoR::getRt()
{
    return rt;
}

void FormatoR::setRt(unsigned int s)
{
    rt = s;
}

unsigned int FormatoR::getShamt()
{
    return shamt;
}

void FormatoR::setShamt(unsigned int s)
{
    shamt = s;
}

unsigned int FormatoR::getFunct()
{
    return funct;
}

void FormatoR::setFunct(unsigned int s)
{
    funct = s;
}

FormatoR::FormatoR(unsigned int op,unsigned int rrd,unsigned int rrs,unsigned int rrt,unsigned int shamtt,unsigned int functt)
{
    opcode = op;
    rd = rrd;
    rt = rrt;
    rs = rrs;
    shamt = shamtt;
    funct = functt;
}

void FormatoR::show_Objeto()
{
    cout << "opcode contem: " << opcode << endl;
    cout << "rd contem: " << rd << endl;
    cout << "rs contem: " << rs << endl;
    cout << "rt contem: " << rt << endl;
    cout << "shamt contem: " << shamt << endl;
    cout << "funct contem: " << funct << endl;
}

void FormatoR::Update()
{
    opcode = 0;
    rd = 0;
    rt = 0;
    rs = 0;
    shamt = 0;
    funct = 0;
}
