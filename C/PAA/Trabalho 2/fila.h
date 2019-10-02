#include<stdio.h>
#include<stdlib.h>

typedef struct no
{
	int info;
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

No* criaNo(int dados);

Fila* clean(Fila* fileira);

int tamanho(Fila* f);

void enqueue(Fila* f, int dados);

int dequeue(Fila* f);

void imprime(Fila* f);