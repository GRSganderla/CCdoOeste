#include "quimico.h"
#include<iostream>
#include "produto.h"
#include<string>

using namespace std;

Quimico::Quimico()
{
    this->inflamavel = false;
}

Quimico::Quimico( int codigo) : Produto(codigo)
{
    this->inflamavel = false;
}

Quimico::Quimico(int codigo, float preco, char nome[], int quantidade) : Produto(codigo, preco, nome, quantidade)
{
    this->inflamavel = false;
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

    if(this->inflamavel == false)
        cout << "Nao ";
    cout << "Inflamavel!" << endl;
    cout << endl;
}

Quimico::~Quimico()
{

}
