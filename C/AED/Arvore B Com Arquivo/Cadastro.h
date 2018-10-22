#include<stdio.h>
#define MAX 100

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

void escreveCabecalhoDat(FILE* registros, CabecalhoDados* indice);

void criaIndicesArqDat(FILE *binario);

int soNumero(char *s);

Cadastro* lerArquivo(char* nome);

void printaCadastro(Cadastro* medicos);

///
/// \brief inicializaCadastro, aloca e inicializa as variaveis da estrutura Cadastro
/// \return uma estrutura de dados do tipo Cadastro alocada
/// \pre nenhuma
/// \post nenhuma
///
Cadastro* inicializaCadastro();