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

typedef struct aresta {

    int u, v;
    int peso;
} Aresta;

typedef struct kruskal{

    Aresta* A;
}Kruskal;

typedef struct prim{
    int conhecido;
    int key;
    int pred;
    int *adj;
} Prim;

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

int PrimAlgm(Grafo* g, int r, int** res);

int KruskalAlgm(Grafo* g, int **res);

Aresta* fazAresta(Grafo* g, int *n);

int jaExiste(int i, int j, int peso, Aresta* e, int n);

void Uniao(int u, int v, int *conj);

void troca(int u, int v, int *conj);

int diferente(int u, int v, int *conj);

int findV(int alvo, int *conj);
///
/// \brief mergeSortN, algoritmo de ordenação por metodo de separar, ordenar e reajuntar e ordenar...
/// \param v, vetor a ser ordenado
/// \param inicio, indice do inicio do vetor
/// \param fim, tamanho maximo do vetor
/// \pre nenhuma
/// \post nenhuma
///
void mergeSortN(Aresta* v, int inicio, int fim);
///
/// \brief intercala, função auxiliar do algoritmo de ordenação Merge Sort
/// \param vet, vetor a ser ordenado
/// \param inicio, indice do inicio da parte do vetor separada
/// \param meio, indice do meio do vetor partido
/// \param fim, tamanho maximo da partição
/// \pre nenhuma
/// \post nenhuma
///
void intercala(Aresta* vet, int inicio, int meio, int fim);

#endif // ALGORITMOS_H