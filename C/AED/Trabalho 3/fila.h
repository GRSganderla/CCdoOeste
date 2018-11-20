#include<stdio.h>
#include<stdlib.h>

typedef struct no
{
	void* info;
	struct no* prox, *ant;
}No;

typedef struct fila
{
	int n;
	struct no* inicio;
	struct no* final;
}Fila;

Fila* start();

int empty(Fila* f);

No* criaNo(void* dados);

Fila* clean(Fila* fileira);

int tamanho(Fila* f);

void enqueue(Fila* f, void* dados);

No* dequeue(Fila* f);