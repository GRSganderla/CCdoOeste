#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Cadastro.h"
#define MAX 100

void escreveCabecalhoDat(FILE* registros, CabecalhoDados* indice)
{
	if(!indice)
		return;
	
	fseek(registros, 0, SEEK_SET);

	fwrite(indice, sizeof(CabecalhoDados), 1, registros);
}

CabecalhoDados* leCabecalhoDat(FILE* dados)
{
	CabecalhoDados* indice;

	fseek(dados, 0, SEEK_SET);

	fread(indice, sizeof(CabecalhoDados), 1, dados);

	return indice;
}

void criaIndicesArqDat(FILE *binario)
{
	CabecalhoDados indice;

	indice.topo = -1;
	indice.nohsLivre = -1;

	escreveCabecalhoDat(binario, &indice);
}

int soNumero(char *s)
{
	int len = strlen(s);

	int i;
	for(i = 0; i < len; i++)
	{
		if((s[i] < '0' || s[i] > '9') && s[i] != '-')
			return 1;
	}

	return 0;
}

void lerArquivo(FILE* dados, FILE* arvore, char* nome)
{
	int n = 0, temp = 0;
	FILE* texto = fopen(nome, "r+");
	if(texto == NULL)
	{
		printf("Arquivo Vazio!\n");
		return NULL;
	}

	Cadastro medicos = inicializaCadastro();

	while(!feof(texto))
	{
		fscanf(texto, "%d :", &medicos.codigo);
		fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.nome);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.sexo);
	    fseek(texto, +1, SEEK_CUR);
	   
	    fscanf(texto, "%[^:]", medicos.cpf);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.crm);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.especialidade);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.rg);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.telefone);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.celular);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.email);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.endereco);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^\n]", medicos.nascimento);

	    if(!medicos.rg || medicos.codigo == -1 || !medicos.nome || !medicos.sexo || !medicos.cpf || soNumero(medicos.cpf) || !medicos.crm || soNumero(medicos.telefone) || soNumero(medicos.celular) || !medicos.nascimento)
	    {
	    	printf("Cadastro Invalido!\n");
	    }
    	int pos = escreverRegistro(dados, medicos);
    	insere(arvore, medicos.codigo, pos);
	}
    
   return medicos;
}

void escreverRegistro(FILE* dados, CabecalhoDados* indice, Cadastro medico)
{
	int pos = 0;

	if(!indice || !medico)
		return;

	pos = indice->nohsLivre;

	if(pos == -1)
	{
		pos = indice->topo;
	}
	else
	{
		Livres *novo = leLivres(registros, posicao);
		indice->nohsLivre = novo->prox;
		free(novo);
	}

	fseek(dados, sizeof(CabecalhoDados) + sizeof(Cadastro)*pos, SEEK_SET);

	fwrite(medico->codigo, sizeof(int), 1, dados);
	fwrite(medico->nome, sizeof(char)* 100, 1, dados);
	fwrite(medico->sexo, sizeof(char), 1, dados);
	fwrite(medico->cpf, sizeof(char)* 12, 1, dados);
	fwrite(medico->crm, sizeof(char)* 20, 1, dados);
	fwrite(medico->especialidade, sizeof(char)* 100, 1, dados);
	fwrite(medico->rg, sizeof(char)* 12, 1, dados);
	fwrite(medico->telefone, sizeof(char)* 13, 1, dados);
	fwrite(medico->celular, sizeof(char)* 14, 1, dados);
	fwrite(medico->email, sizeof(char)* 100, 1, dados);
	fwrite(medico->endereco, sizeof(char)* 100, 1, dados);
	fwrite(medico->nascimento, sizeof(char)* 11, 1, dados);
}

void printaCadastro(FILE* dados)
{
	int i;
	system("CLS");
	for(i = 0; i < MAX; i++)
	{
	    printf("//----------------------------------------//\n");
		printf("Medico[%d]\n", i);
		printf("Codigo: %d\n", medicos[i].codigo);
		
	    printf("Nome: %s\n", medicos[i].nome);
	    
	    printf("Sexo: %s\n", medicos[i].sexo);
	   
	    printf("CPF: %s\n", medicos[i].cpf);
	    
	    printf("CRM: %s\n", medicos[i].crm);
	    
	    printf("Especialidade: %s\n", medicos[i].especialidade);
	    
	    printf("RG: %s\n", medicos[i].rg);
	    
	    printf("Telefone: %s\n", medicos[i].telefone);
	    
	    printf("Celular: %s\n", medicos[i].celular);
	    
	    printf("Email: %s\n", medicos[i].email);
	    
	    printf("Endereco: %s\n", medicos[i].endereco);
	    
	    printf("Data de Nascimento: %s\n", medicos[i].nascimento);
	}
}