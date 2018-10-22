#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fila.h"
#define ORDEM 5

typedef struct noBArq
{
	int cabecalho;
	int quantidade;
	int nohsLivre;
	int quantidadeLivre;
}Cabecalho;

typedef struct cadastro
{
	int codigo;
	char *nome;
	char *sexo;
	char *cpf;
	char *crm;
	char *especialidade;
	char *rg;
	char *telefone;
	char *celular;
	char *email;
	char *endereco;
	char *nascimento;
}Cadastro;

typedef struct arvoreB
{
	int numChaves;
	int posicao;
	int chave[ORDEM];
	int dados[ORDEM];
	int filho[ORDEM];
}ArvoreB;

typedef struct nohLivre
{
	int prox;
}Livres;

void liberaNoh(ArvoreB* alvo);

Cadastro* lerArquivo();

void printaCadastro(Cadastro* medicos);

Cadastro* inicializaCadastro();

void criaIndicesArq(FILE *binario);

ArvoreB* inicializaArvore();

Cabecalho* leituraDoCabecalho(FILE* binario);

ArvoreB* leituraDoNoh(FILE* binario, int posicao);

void escreveCabecalho(FILE* registros, Cabecalho* indice);

int escreveArvore(FILE* registros, ArvoreB* galho, Cabecalho* indice);