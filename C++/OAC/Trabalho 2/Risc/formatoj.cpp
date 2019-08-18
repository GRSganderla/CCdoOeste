#include "formatoj.h"

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

unsigned int FormatoJ::getOpcode()
{
    return opcode;
}

void FormatoJ::setOpcode(unsigned int s)
{
    opcode = s;
}

void FormatoJ::setEndereco(unsigned int s)
{
    endereco = s;
}

unsigned int FormatoJ::getEndereco()
{
    return endereco;
}

FormatoJ::FormatoJ(unsigned int op,unsigned int end)
{
    opcode = op;
    endereco = end;
}

void FormatoJ::show_Objeto()
{
    cout << "opcode contem: " << opcode << endl;
    cout << "end contem: " << endereco << endl;
}

void FormatoJ::Update()
{
    opcode = 0;
    endereco = 0;
}
