#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "arquivo.h"
#include "grafo.h"
#include "fila.h"

typedef struct profundidade{

    char cor;
    int pred;
    int d, f;
    int *adj;

} Profundidade;

typedef struct largura{

    char cor;
    int pred;
    int d;
    int *adj;

} Largura;

int timestamp;

void menu(Grafo* g, char nomeArq[]);

int **buscaEmProfundidade(Grafo* grf, int inicial);

void visita_buscaProf(int vertice, Profundidade* busca, int n, int **ordem);

void beginBuscaProf(Grafo* g, char nomeArq[]);

int** buscaEmLargura(Grafo* g, int origem);

int vertice_origem(Grafo* g);

#endif // ALGORITMOS_H