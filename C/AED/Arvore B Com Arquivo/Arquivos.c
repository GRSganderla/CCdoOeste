#include<stdio.h>
#include "Arquivos.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

void escreveCabecalho(FILE* registros, Cabecalho* indice)
{
	if(!indice)
		return;
	
	fseek(registros, 0, SEEK_SET);

	fwrite(indice, sizeof(Cabecalho), 1, registros);
}

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
