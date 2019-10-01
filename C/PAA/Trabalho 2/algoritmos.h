#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "grafo.h"

typedef struct profundidade{

    char cor;
    int pred;
    int d, f;
    int *adj;

} Profundidade;

int **buscaEmProfundidade(Grafo* grf, int inicial);

#endif // ALGORITMOS_H