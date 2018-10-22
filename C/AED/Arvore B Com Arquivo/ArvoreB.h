#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Arquivos.h"

Cadastro* inicializaCadastro();

///
/// \brief overflow, funcao que testa se o nó atual 
/// \param 
/// \return 
/// \pre nenhuma
/// \post nenhuma
///
int overflow(ArvoreB* r);

///
/// \brief 
/// \param 
/// \return 
/// \pre nenhuma
/// \post nenhuma
///
int vazia(ArvoreB* r);

ArvoreB* split(ArvoreB* x, int *m);

int buscaPos(ArvoreB* r, int info, int * pos);

int eh_folha(ArvoreB* r);

void adicionaDireita(ArvoreB* r, int pos, int k, int p);

void insere_aux(FILE* registros, Cabecalho* indice, ArvoreB* r, int info);

void insere(FILE* registros, int info);

void printaArvore(FILE* registros);
