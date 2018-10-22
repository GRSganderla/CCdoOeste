#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ArvoreB.h"

int overflow(ArvoreB* r)
{
	return (r->numChaves == ORDEM)? 1:0;
}

int vazia(ArvoreB* r)
{
	return (r == NULL);
}

ArvoreB* split(ArvoreB* x, int *m) 
{
	ArvoreB* nova = inicializaArvore();

	int q = x->numChaves/2;
	nova->numChaves = x->numChaves - q - 1;
	x->numChaves = q;
	
	*m = x->chave[q]; // chave mediana
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
		if(info == r->chave[(*pos)])
			return 1;
		else if(info < r->chave[(*pos)])
			break;
	}

	return 0;
}

int eh_folha(ArvoreB* r) 
{
	return (r->filho[0] == -1);
}

void adicionaDireita(ArvoreB* r, int pos, int k, int p)
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

void insere_aux(FILE* registros, Cabecalho* indice, ArvoreB* r, int info)
{
	int pos = 0;

	if(!buscaPos(r, info, &pos))
	{
		if(eh_folha(r)) 
		{
			adicionaDireita(r, pos, info, -1);
		}
		else 
		{
			int alvo = r->filho[pos];
			
			ArvoreB* aux = leituraDoNoh(registros, alvo); 
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

void insere(FILE* registros, int info)
{
	Cabecalho *indice = leituraDoCabecalho(registros);

	ArvoreB* raiz = leituraDoNoh(registros, indice->cabecalho);
	ArvoreB* novo;

	if(!raiz) 
	{
		raiz = inicializaArvore();

		raiz->chave[0] = info;
		raiz->numChaves = 1;

		indice->cabecalho = escreveArvore(registros, raiz, indice);
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
			novaRaiz->filho[0] = indice->cabecalho;
			novaRaiz->numChaves = 1;
			novaRaiz->filho[1] = escreveArvore(registros, novo, indice);

			indice->cabecalho = escreveArvore(registros, novaRaiz, indice);

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

	ArvoreB* raiz = leituraDoNoh(registros, indice->cabecalho);

	Fila* fileira = start();
	enqueue(fileira, raiz);

	int n = fileira->n;

	while(n)
	{
		for(; n > 0; n--)
		{
			No* noh = dequeue(fileira);

			ArvoreB* nova = (ArvoreB*)noh->info;

			printf("[");
			for(int i = 0; i < ORDEM; i++)
				printf(" %d", nova->chave[i]);
			printf("] ");

			int j;
			printf("%d\n", nova->numChaves);
			for(j = 0; j <= nova->numChaves; j++)
			{
				printf("%d %d\n",j, nova->filho[j]);
				if(nova->filho[j] != -1)
				{
					printf("aaaa\n");
					enqueue(fileira, leituraDoNoh(registros, nova->filho[j]));
				}
			}

			printf("bbbb\n");
			n--;				
			free(noh);
			liberaNoh(nova);
		}
		printf("\n");
		n = fileira->n;
	}
	liberaNoh(raiz);
	clean(fileira);
}