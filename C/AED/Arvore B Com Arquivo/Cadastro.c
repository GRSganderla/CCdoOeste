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

Cadastro* lerArquivo(char* nome)
{
	int n = 0, temp = 0;
	FILE* texto = fopen(nome, "r+");
	if(texto == NULL)
	{
		printf("Arquivo Vazio!\n");
		return NULL;
	}
	Cadastro *medicos = (Cadastro*)malloc(sizeof(Cadastro));

	while(!feof(texto))
	{
		fscanf(texto, "%d :", &medicos->codigo);
		fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->nome);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->sexo);
	    fseek(texto, +1, SEEK_CUR);
	   
	    fscanf(texto, "%[^:]", medicos->cpf);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->crm);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->especialidade);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->rg);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->telefone);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->celular);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->email);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->endereco);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^\n]", medicos->nascimento);

	    if(!medicos->rg || medicos->codigo == -1 || !medicos->nome || !medicos->sexo || !medicos->cpf || soNumero(medicos->cpf) || !medicos->crm || soNumero(medicos->telefone) || soNumero(medicos->celular) || !medicos->nascimento)
	    {
	    	printf("Cadastro Invalido!\n");
	    }
    	//printaArqCadastro(Cadastro);
	}
    
   return medicos;
}

void printaCadastro(Cadastro* medicos)
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