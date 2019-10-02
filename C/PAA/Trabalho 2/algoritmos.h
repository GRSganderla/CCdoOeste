#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "arquivo.h"
#include "grafo.h"

typedef struct profundidade{

    char cor;
    int pred;
    int d, f;
    int *adj;

} Profundidade;

void menu(Grafo* g, char nomeArq[]);

int **buscaEmProfundidade(Grafo* grf, int inicial);

void visita_buscaProf(int vertice, Profundidade* busca, int n, int **ordem);

void beginBuscaProf(Grafo* g, char nomeArq[]);

#endif // ALGORITMOS_H