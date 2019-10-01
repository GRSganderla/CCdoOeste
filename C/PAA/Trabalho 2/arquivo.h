#ifndef ARQUIVO_H
#define ARQUIVO_H

#include<stdio.h>
#include<stdlib.h>
#include "grafo.h"

void leArquivo(FILE* in);

void fazArquivoDot(Grafo* grf, FILE* out);

#endif // ARQUIVO_H