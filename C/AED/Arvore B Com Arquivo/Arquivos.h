#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ArvoreB.h"

typedef struct noBArq
{
	int numChaves;
	int chaves[ORDEM-1];
	int filhos[ORDEM];
}NodeArq;

typedef struct cadastroArq
{
	int codigo;
	int nome;
	int sexo;
	int cpf;
	int crm;
	int especialidade;
	int rg;
	int telefone;
	int celular;
	int email;
	int endereco;
	int nascimento;
}CadastroArq;

Cadastro lerArqEntrada();
