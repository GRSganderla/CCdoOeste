#include<stdio.h>
#include<stdlib.h>
#define MAX(X, Y) (((X) > (Y)) ? (1) : (0))

int **s, **aux_x, *x;

typedef struct objeto
{
	int w, c;
}Objeto;

int K(Objeto *ob, int W, int n);

void aloca(int n, int W);

void mochila();