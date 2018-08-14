#include "usaproduto.h"

UsaProduto::UsaProduto(char nome[], int codigo, float preco, int quantidade, bool infl)
{
    this->item = new Produto(codigo, preco,nome, quantidade);
    this->infl = new Quimico(infl);
}

void UsaProduto::mostraDados()
{
    this->item->printProd();
    this->infl->toString();
}

UsaProduto::~UsaProduto()
{

}
