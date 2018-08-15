#include "usaproduto.h"

UsaProduto::UsaProduto(char nome[], int codigo, float preco, int quantidade, bool infl)
{
    this->infl = new Quimico(codigo, preco,nome, quantidade);
    this->infl->setInfla(infl);
}

void UsaProduto::mostraDados()
{
    this->infl->toString();
}

UsaProduto::~UsaProduto()
{

}
