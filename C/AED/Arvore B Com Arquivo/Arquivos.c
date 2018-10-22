#include<stdio.h>
#include "Arquivos.h"

Cadastro* lerArqEntrada()
{
	FILE *texto = fopen("cadastros.txt", "r");

	Cadastro *arquivo = (Cadastro*)malloc(sizeof(Cadastro)*10);

	int i, n, temp;

	for(i = 0; !feof(texto); i++)
	{
		printf("%d\n", i);
		fscanf(texto, "%d[^:]", &arquivo[i].codigo);
		printf("%d\n", arquivo[i].codigo);
		fseek(texto, +1, SEEK_CUR);
		fscanf(texto, "%[^:]", arquivo[i].nome);
		printf("%s\n", arquivo[i].nome);
		fseek(texto, +1, SEEK_CUR);
		fscanf(texto, "%c[^:]", &arquivo[i].sexo);
		printf("%c\n", arquivo[i].sexo);
		fseek(texto, +1, SEEK_CUR);
		fscanf(texto, "%[^:]*c", arquivo[i].cpf);
		printf("%s\n", arquivo[i].cpf);
		fseek(texto, +1, SEEK_CUR);
		fscanf(texto, "%[^:]*c", &arquivo[i].crm);
		printf("%d\n", arquivo[i].crm);
		fseek(texto, +1, SEEK_CUR);
		fscanf(texto, "%[^:]*c", arquivo[i].especialidade);
		printf("%s\n", arquivo[i].especialidade);
		fseek(texto, +1, SEEK_CUR);
		fscanf(texto, "%[^:]*c", arquivo[i].rg);
		printf("%s\n", arquivo[i].rg);
		fseek(texto, +1, SEEK_CUR);
		fscanf(texto, "%[^:]*c", arquivo[i].telefone);
		printf("%s\n", arquivo[i].telefone);
		fseek(texto, +1, SEEK_CUR);
		fscanf(texto, "%[^:]*c", arquivo[i].celular);
		printf("%s\n", arquivo[i].celular);
		fseek(texto, +1, SEEK_CUR);
		fscanf(texto, "%[^:]*c", arquivo[i].email);
		printf("%s\n", arquivo[i].email);
		fseek(texto, +1, SEEK_CUR);
		fscanf(texto, "%[^\n]*c", arquivo[i].endereco);
		printf("%s\n", arquivo[i].endereco);
	}

	return arquivo;
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

	posicao = galho->posicao;

	if(posicao == -1)
	{
		posicao = indice->quantidadeLivre;
		
		if(posicao == -1)
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