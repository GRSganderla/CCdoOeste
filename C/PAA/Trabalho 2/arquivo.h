#ifndef ARQUIVO_H
#define ARQUIVO_H

#include<stdio.h>
#include<stdlib.h>
#include "grafo.h"

#define LINHA_ORIENTADO 1;
#define LINHA_ROTULO_VERTICES 2;
#define LINHA_N_VERTICES 3;
#define LINHA_ARESTAS 4;

void fazArquivoAlg(Grafo* g, FILE* out, int** res);

Grafo* leArquivo(FILE* in);

void fazArquivoDot(Grafo* grf, FILE* out);

#endif // ARQUIVO_H