#ifndef QUIMICO_H
#define QUIMICO_H
#include "produto.h"

class Quimico : public Produto
{
private:
    bool inflamavel;
public:
    Quimico();
    Quimico(int codigo);
    Quimico(int codigo, float preco, char nome[], int quantidade);
    void setInfla(bool inflamavel);
    bool getInfla();
    void toString();
    ~Quimico();
};

#endif // QUIMICO_H
