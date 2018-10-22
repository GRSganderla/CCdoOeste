#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fila.h"
#include "Cadastro.h"

void liberaNoh(ArvoreB* alvo);

void criaIndicesArq(FILE *binario);

ArvoreB* inicializaArvore();

Cabecalho* leituraDoCabecalho(FILE* binario);

ArvoreB* leituraDoNoh(FILE* binario, int posicao);

void escreveCabecalho(FILE* registros, Cabecalho* indice);

int escreveArvore(FILE* registros, ArvoreB* galho, Cabecalho* indice);

Livres* criaNohLivre();