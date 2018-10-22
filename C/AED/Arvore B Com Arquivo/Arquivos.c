#include<stdio.h>
#include "Arquivos.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

void criaIndicesArq(FILE *binario)
{
	Cabecalho indice;

	indice.topo = -1;
	indice.quantidade = 0;
	indice.nohsLivre = -1;
	indice.quantidadeLivre = 0;

	escreveCabecalho(binario, &indice);
}

Livres* criaNohLivre()
{
	Livres* novo = (Livres*)malloc(sizeof(Livres));

	novo->prox = -1;

	return novo;
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
		new->chave[i].codigo = 0;
		new->chave[i].registroPos = -1;
		new->filho[i] = -1;
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

void escreveNosLivres(FILE* registros, Cabecalho* indice, ArvoreB* raiz)
{
	if(!indice)
		return;

	int pos;

	pos = raiz->posicao;
	Livres* nos = criaNohLivre();

	nos->prox = indice->nohsLivre;
	indice->nohsLivre = pos;

	indice->quantidadeLivre++;

	fseek(registros, sizeof(Cabecalho)+sizeof(ArvoreB)*pos, SEEK_SET);

	fwrite(nos, sizeof(Livres), 1, registros);

	free(nos);
}

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

Cadastro inicializaCadastro()
{
	Cadastro novo;

	novo.codigo = 0;
	novo.nome[0] = '\0';
	novo.sexo = '\0';
	novo.cpf[0] = '\0';
	novo.crm[0] = '\0';
	novo.especialidade[0] = '\0';
	novo.rg[0] = '\0';
	novo.telefone[0] = '\0';
	novo.celular[0] = '\0';
	novo.email[0] = '\0';
	novo.endereco[0] = '\0';
	novo.nascimento[0] = '\0';

	return novo;
}

int escreverRegistro(FILE* dados, CabecalhoDados* indice, Cadastro medico)
{
	int pos = 0;

	if(!indice)
		return -1;

	pos = indice->nohsLivre;

	if(pos == -1)
	{
		pos = indice->topo;
	}
	else
	{
		Livres *novo = leLivres(dados, pos);
		indice->nohsLivre = novo->prox;
		free(novo);
	}

	fseek(dados, sizeof(CabecalhoDados) + sizeof(Cadastro)*pos, SEEK_SET);

	fwrite(&medico.codigo, sizeof(int), 1, dados);
	fwrite(medico.nome, sizeof(char)* 100, 1, dados);
	fwrite(&medico.sexo, sizeof(char), 1, dados);
	fwrite(medico.cpf, sizeof(char)* 12, 1, dados);
	fwrite(medico.crm, sizeof(char)* 20, 1, dados);
	fwrite(medico.especialidade, sizeof(char)* 100, 1, dados);
	fwrite(medico.rg, sizeof(char)* 12, 1, dados);
	fwrite(medico.telefone, sizeof(char)* 13, 1, dados);
	fwrite(medico.celular, sizeof(char)* 14, 1, dados);
	fwrite(medico.email, sizeof(char)* 100, 1, dados);
	fwrite(medico.endereco, sizeof(char)* 100, 1, dados);
	fwrite(medico.nascimento, sizeof(char)* 11, 1, dados);

	return pos;
}

void lerArquivo(FILE* dados, FILE* arvore, char* nome)
{
	int n = 0, temp = 0;
	FILE* texto = fopen(nome, "r+");
	if(texto == NULL)
	{
		printf("Arquivo Vazio!\n");
		return;
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
}

/*void printaCadastro(FILE* dados)
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
}*/
