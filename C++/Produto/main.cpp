#include <iostream>
#include "produto.h"
#include "quimico.h"

using namespace std;

int main()
{
    Produto *a = new Produto();
    Quimico *i = new Quimico(true);

    a->setCodigo(151);
    a->setNome("Alvejante");
    a->setPreco(14.95);
    a->setQuant(2);

    a->printProd();
    i->toString();

    delete a;

    return 0;
}
