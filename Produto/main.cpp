#include <iostream>
#include "produto.h"

using namespace std;

int main()
{
    Produto *a = new Produto();

    a->setCodigo(151);
    a->setNome("Alvejante");
    a->setPreco(14.95);
    a->setQuant(2);

    a->printProd();

    delete a;

    return 0;
}
