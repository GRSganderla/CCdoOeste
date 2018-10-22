#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ArvoreB.h"

int overflow(ArvoreB* r)
{
	return (r->numChaves == ORDEM);
}

int vazia(ArvoreB* r)
{
	return (r == NULL);
}

ArvoreB* split(ArvoreB* x, int *m) 
{
	ArvoreB* nova = inicializaArvore();

	int q = ORDEM/2;
	nova->numChaves =  q;
	x->numChaves = q;
	
	*m = x->chave[q].codigo;
	int i = 0;
	
	nova->filho[0] = x->filho[q+1];
	
	for(i = 0; i < nova->numChaves; i++)
	{
		nova->chave[i] = x->chave[q+i+1];
		nova->filho[i+1] = x->filho[q+i+2];
	}

	return nova;
}

int buscaPos(ArvoreB* r, int info, int * pos) 
{
	for((*pos)=0; (*pos) < r->numChaves; (*pos)++)
	{
		if(info == r->chave[(*pos)].codigo)
			return 1;
		else if(info < r->chave[(*pos)].codigo)
			break;
	}

	return 0;
}

int eh_folha(ArvoreB* r) 
{
	return (r->filho[0] == -1);
}

void adicionaDireita(ArvoreB* r, int pos, RegistrosDat* k, int p)
{
	int i;

	for(i=r->numChaves; i>pos; i--)
	{
		r->chave[i] = r->chave[i-1];
		r->filho[i+1] = r->filho[i];
	}
	
	r->chave[pos] = k;
	r->filho[pos+1] = p;
	r->numChaves++;
}

void insere_aux(FILE* registros, Cabecalho* indice, ArvoreB* r, RegistrosDat info)
{
	int pos = 0;

	if(!buscaPos(r, info.codigo, &pos))
	{
		if(eh_folha(r)) 
		{
			adicionaDireita(r, pos, info, -1);
		}
		else 
		{
			ArvoreB* aux = leituraDoNoh(registros, r->filho[pos]); 
			insere_aux(registros, indice, aux, info);
			
			if(overflow(aux))
			{
				int m;
				ArvoreB* pai = split(aux, &m);
				adicionaDireita(r, pos, m, escreveArvore(registros, pai, indice));
				escreveArvore(registros, aux, indice);

				liberaNoh(pai);
			}
		}
	}

	escreveArvore(registros, r, indice);
}

void insere(FILE* registros, int dado, int pos)
{
	RegistrosDat *info = (RegistrosDat*)malloc(sizeof(RegistrosDat));
	info->codigo = dado;
	info->registroPos = pos;

	Cabecalho *indice = leituraDoCabecalho(registros);

	ArvoreB* raiz = leituraDoNoh(registros, indice->topo);
	ArvoreB* novo;

	if(!raiz) 
	{
		raiz = inicializaArvore();

		raiz->chave[0] = info;
		raiz->numChaves = 1;

		indice->topo = escreveArvore(registros, raiz, indice);
	}
	else 
	{
		insere_aux(registros, indice, raiz,info);

		if(overflow(raiz))
		{
			int m;
			novo = split(raiz, &m);

			ArvoreB* novaRaiz = inicializaArvore();

			novaRaiz->chave[0] = m;
			novaRaiz->filho[0] = indice->topo;
			novaRaiz->numChaves = 1;
			novaRaiz->filho[1] = escreveArvore(registros, novo, indice);

			indice->topo = escreveArvore(registros, novaRaiz, indice);

			liberaNoh(novo);	
			liberaNoh(novaRaiz);
		}
		
		escreveArvore(registros, raiz, indice);
	}

	escreveCabecalho(registros, indice);

	liberaNoh(raiz);
	free(indice);
}

void printaArvore(FILE* registros)
{
	Cabecalho* indice = leituraDoCabecalho(registros);

	ArvoreB* raiz = leituraDoNoh(registros, indice->topo);

	Fila* fileira = start();
	enqueue(fileira, raiz);

	int n;
	n = fileira->n;
	while(n)
	{
		while( n)
		{
			No* noh = dequeue(fileira);

			ArvoreB* nova = (ArvoreB*)noh->info;

			printf("[");
			for(int i = 0; i < nova->numChaves - 1; i++)
				printf(" %d", nova->chave[i]);
			printf(" %d", nova->chave[nova->numChaves-1]);
			printf("] ");

			int j;
			for(j = 0; j <= nova->numChaves; j++)
			{
				if(nova->filho[j] != -1)
				{
					enqueue(fileira, leituraDoNoh(registros, nova->filho[j]));
				}
			}
			n--;
			free(noh);
			liberaNoh(nova);
		}
		n = fileira->n;
		printf("\n");
	}

	liberaNoh(raiz);
	clean(fileira);
}