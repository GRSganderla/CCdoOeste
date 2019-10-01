#ifndef GRAFO_H
#define GRAFO_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct label {
    char nome[100];
} Label;

typedef struct grafo{
    int **adjacente, nVertices, EhRotulado, **pesos;
    Label **rotulos, *nomes;
    char orientado[4];
} Grafo;

Grafo* initGrafo(char orientado[]);

Label** initLabels(int v);

int ** init(int v);

#endif // GRAFO_H