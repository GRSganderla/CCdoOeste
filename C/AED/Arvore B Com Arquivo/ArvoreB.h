#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ORDEM 5

typedef struct cadastro
{
	int codigo;
	char *nome;
	char sexo;
	char *cpf;
	int crm;
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
	int chave[ORDEM-1];
	struct arvoreB* filho[ORDEM];
}ArvoreB;

int overflow(ArvoreB* r);

int vazia(ArvoreB* r);

ArvoreB* split(ArvoreB* x, int *m);

int buscaPos(ArvoreB* r, int info, int * pos);

int eh_folha(ArvoreB* r);

void adicionaDireita(ArvoreB* r, int pos, int k, ArvoreB* p);

void insere_aux(ArvoreB* r, int info);

ArvoreB* insere(ArvoreB* r, int info);

ArvoreB* busca(ArvoreB* r, int info, int * pos);

int altura(ArvoreB* r);

void printaNivelB(ArvoreB* r, int i);

void printaPorNivelB(ArvoreB* r);

ArvoreB* inicializaArvore();

void lerCadastro(Cadastro hospital[]);

Cadastro* inicializaCadastro();