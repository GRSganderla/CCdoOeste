#ifndef USAPRODUTO_H
#define USAPRODUTO_H
#include "quimico.h"

class UsaProduto
{
private:
    Produto* item;
    Quimico* infl;
public:
    UsaProduto(char nome[], int codigo, float preco, int quantidade, bool infl);
    void mostraDados();
    ~UsaProduto();
};

#endif // USAPRODUTO_H
