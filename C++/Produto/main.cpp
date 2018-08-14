#include <iostream>
#include "usaproduto.h"

using namespace std;

int main()
{
    UsaProduto* a = new UsaProduto("Alvejante", 151, 14.95, 2, true);

    a->mostraDados();

    delete a;

    return 0;
}
