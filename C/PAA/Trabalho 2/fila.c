#include<stdio.h>
#include<stdlib.h>
#include "fila.h"

Fila* start()
{
	Fila* aux = (Fila*)malloc(sizeof(Fila));

	aux->final = NULL;
	aux->inicio = NULL;
	aux->n = 0;

	return aux;
}

int empty(Fila* f)
{
	return (f->inicio) ? 0: 1;
}

No* criaNo(int dados)
{
	No* aux = (No*)malloc(sizeof(No));

	aux->info = dados;
	aux->prox = NULL;
	aux->ant = NULL;

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

void enqueue(Fila* f, int dados)
{
	if(!f)return;

	No* auxf = criaNo(dados);

	if(!f->inicio)
		f->inicio = f->final = auxf;
	else{
		auxf->ant = f->final;
		f->final->prox = auxf;
		f->final = auxf;
	}
	f->n++;
}

int dequeue(Fila* f)
{
	if(empty(f)) return -1;
	if(f->inicio == NULL) return -1;

	No* aux = f->inicio;
	f->inicio = aux->prox;
	
	if(f->inicio)
	{
		f->inicio->ant = NULL;
	}
	else{
		f->final = NULL;
	}

	f->n--;

	return aux->info;
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
