#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ORDEM 5

int overflow(ArvoreB* r)
{
	return (r->numChaves == ORDEM) ? 1: 0;
}

int vazia(ArvoreB* r)
{
	return (r == NULL);
}

ArvoreB* split(ArvoreB* x, int *m) 
{
	ArvoreB* y = (ArvoreB*) malloc(sizeof(ArvoreB));

	int q = x->numChaves/2;
	y->numChaves = x->numChaves - q - 1;
	x->numChaves = q;
	
	*m = x->chave[q]; // chave mediana
	int i = 0;
	
	y->filho[0] = x->filho[q+1];
	
	for(i = 0; i < y->numChaves; i++)
	{
		y->chave[i] = x->chave[q+i+1];
		y->filho[i+1] = x->filho[q+i+2];
	}

	return y;
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
	return (r->filho[0] == NULL);
}

void adicionaDireita(ArvoreB* r, int pos, int k, ArvoreB* p)
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

void insere_aux(ArvoreB* r, int info)
{
	int pos;
	if(!buscaPos(r,info, &pos)){
		if(eh_folha(r)) {
			adicionaDireita(r,pos,info,NULL);
		}
		else {
			insere_aux(r->filho[pos],info);
			if(overflow(r->filho[pos]))
			{
			int m;
			ArvoreB* aux = split(r->filho[pos],&m);
			adicionaDireita(r,pos,m,aux);
			}
		}
	}
}

ArvoreB* insere(ArvoreB* r, int info)
{
	if(vazia(r)) 
	{
		r = malloc(sizeof(ArvoreB));
		r->chave[0] = info;
		r->filho[0] = NULL;
		r->numChaves = 1;
	}
	else 
	{
		insere_aux(r,info);
		if(overflow(r))
		{
			int m;
			ArvoreB* x = split(r,&m);
			ArvoreB* novaRaiz = malloc(sizeof(ArvoreB));
			novaRaiz->chave[0] = m;
			novaRaiz->filho[0] = r;
			novaRaiz->filho[1] = x;
			novaRaiz->numChaves = 1;
			return novaRaiz;
		}
	}

	return r;
}

ArvoreB* busca(ArvoreB* r, int info, int * pos)
{
	if(vazia(r))
		return NULL;
	
	int i = 0;
	
	while(i < r->numChaves && r->chave[i] < info) i++;
		if((i+1) > r->numChaves || r->chave[i] > info)
			return busca(r->filho[i], info, pos);
	
	*pos = i;
	return r;
}

int altura(ArvoreB* r)
{
	if(r == NULL)
		return 0;
	if(r->filho[0] == NULL)
		return 1;
	else
		return altura(r->filho[0]) + 1;
}

void printaNivelB(ArvoreB* r, int i)
{
	if(i == 0)
	{
		int j;
		printf("[ ");
		for(j = 0; j < r->numChaves; j++)
			printf("%d ", r->chave[j]);
		printf("]");	
	}
	else
	{
		if(r->filho[0] != NULL)
		{
			int j;
			for(j = 0; j <= r->numChaves; j++)
				printaNivelB(r->filho[j], i-1);
		}
	}
}

void printaPorNivelB(ArvoreB* r)
{
	int i;
	for(i = 0; i < altura(r); i++)
	{
		printaNivelB(r, i);
		printf("\n");
	}
}

ArvoreB* inicializaArvore()
{
	ArvoreB* new = (ArvoreB*)malloc(sizeof(ArvoreB));

	new->numChaves = 0;


	for(int i = 0; i < ORDEM; i++)
	{
		new->chave[i] = 0;
		new->filho[i] = NULL;
	}

	return new;
}

void lerCadastro(Cadastro hospital[])
{
	int i;
	for(i = 0; i < 1; i++)
	{
		scanf("%d%*c", &hospital[i].codigo);
		scanf("%[^:]%*c", hospital[i].nome);
		scanf("%c%*c", hospital[i].sexo);
		scanf("%[^:]%*c", hospital[i].cpf);
		scanf("%d%*c", &hospital[i].crm);
		scanf("%[^:]%*c", hospital[i].especialidade);
		scanf("%[^:]%*c", hospital[i].rg);
		scanf("%[^:]%*c", hospital[i].telefone);
		scanf("%[^:]%*c", hospital[i].celular);
		scanf("%[^:]%*c", hospital[i].email);
		scanf("%[^:]%*c", hospital[i].endereco);
		scanf("%[^:]%*c", shospital[i].nascimento);
	}
}

Cadastro* inicializaCadastro()
{
	Cadastro *novo = (Cadastro*)malloc(sizeof(Cadastro));

	novo->codigo = 0;
	novo->nome = malloc(sizeof(char)*100);
	novo->sexo = '\0';
	novo->cpf = malloc(sizeof(char)*100);
	novo->crm = 0;
	novo->especialidade = malloc(sizeof(char)*100);
	novo->rg = malloc(sizeof(char)*100);
	novo->telefone = malloc(sizeof(char)*100);
	novo->celular = malloc(sizeof(char)*100);
	novo->email = malloc(sizeof(char)*100);
	novo->endereco = malloc(sizeof(char)*100);
	novo->nascimento = malloc(sizeof(char)*10);

	return novo;
}