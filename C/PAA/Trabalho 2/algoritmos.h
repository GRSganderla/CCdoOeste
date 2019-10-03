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

typedef struct bellmanford {

    int d;
    int pred;
} BellmanFord;

int timestamp;

void menu(Grafo* g, char nomeArq[]);

void buscaEmProfundidade(Grafo* grf, int inicial, int** res);

void visita_buscaProf(int vertice, Profundidade* busca, int n, int **ordem);

void beginBuscaProf(Grafo* g, char nomeArq[]);

int buscaEmLargura(Grafo* g, int origem, int** res);

int vertice_origem(Grafo* g);

int BellmanFordAlg(Grafo* g, int origem, int** res);

void relax(BellmanFord* bf, int** pesos, int u, int v);

BellmanFord* inicializaOrigem(int n, int origem);

#endif // ALGORITMOS_H