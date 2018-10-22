#include<stdio.h>
#include "Arquivos.h"
#define MAX 100

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
	Cadastro *medicos = inicializaCadastro();

	for(int i = 0; !feof(texto); i++)
	{
		fscanf(texto, "%d[^:]", &medicos[i].codigo);
		if(medicos[i].codigo == -1)
		{
			printf("Codigo Vazio\n");
			return NULL;
		}

		fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos[i].nome);
	    if(!medicos[i].nome)
	    {
	    	printf("Nome Vazio!\n");
	    	return NULL;
	    }
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos[i].sexo);
	    if(!medicos[i].sexo)
	    {
	    	printf("Sexo Vazio!\n");
	    	return NULL;
	    }
	    fseek(texto, +1, SEEK_CUR);
	   
	    fscanf(texto, "%[^:]", medicos[i].cpf);
	    if(!medicos[i].cpf || soNumero(medicos[i].cpf))
	    {
	    	printf("CPF Nao cumpre requisitos\n");
	    	return NULL;
	    }
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos[i].crm);
	    if(!medicos[i].crm)
	    {
	    	printf("CRM Vazio!\n");
	    	return NULL;
	    }
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos[i].especialidade);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos[i].rg);
	    if(!medicos[i].rg)
	    {
	    	printf("RG Vazio!\n");
	    	return NULL;
	    }
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos[i].telefone);
	    if(soNumero(medicos[i].telefone))
	    {
	    	printf("Telefone nao cumpre requisitos!\n");
	    	return NULL;
	    }
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos[i].celular);
	    if(soNumero(medicos[i].celular))
	    {
	    	printf("Celular nao cumpre requisitos\n");
	    	return NULL;
	    }
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos[i].email);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos[i].endereco);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^\n]", medicos[i].nascimento);
	    if(!medicos[i].nascimento)
	    {
	    	printf("Data de Nascimento Vazia!\n");
	    	return NULL;
	    }
	}
    
   return medicos;
}

void printaCadastro(Cadastro* medicos)
{
	int i;
	system("CLS");
	for(i = 0; i < MAX; i++)
	{
		//if(medicos[i].codigo == -1)
		//break;

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

Cadastro* inicializaCadastro()
{
	Cadastro* novo = (Cadastro*)malloc(sizeof(Cadastro)*MAX);

	for(int i = 0; i < MAX; i++)
	{
		novo[i].codigo = -1;
	    novo[i].nome = (char*)malloc(sizeof(char)*256);
	    novo[i].sexo = (char*)malloc(sizeof(char)*256);
	    novo[i].cpf = (char*)malloc(sizeof(char)*256);
	    novo[i].crm = (char*)malloc(sizeof(char)*256);
	    novo[i].especialidade = (char*)malloc(sizeof(char)*256);
	    novo[i].rg = (char*)malloc(sizeof(char)*256);
	    novo[i].telefone = (char*)malloc(sizeof(char)*256);
	    novo[i].celular = (char*)malloc(sizeof(char)*256);
	    novo[i].email = (char*)malloc(sizeof(char)*256);
	    novo[i].endereco = (char*)malloc(sizeof(char)*256);
	    novo[i].nascimento = (char*)malloc(sizeof(char)*256);
	}

	return novo;
}

void criaIndicesArq(FILE *binario)
{
	Cabecalho indice;

	indice.cabecalho = -1;
	indice.quantidade = 0;
	indice.nohsLivre = -1;
	indice.quantidadeLivre = 0;

	escreveCabecalho(binario, &indice);
}

void liberaNoh(ArvoreB* alvo)
{
	if(alvo)
		free(alvo);
}

ArvoreB* inicializaArvore()
{
	ArvoreB* new = (ArvoreB*)malloc(sizeof(ArvoreB));

	new->numChaves = 0;
	new->posicao = -1;
	
	int i;

	for(i = 0; i < ORDEM; i++)
	{
		new->chave[i] = 0;
		new->filho[i] = -1;
		new->dados[i] = -1;
	}
	
	return new;
}

ArvoreB* leituraDoNoh(FILE* binario, int posicao)
{
    ArvoreB* nois;

	if(posicao == -1)
		return NULL;

    nois = (ArvoreB*)malloc(sizeof(ArvoreB));

    fseek(binario, sizeof(Cabecalho) + sizeof(ArvoreB)*posicao , SEEK_SET);

    fread(nois, sizeof(ArvoreB), 1, binario);

    return nois;
}

void escreveCabecalho(FILE* registros, Cabecalho* indice)
{
	if(!indice)
		return;
	
	fseek(registros, 0, SEEK_SET);

	fwrite(indice, sizeof(Cabecalho), 1, registros);
}

Livres* leLivres(FILE* registros, int posicao)
{
	Livres* novo;

	if(posicao == -1)
		return NULL;

	novo = (Livres*)malloc(sizeof(Livres));

	fseek(registros, sizeof(Cabecalho) + sizeof(ArvoreB) * posicao, SEEK_SET);

	fread(novo, sizeof(Livres), 1, registros);

	return novo;
}

int escreveArvore(FILE* registros, ArvoreB* galho, Cabecalho* indice)
{
	int posicao;

	if(!indice || !galho) return -1;

	if((posicao = galho->posicao) == -1)
	{
		if(posicao = indice->nohsLivre == -1)
			posicao = indice->quantidade++;
		else
		{
			Livres *novo = leLivres(registros, posicao);
			indice->nohsLivre = novo->prox;
			free(novo);
		}
	}
	
	galho->posicao = posicao;

	fseek(registros, sizeof(Cabecalho) + sizeof(ArvoreB) * posicao, SEEK_SET);
	fwrite(galho, sizeof(ArvoreB), 1, registros);

	return posicao;
}

Cabecalho* leituraDoCabecalho(FILE* binario)
{
    Cabecalho* cabeca = (Cabecalho*)malloc(sizeof(Cabecalho));

    fseek(binario, 0, SEEK_SET);

    fread(cabeca, sizeof(Cabecalho), 1, binario);

    return cabeca;
}