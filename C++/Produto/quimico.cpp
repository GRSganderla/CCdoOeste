#include "quimico.h"
#include<iostream>
#include "produto.h"

using namespace std;

Quimico::Quimico(bool inflamavel) : Produto()
{
    this->inflamavel = inflamavel;
}

void Quimico::setInfla(bool inflamavel)
{
    this->inflamavel = inflamavel;
}

bool Quimico::getInfla()
{
    return this->inflamavel;
}

void Quimico::toString()
{
    this->printProd();
    if(this->inflamavel == true)
        cout << "Inflamavel!" << endl;
}

Quimico::~Quimico()
{

}
