#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fila.h"
#define MAX 100
#define ORDEM 5

typedef struct cadastro
{
	int codigo;
	char nome[100];
	char sexo;
	char cpf[12];
	char crm[20];
	char especialidade[100];
	char rg[12];
	char telefone[13];
	char celular[14];
	char email[100];
	char endereco[100];
	char nascimento[11];
}Cadastro;

typedef struct noBArqDat
{
	//variaves da cabeca do arquivo e a raiz dos nós livres
	int topo;
	int nohsLivre;
}CabecalhoDados;

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

void escreveCabecalhoDat(FILE* registros, CabecalhoDados* indice);

void criaIndicesArqDat(FILE *binario);

int soNumero(char *s);

void lerArquivo(FILE* dados, FILE* arvore, char* nome);

///
/// \brief inicializaCadastro, aloca e inicializa as variaveis da estrutura Cadastro
/// \return uma estrutura de dados do tipo Cadastro alocada
/// \pre nenhuma
/// \post nenhuma
///
Cadastro inicializaCadastro();

void liberaNoh(ArvoreB* alvo);

void criaIndicesArq(FILE *binario);

ArvoreB* inicializaArvore();

Cabecalho* leituraDoCabecalho(FILE* binario);

ArvoreB* leituraDoNoh(FILE* binario, int posicao);

void escreveCabecalho(FILE* registros, Cabecalho* indice);

int escreveArvore(FILE* registros, ArvoreB* galho, Cabecalho* indice);

Livres* criaNohLivre();