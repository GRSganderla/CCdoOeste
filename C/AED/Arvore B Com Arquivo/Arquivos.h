#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fila.h"
#include "Cadastro.h"
#define ORDEM 5

//estrutura para o cabecalho do arquivo
typedef struct noBArq
{
	//variaves da cabeca do arquivo, sendo a raiz do arquivo, a quantidade de nós, a raiz dos nós livres e sua quantidade
	int topo;
	int quantidade;
	int nohsLivre;
	int quantidadeLivre;
}Cabecalho;

typedef struct registros
{
	int codigo;
	int registroPos;
}RegistrosDat;

typedef struct arvoreB
{
	int numChaves;
	int posicao;
	RegistrosDat chave[ORDEM];
	int filho[ORDEM];
}ArvoreB;

typedef struct nohLivre
{
	int prox;
}Livres;

void liberaNoh(ArvoreB* alvo);

void criaIndicesArq(FILE *binario);

ArvoreB* inicializaArvore();

Cabecalho* leituraDoCabecalho(FILE* binario);

ArvoreB* leituraDoNoh(FILE* binario, int posicao);

void escreveCabecalho(FILE* registros, Cabecalho* indice);

int escreveArvore(FILE* registros, ArvoreB* galho, Cabecalho* indice);