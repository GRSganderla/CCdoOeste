#include<stdio.h>
#include<stdlib.h>
#include "fila.h"

Fila* start()
{
	Fila* aux = (Fila*)malloc(sizeof(Fila));

	aux->final = NULL;
	aux->inicio = NULL;

	return aux;
}

int empty(Fila* f)
{
	return (f->inicio) ? 0: 1;
}

No* criaNo(void* dados)
{
	No* aux = (No*)malloc(sizeof(No));

	aux->info = dados;
	aux->prox = NULL;

	return aux;
}

Fila* clean(Fila* fileira)
{
	if(!empty(fileira))
	{
		No* aux;
		while(fileira->inicio)
		{
			aux = fileira->inicio;
			fileira->inicio = fileira->inicio->prox;
			free(aux);
		}
		free(fileira);
	}
}

int tamanho(Fila* f)
{
	if(empty(f)) return -1;
	No* aux = f->inicio;
	int n = 0;
	while(aux)
	{
		n++;
		aux = aux->prox;
	}
	return n;
}

void enqueue(Fila* f, void* dados)
{
	No* auxf = criaNo(dados);

	if(f->final == NULL)
		f->inicio = auxf;
	else{
		struct no* aux = f->inicio;
		while(aux)
			aux = aux->prox;
		aux = auxf;
	}
	f->n++;
	f->final = auxf;
}

No *dequeue(Fila* f)
{
	if(empty(f)) return NULL;

	No* aux = f->inicio;
	f->inicio = f->inicio->prox;
	
	if(!f->inicio)
	{
		f->final = NULL;
	}

	f->n--;

	return aux;
}

void imprime(Fila* f)
{
	if(empty(f)) return;

	struct no* aux = f->inicio;
	while(aux)
	{
		printf("[%d]->", aux->info);
		aux = aux->prox;
	}
	printf("NULL\n");
}
