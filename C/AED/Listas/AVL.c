#include<stdio.h>
#include<stdlib.h>

struct no
{
	int info;
	struct no* esq;
	struct no* dir;
	int fb;
};

typedef struct no* AVL;

AVL rotacaoSimplesEsq(AVL raiz)
{
	AVL u = raiz->esq;
	AVL t2 = u->dir;
	
	u->esq = raiz;
	raiz->dir = t2;
	
	return u; 
}

AVL rotacaoDuplaEsq(AVL raiz)
{
	AVL u = raiz->dir;
	AVL v = u->esq;
	AVL t2 = v->esq;
	AVL t3 = v->dir;
	
	raiz->dir = t2;
	u->esq = t3;
	v->esq = p;
	v->dir = u;
	
	return v;
}

AVL rotacaoSimplesDir(AVL raiz)
{
	AVL u = raiz->esq;
	AVL t2 = u->esq;
	
	u->dir = raiz;
	raiz->esq = t2;

	return u;
}

int main()
{
	AVL balanceado;	
}