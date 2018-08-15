#include <iostream>
#include "usaproduto.h"

using namespace std;

int main()
{
    UsaProduto* a = new UsaProduto("Alvejante", 151, 14.95, 2, true);
    Produto *b = new Produto();
    Produto *c = new Produto(12);
    Produto *d = new Produto(12, 22.5, "Nutella", 3);
    Quimico *q = new Quimico();
    Quimico *q1 = new Quimico(178);
    Quimico *q2 = new Quimico(25, 5.32, "Detergente", 4);

    b->printProd();
    cout << endl;

    c->printProd();
    cout << endl;

    d->printProd();
    cout << endl;

    q2->setInfla(true);

    q->toString();
    q1->toString();
    q2->toString();

    a->mostraDados();

    delete a;
    delete b;
    delete c;
    delete d;
    delete q;
    delete q1;
    delete q2;

    return 0;
}
