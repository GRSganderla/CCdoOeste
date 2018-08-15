#ifndef QUIMICO_H
#define QUIMICO_H
#include "produto.h"

class Quimico : public Produto
{
private:
    bool inflamavel;
public:
    Quimico(bool inflamavel = false);
    Quimico(bool inflamavel = false, int codigo);
    Quimico(bool inflamavel = false, int codigo, float preco, char nome[], int quantidade);
    void setInfla(bool inflamavel);
    bool getInfla();
    void toString();
    ~Quimico();
};

#endif // QUIMICO_H
