#include "produto.h"
#include<string.h>
#include<iostream>

using namespace std;

Produto::Produto()
{
    this->codigo = 0;
    this->quantidade = 0;
    this->preco = 0.0;
    this->nome[50] = {};
}

Produto::Produto(int codigo)
{
    this->codigo = codigo;
    this->quantidade = 0;
    this->preco = 0.0;
    this->nome[50] = {};
}

Produto::Produto(int codigo, float preco, char nome[], int quantidade)
{
    this->codigo = codigo;
    this->quantidade = quantidade;
    this->preco = preco;
    strcpy(this->nome, nome);
}

void Produto::setCodigo(int codigo)
{
    this->codigo = codigo;
}

void Produto::setNome(char nome[])
{
    strcpy(this->nome, nome);
}

void Produto::setQuant(int quantidade)
{
    this->quantidade = quantidade;
}

void Produto::printProd()
{
    cout << this->nome << ":" << endl;
    cout << "Codigo: " << this->codigo << endl;
    cout << "Preco: " << this->preco << endl;
    cout << "Quantidade: " << this->quantidade << endl;
    cout << "Total: " << this->totaliza() << endl;
}

void Produto::setPreco(float preco)
{
    this->preco = preco;
}

int Produto::getCodigo()
{
    return this->codigo;
}

char* Produto::getNome()
{
    return this->nome;
}

int Produto::getQuant()
{
    return this->quantidade;
}

float Produto::getPreco()
{
    return this->preco;
}

void Produto::upPreco(int porcentagem)
{
    float p = porcentagem/100;
    this->preco = this->preco + this->preco/p;
}

float Produto::totaliza()
{
    return (this->preco * this->quantidade);
}

void Produto::toString(int* codigo, float* preco, char nome[], int* quantidade, float *total)
{
    *codigo = this->codigo;
    *preco = this->preco;
    strcpy(nome, this->nome);
    *quantidade = this->quantidade;
    *total = this->totaliza();
}

Produto::~Produto()
{

}
