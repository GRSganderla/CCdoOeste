#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ArvoreB.h"

int soNumero(char *s)
{
	int len = strlen(s);

	int i;
	for(i = 0; i < len; i++)
	{
		if((s[i] < '0' || s[i] > '9') && s[i] != '-')
			return 1;
	}

	return 0;
}

void escreveCabecalhoDat(FILE* registros, CabecalhoDados* indice)
{
	if(!indice)
		return;
	
	fseek(registros, 0, SEEK_SET);

	fwrite(indice, sizeof(CabecalhoDados), 1, registros);
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

	if((posicao = galho->posicao) == -1)
	{
		if(posicao = indice->nohsLivre == -1)
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

int overflow(ArvoreB* r)
{
	return (r->numChaves == ORDEM);
}

int vazia(ArvoreB* r)
{
	return (r == NULL);
}

ArvoreB* split(ArvoreB* x, RegistrosDat *m) 
{
	ArvoreB* nova = inicializaArvore();

	int q = (ORDEM-1)/2;
	nova->numChaves =  q;
	x->numChaves = q;
	
	*m = x->chave[q];
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

void adicionaDireita(ArvoreB* r, int pos, RegistrosDat info, int p)
{
	int i;

	for(i=r->numChaves; i>pos; i--)
	{
		r->chave[i] = r->chave[i-1];
		r->filho[i+1] = r->filho[i];
	}
	
	r->chave[pos] = info;
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
				RegistrosDat m;
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
	RegistrosDat info;
	info.codigo = dado;
	info.registroPos = pos;

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
			RegistrosDat m;
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


int escreverRegistro(FILE* dados, CabecalhoDados* indice, Cadastro medico)
{
	int pos = 0;

	if(!indice)
		return -1;

	pos = indice->nohsLivre;

	if(pos == -1)
	{
		pos = indice->topo;
	}
	else
	{
		Livres *novo = leLivres(dados, pos);
		indice->nohsLivre = novo->prox;
		free(novo);
	}

	fseek(dados, sizeof(CabecalhoDados) + sizeof(Cadastro)*pos, SEEK_SET);

	fwrite(&medico.codigo, sizeof(int), 1, dados);
	fwrite(medico.nome, sizeof(char)* 100, 1, dados);
	fwrite(&medico.sexo, sizeof(char), 1, dados);
	fwrite(medico.cpf, sizeof(char)* 12, 1, dados);
	fwrite(medico.crm, sizeof(char)* 20, 1, dados);
	fwrite(medico.especialidade, sizeof(char)* 100, 1, dados);
	fwrite(medico.rg, sizeof(char)* 12, 1, dados);
	fwrite(medico.telefone, sizeof(char)* 13, 1, dados);
	fwrite(medico.celular, sizeof(char)* 14, 1, dados);
	fwrite(medico.email, sizeof(char)* 100, 1, dados);
	fwrite(medico.endereco, sizeof(char)* 100, 1, dados);
	fwrite(medico.nascimento, sizeof(char)* 11, 1, dados);

	return pos;
}

void criaIndicesArqDat(FILE *binario)
{
	CabecalhoDados indice;

	indice.topo = -1;
	indice.nohsLivre = -1;

	escreveCabecalhoDat(binario, &indice);
}

CabecalhoDados* leCabecalhoDat(FILE* dados)
{
	CabecalhoDados* indice = (CabecalhoDados*)malloc(sizeof(CabecalhoDados));

	fseek(dados, 0, SEEK_SET);

	fread(indice, sizeof(CabecalhoDados), 1, dados);

	return indice;
}

void lerArquivo(FILE* dados, FILE* arvore, char* nome)
{
	int n = 0, temp = 0;
	FILE* texto = fopen(nome, "r+");
	if(texto == NULL)
	{
		printf("Arquivo Vazio!\n");
		return;
	}

	CabecalhoDados* indice = leCabecalhoDat(dados);

	while(!feof(texto))
	{
		Cadastro medicos = inicializaCadastro();
		fscanf(texto, "%d :", &medicos.codigo);
		fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.nome);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%c", &medicos.sexo);
	    fseek(texto, +1, SEEK_CUR);
	   
	    fscanf(texto, "%[^:]", medicos.cpf);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.crm);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.especialidade);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.rg);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.telefone);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.celular);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.email);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos.endereco);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^\n]", medicos.nascimento);

	    if(!medicos.rg[0] || medicos.codigo == -1 || !medicos.nome[0] || medicos.sexo == '\0' || !medicos.cpf[0] || soNumero(medicos.cpf) || !medicos.crm[0] || soNumero(medicos.telefone) || soNumero(medicos.celular) || !medicos.nascimento[0])
	    {
	    	printf("Cadastro Invalido!\n");
	    }
	    printf("psos\n");
    	int pos = escreverRegistro(dados, indice, medicos);
    	insere(arvore, medicos.codigo, pos);
    	printf("dasdasdsada\n");
	}
}