#include "quimico.h"
#include<iostream>
#include "produto.h"

using namespace std;

Quimico::Quimico(bool inflamavel)
{
    this->inflamavel = inflamavel;
}

Quimico::Quimico(bool inflamavel) : Produto(int codigo)
{
    this->inflamavel = inflamavel;
}

Quimico::Quimico(bool inflamavel) : Produto(int codigo, float preco, char nome[], int quantidade)
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
    if(this->inflamavel == true)
        cout << "Inflamavel!" << endl;
}

Quimico::~Quimico()
{

}
