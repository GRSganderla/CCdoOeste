#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<ctype.h>
#include "ArvoreB.h"

int validaDado(char *s)
{	
	int i;
	for(i = 0; i < strlen(s); i++)
		if(!isdigit(s[i]))
			if(s[i] != '-')
				return 0;

	return 1;
}

int validaData(char *s)
{
	if(s[0] == '\0')
		return 0;

	int i;
	if(s[2] == '/' && s[5] == '/')
		return 1;

	else
		return 0;
}

Cadastro* leDados(FILE* dados, CabecalhoDados* raiz, int indice)
{
	Cadastro* novo;

	if(indice == -1)
		return NULL;

	novo = (Cadastro*)malloc(sizeof(Cadastro));

	fseek(dados, sizeof(CabecalhoDados) + sizeof(Cadastro)*indice, SEEK_SET);

	fread(&novo->codigo, sizeof(int), 1, dados);
	fread(&novo->nome, sizeof(char)* 100, 1, dados);
	fread(&novo->sexo, sizeof(char), 1, dados);
	fread(&novo->cpf, sizeof(char)* 22, 1, dados);
	fread(&novo->crm, sizeof(char)* 30, 1, dados);
	fread(&novo->especialidade, sizeof(char)* 100, 1, dados);
	fread(&novo->rg, sizeof(char)* 22, 1, dados);
	fread(&novo->telefone, sizeof(char)* 23, 1, dados);
	fread(&novo->celular, sizeof(char)* 24, 1, dados);
	fread(&novo->email, sizeof(char)* 100, 1, dados);
	fread(&novo->endereco, sizeof(char)* 100, 1, dados);
	fread(&novo->nascimento, sizeof(char)* 21, 1, dados);

	return novo;
}

ArvoreB* leituraDoNoh(FILE* binario, int posicao)
{
    ArvoreB* nois;

	if(posicao == -1)
		return NULL;

    nois = (ArvoreB*)malloc(sizeof(ArvoreB));

    fseek(binario, sizeof(Cabecalho) + sizeof(ArvoreB)*posicao , SEEK_SET);

    fread(nois, sizeof(ArvoreB), 1, binario);

    return nois;
}

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
		if((posicao = indice->nohsLivre) == -1)
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
			for(int i = 0; i < nova->numChaves-1; i++)
				printf(" %d", nova->chave[i].codigo);
			printf(" %d", nova->chave[nova->numChaves-1].codigo);
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


int escreverRegistro(FILE* dados, CabecalhoDados* indice, Cadastro* medico)
{
	int pos = 0;

	if(!indice)
		return -1;

	pos = indice->nohsLivre;

	if(pos == -1)
	{
		pos = indice->topo++;
	}
	else
	{
		Livres *novo = leLivres(dados, pos);
		indice->nohsLivre = novo->prox;
		free(novo);
	}

	fseek(dados, sizeof(CabecalhoDados) + sizeof(Cadastro)*pos, SEEK_SET);

	fwrite(&medico->codigo, sizeof(int), 1, dados);
	fwrite(medico->nome, sizeof(char)* 100, 1, dados);
	fwrite(&medico->sexo, sizeof(char), 1, dados);
	fwrite(medico->cpf, sizeof(char)* 22, 1, dados);
	fwrite(medico->crm, sizeof(char)* 30, 1, dados);
	fwrite(medico->especialidade, sizeof(char)* 100, 1, dados);
	fwrite(medico->rg, sizeof(char)* 22, 1, dados);
	fwrite(medico->telefone, sizeof(char)* 23, 1, dados);
	fwrite(medico->celular, sizeof(char)* 24, 1, dados);
	fwrite(medico->email, sizeof(char)* 100, 1, dados);
	fwrite(medico->endereco, sizeof(char)* 100, 1, dados);
	fwrite(medico->nascimento, sizeof(char)* 21, 1, dados);

	return pos;
}

void criaIndicesArqDat(FILE *binario)
{
	CabecalhoDados indice;

	indice.topo = 0;
	indice.nohsLivre = -1;

	escreveCabecalhoDat(binario, &indice);
}

Cadastro limpaMed()
{
	Cadastro novo;

	novo.codigo = 0;
	novo.nome[0] = '\0';
	novo.sexo = '\0';
	novo.cpf[0] = '\0';
	novo.crm[0] = '\0';
	novo.especialidade[0] = '\0';
	novo.rg[0] = '\0';
	novo.telefone[0] = '\0';
	novo.celular[0] = '\0';
	novo.email[0] = '\0';
	novo.endereco[0] = '\0';
	novo.nascimento[0] = '\0';

	return novo;
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
	Cadastro *medicos = inicializaCadastro();

	while(!feof(texto))
	{
		*medicos = limpaMed();
		fscanf(texto, "%d", &medicos->codigo);
		fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->nome);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%c", &medicos->sexo);
	    fseek(texto, +1, SEEK_CUR);
	   
	    fscanf(texto, "%[^:]", medicos->cpf);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->crm);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->especialidade);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->rg);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->telefone);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->celular);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->email);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^:]", medicos->endereco);
	    fseek(texto, +1, SEEK_CUR);
	    
	    fscanf(texto, "%[^\n]%*c", medicos->nascimento);

	    if(!medicos->rg[0] || medicos->codigo == -1 || !medicos->nome[0] || medicos->sexo == '\0' || !medicos->cpf[0] || !validaDado(medicos->cpf) || !medicos->crm[0] || !validaDado(medicos->telefone) || !validaDado(medicos->celular) || !medicos->nascimento[0] || !validaData(medicos->nascimento))
	    {
	    	printf("Cadastro Invalido!\n");
	    }
	    else
	    {
    		int pos = escreverRegistro(dados, indice, medicos);
    		insere(arvore, medicos->codigo, pos);
    		escreveCabecalhoDat(dados, indice);
    	}
	}


	free(medicos);
}

int eh_folha(ArvoreB* r) 
{
	return (r->filho[0] == -1);
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

CabecalhoDados* leCabecalhoDat(FILE* dados)
{
	CabecalhoDados* indice = (CabecalhoDados*)malloc(sizeof(CabecalhoDados));

	fseek(dados, 0, SEEK_SET);

	fread(indice, sizeof(CabecalhoDados), 1, dados);

	return indice;
}

void escreveCabecalho(FILE* registros, Cabecalho* indice)
{
	if(!indice)
		return;
	
	fseek(registros, 0, SEEK_SET);

	fwrite(indice, sizeof(Cabecalho), 1, registros);
}

void criaIndicesArq(FILE *binario)
{
	Cabecalho indice;

	indice.topo = -1;
	indice.quantidade = 0;
	indice.nohsLivre = -1;
	indice.quantidadeLivre = 0;

	escreveCabecalho(binario, &indice);
}

Livres* criaNohLivre()
{
	Livres* novo = (Livres*)malloc(sizeof(Livres));

	novo->prox = -1;

	return novo;
}

void liberaNoh(ArvoreB* alvo)
{
	if(alvo)
		free(alvo);
}

ArvoreB* inicializaArvore()
{
	ArvoreB* new = (ArvoreB*)malloc(sizeof(ArvoreB));

	new->numChaves = 0;
	new->posicao = -1;
	
	int i;

	for(i = 0; i < ORDEM; i++)
	{
		new->chave[i].codigo = 0;
		new->chave[i].registroPos = -1;
		new->filho[i] = -1;
	}
	
	return new;
}

Cabecalho* leituraDoCabecalho(FILE* binario)
{
    Cabecalho* cabeca = (Cabecalho*)malloc(sizeof(Cabecalho));

    fseek(binario, 0, SEEK_SET);

    fread(cabeca, sizeof(Cabecalho), 1, binario);

    return cabeca;
}

void escreveNosLivres(FILE* registros, Cabecalho* indice, ArvoreB* raiz)
{
	if(!indice)
		return;

	int pos;

	pos = raiz->posicao;
	Livres* nos = criaNohLivre();

	nos->prox = indice->nohsLivre;
	indice->nohsLivre = pos;

	indice->quantidadeLivre++;

	fseek(registros, sizeof(Cabecalho)+sizeof(ArvoreB)*pos, SEEK_SET);

	fwrite(nos, sizeof(Livres), 1, registros);

	free(nos);
}

Cadastro* inicializaCadastro()
{
	Cadastro* novo = (Cadastro*)malloc(sizeof(Cadastro));

	novo->codigo = 0;
	novo->nome[0] = '\0';
	novo->sexo = '\0';
	novo->cpf[0] = '\0';
	novo->crm[0] = '\0';
	novo->especialidade[0] = '\0';
	novo->rg[0] = '\0';
	novo->telefone[0] = '\0';
	novo->celular[0] = '\0';
	novo->email[0] = '\0';
	novo->endereco[0] = '\0';
	novo->nascimento[0] = '\0';

	return novo;
}

void remocaoPorFolha(ArvoreB *raiz, int pos) 
{
    for (int i = pos + 1; i < raiz->numChaves; ++i) {
        raiz->chave[i - 1] = raiz->chave[i];
    }

    raiz->numChaves--;
}

RegistrosDat pegaPrede(FILE *registros, ArvoreB *raiz, int pos) {
    ArvoreB *atual = leituraDoNoh(registros, raiz->filho[pos]);
    ArvoreB *proximo = NULL;
    RegistrosDat pred;

    while (!eh_folha(atual)) {
        proximo = leituraDoNoh(registros, raiz->numChaves);
        liberaNoh(atual);
        atual = proximo;
    }

    pred = atual->chave[atual->numChaves - 1];
    liberaNoh(atual);

    return pred;
}

RegistrosDat pegaSucessor(FILE *registros, ArvoreB *raiz, int pos) {
    ArvoreB *atual = leituraDoNoh(registros, raiz->filho[pos + 1]);
    ArvoreB *proximo = NULL;
    RegistrosDat sucessor;

    while (!eh_folha(atual)) 
    {
        proximo = leituraDoNoh(registros, 0);
        liberaNoh(atual);
        atual = proximo;
    }

    sucessor = atual->chave[0];
    liberaNoh(atual);

    return sucessor;
}

void merge(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos) 
{
    ArvoreB *filho = leituraDoNoh(registros, pos);
    ArvoreB *sobrinho = leituraDoNoh(registros, pos + 1);

    filho->chave[(ORDEM - 1) / 2 - 1] = raiz->chave[pos];

    for (int i = 0; i < sobrinho->numChaves; ++i) {
        filho->chave[i + (ORDEM - 1) / 2] = sobrinho->chave[i];
    }

    if (!eh_folha(filho)) {
        for (int i = 0; i <= sobrinho->numChaves; ++i)
            filho->filho[i + (ORDEM - 1) / 2] = sobrinho->filho[i];
    }

    for (int i = pos + 1; i < raiz->numChaves; ++i)
        raiz->chave[i - 1] = raiz->chave[i];

    for (int i = pos + 2; i <= raiz->numChaves; ++i)
        raiz->filho[i - 1] = raiz->filho[i];

    filho->numChaves += sobrinho->numChaves + 1;
    raiz->numChaves--;

    escreveArvore(registros, filho,indice);
    escreveArvore(registros, raiz, indice);

    escreveNosLivres(registros, indice, sobrinho);

    escreveCabecalho(registros, indice);

    liberaNoh(sobrinho);
    liberaNoh(filho);
}

void emprestaDoAnt(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos) {
    ArvoreB *filho = leituraDoNoh(registros, raiz->filho[pos]);
    ArvoreB *sobrinho = leituraDoNoh(registros, raiz->filho[pos - 1]);

    for (int i = filho->numChaves - 1; i >= 0; --i)
        filho->chave[i + 1] = filho->chave[i];

    if (!eh_folha(filho)) {
        for (int i = filho->numChaves; i >= 0; --i)
            filho->filho[i + 1] = filho->filho[i];
    }

    filho->chave[0] = raiz->chave[pos - 1];

    if (!eh_folha(filho))
        filho->filho[0] = sobrinho->filho[sobrinho->numChaves];

    raiz->chave[pos - 1] = sobrinho->chave[sobrinho->numChaves - 1];

    filho->numChaves += 1;
    sobrinho->numChaves -= 1;

    escreveArvore(registros, filho, indice);
    escreveArvore(registros, sobrinho, indice);
    escreveArvore(registros, raiz, indice);

    liberaNoh(filho);
    liberaNoh(sobrinho);
}

void emprestaDoProx(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos) {
    ArvoreB *filho = leituraDoNoh(registros, raiz->filho[pos]);
    ArvoreB *sobrinho = leituraDoNoh(registros, raiz->filho[pos + 1]);

    filho->chave[filho->numChaves] = raiz->chave[pos];

    if (!eh_folha(filho)) {
        filho->filho[(filho->numChaves) + 1] = sobrinho->filho[0];
    }

    filho->chave[pos] = raiz->chave[0];

    for (int i = 1; i < sobrinho->numChaves; ++i) {
        sobrinho->chave[i - 1] = sobrinho->chave[i];
    }

    if (!eh_folha(sobrinho)) 
    {
        for (int i = 1; i <= sobrinho->numChaves; ++i) 
            sobrinho->filho[i - 1] = sobrinho->filho[i];
        
    }

    filho->numChaves += 1;
    sobrinho->numChaves -= 1;

    escreveArvore(registros, filho, indice);
    escreveArvore(registros, sobrinho, indice);
    escreveArvore(registros, raiz, indice);

    liberaNoh(filho);
    liberaNoh(sobrinho);
}

void enche(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos) {
    ArvoreB *filhoAnt = leituraDoNoh(registros, raiz->filho[pos - 1]);
    ArvoreB *filhoProx = leituraDoNoh(registros, raiz->filho[pos + 1]);

    if (pos != 0 && filhoAnt->numChaves - 1 >= ORDEM / 2) 
    {
        emprestaDoAnt(registros, indice, raiz, pos);
    } 
    else if (pos != raiz->numChaves && filhoProx->numChaves - 1 >= ORDEM / 2) 
    {
        emprestaDoProx(registros, indice, raiz, pos);
    } 
    else 
    {
        if (pos != raiz->numChaves) 
        {
            merge(registros, indice, raiz, pos);
        } 
        else 
        {
            merge(registros, indice, raiz, pos - 1);
        }
    }

    liberaNoh(filhoProx);
    liberaNoh(filhoAnt);
}

void remocaoAux(FILE *registros, Cabecalho *indice, ArvoreB *raiz, RegistrosDat dados) 
{
    int pos;
    buscaPos(raiz, dados.codigo, &pos);

    if (pos < raiz->numChaves && raiz->chave[pos].codigo == dados.codigo) {
        if (eh_folha(raiz)) {
            remocaoPorFolha(raiz, pos);
        } else {
            remocaoDoInterior(registros, indice, raiz, pos);
        }
        escreveArvore(registros, raiz, indice);
    } else {
        if (eh_folha(raiz)) {
            printf("Dado nao presente na Arvore\n");
            return;
        }

        int flag = (pos == raiz->numChaves);

        ArvoreB *proxRaiz = leituraDoNoh(registros, raiz->filho[pos]);

        if (proxRaiz->numChaves < ORDEM / 2) {
            enche(registros, indice, raiz, pos);
        }

        ArvoreB *raizAnt = NULL;
        ArvoreB *modificado = NULL;
        if (flag && pos > raiz->numChaves) {
            remocaoAux(registros, indice, raizAnt = leituraDoNoh(registros, raiz->filho[pos - 1]), dados);
            modificado = raizAnt;
        } else {
            remocaoAux(registros, indice, proxRaiz, dados);
            modificado = proxRaiz;
        }

        if (modificado->numChaves < ORDEM / 2) {
            enche(registros, indice, raiz, pos);
        }

        liberaNoh(raizAnt);
        liberaNoh(proxRaiz);
    }
}

void remocaoDoInterior(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos) 
{
    RegistrosDat k = raiz->chave[pos];

    ArvoreB *filhoEsq = leituraDoNoh(registros, raiz->filho[pos]);
    ArvoreB *filhoDir = leituraDoNoh(registros, raiz->filho[pos + 1]);

    if (filhoEsq->numChaves >= ORDEM / 2) 
    {
        RegistrosDat predecessor = pegaPrede(registros, raiz, pos);
        raiz->chave[pos] = predecessor;
        remocaoAux(registros, indice, filhoEsq, predecessor);
    } 
    else if (filhoDir->numChaves >= ORDEM / 2) 
    {
        RegistrosDat sucessor = pegaSucessor(registros, raiz, pos);
        raiz->chave[pos] = sucessor;
        remocaoAux(registros, indice, filhoDir, sucessor);
    } 
    else {
        merge(registros, indice, raiz, pos);
        remocaoAux(registros, indice, filhoEsq, k);
    }

    escreveArvore(registros, filhoEsq, indice);
    escreveArvore(registros, filhoDir, indice);
    escreveArvore(registros, raiz, indice);

    liberaNoh(filhoEsq);
    liberaNoh(filhoDir);
}

void remocao(FILE *registros)
{
	int codigo;
	printf("Chave a ser Removida: ");
	scanf("%d%*c", &codigo);

    Cabecalho *indice = leituraDoCabecalho(registros);
    ArvoreB *raiz = leituraDoNoh(registros, indice->topo);

    RegistrosDat dados;
    dados.codigo = codigo;
    dados.registroPos = -1;

    remocaoAux(registros, indice, raiz, dados);

    liberaNoh(raiz);
    free(indice);
}

void printMedico(Cadastro *medico) 
{
    if(!medico)
        return;

    printf("Codigo: %d\n", medico->codigo);

    printf("Nome: %s\n", medico->nome);

    printf("Sexo: %c\n", medico->sexo);

    printf("CPF: %s\n", medico->cpf);

    printf("CRM: %s\n", medico->crm);

    printf("Especialidade: %s\n", medico->especialidade);

    printf("RG: %s\n", medico->rg);

    printf("Telefone: %s\n", medico->telefone);

    printf("Celular: %s\n", medico->celular);

    printf("Email: %s\n", medico->email);

    printf("Endereco: %s\n", medico->endereco);

    printf("Data de nascimento: %s\n", medico->nascimento);
}

void leituraEmCMD(FILE *registros, FILE *dados) 
{
    Cadastro *medico = inicializaCadastro();

    printf("Codigo: ");
    scanf("%d", &medico->codigo);

    printf("Nome: ");
    scanf(" %[^\n]%*c", medico->nome);

    printf("Sexo: ");
    scanf("%c", &medico->sexo);

    printf("CPF: ");
    scanf(" %[^\n]%*c", medico->cpf);

    printf("CRM: ");
    scanf("%[^\n]%*c", medico->crm);

    printf("Especialidade: ");
    scanf("%[^\n]%*c", medico->especialidade);

    printf("RG: ");
    scanf("%[^\n]%*c", medico->rg);

    printf("Telefone: ");
    scanf("%[^\n]%*c", medico->telefone);

    printf("Celular: ");
    scanf("%[^\n]%*c", medico->celular);

    printf("Email: ");
    scanf("%[^\n]%*c", medico->email);

    printf("Endereco: ");
    scanf("%[^\n]%*c", medico->endereco);

    printf("Data de nascimento: ");
    scanf("%[^\n]%*c", medico->nascimento);  

    if (!medico->rg[0] || medico->codigo == -1 || !medico->nome[0] || medico->sexo == '\0' || !medico->cpf[0] || !validaDado(medico->cpf) || !medico->crm[0] 
    	|| !validaDado(medico->telefone) || !validaDado(medico->celular) || !medico->nascimento[0]) {

        printf("Cadastro Invalido!\n");

    } 
    else 
    {
        CabecalhoDados *indice = leCabecalhoDat(dados);
        int pos = escreverRegistro(dados, indice, medico);

        insere(registros, medico->codigo, pos);

        free(indice);
    	escreveCabecalhoDat(dados, indice);
    }

    free(medico);
}

void imprimeInOrd(FILE *registros, Cabecalho *indice, FILE *dados, CabecalhoDados *raizDat, ArvoreB *raiz) {
    ArvoreB *aux = NULL;
    Cadastro *medico = (Cadastro*)malloc(sizeof(Cadastro));

    if (!raiz)
        return;

    for (int i = 0; i < raiz->numChaves; ++i) 
    {
        imprimeInOrd(registros, indice, dados, raizDat, aux = leituraDoNoh(registros, raiz->filho[i]));

       	medico = leDados(dados, raizDat, raiz->chave[i].registroPos);
        printMedico(medico);
        
        printf("\n");

        liberaNoh(aux);
        free(medico);
    }

    imprimeInOrd(registros, indice, dados, raizDat, aux = leituraDoNoh(registros, raiz->filho[raiz->numChaves]));
    liberaNoh(aux);
}

void imprimeRegistro(FILE *registros, FILE *dados) 
{
	system("CLS");
    Cabecalho *indice = leituraDoCabecalho(registros);
    CabecalhoDados *raizDat = leCabecalhoDat(dados);

    ArvoreB *raiz = leituraDoNoh(registros, indice->topo);

    if (raiz) 
    {
        imprimeInOrd(registros, indice, dados, raizDat, raiz);
    }

    free(indice);
    free(raizDat);
}

Cadastro* procuraCadastro(FILE *registro, FILE *dados, int codigo, int *posicaoRegistro) 
{
    Cabecalho *indice = leituraDoCabecalho(registro);
    CabecalhoDados *indiceDat = leCabecalhoDat(dados);
    ArvoreB *raiz = leituraDoNoh(registro, indice->topo);
    ArvoreB *aux = raiz;
    Cadastro *medico = NULL;
    int pos, achou;

    if(raiz)
    {
        while (!(achou = buscaPos(aux, codigo, &pos)) && !eh_folha(aux)) {
            liberaNoh(aux);
            aux = leituraDoNoh(registro, aux->filho[pos]);
        }

        if (achou) 
        {
            system("CLS");
            medico = leDados(dados, indiceDat, aux->chave[pos].registroPos);
            *posicaoRegistro = aux->chave[pos].registroPos;
        } else {
            printf("Registro nao encontrado!\n");
        }

        liberaNoh(aux);
    }

    free(indice);
    free(indiceDat);

    return medico;
}

void alteraRegistro(FILE* dados, Cadastro* medico, int posicao)
{
	fseek(dados, sizeof(CabecalhoDados) + sizeof(Cadastro)*posicao, SEEK_SET);

	fwrite(&medico->codigo, sizeof(int), 1, dados);
	fwrite(medico->nome, sizeof(char)* 100, 1, dados);
	fwrite(&medico->sexo, sizeof(char), 1, dados);
	fwrite(medico->cpf, sizeof(char)* 22, 1, dados);
	fwrite(medico->crm, sizeof(char)* 30, 1, dados);
	fwrite(medico->especialidade, sizeof(char)* 100, 1, dados);
	fwrite(medico->rg, sizeof(char)* 22, 1, dados);
	fwrite(medico->telefone, sizeof(char)* 23, 1, dados);
	fwrite(medico->celular, sizeof(char)* 24, 1, dados);
	fwrite(medico->email, sizeof(char)* 100, 1, dados);
	fwrite(medico->endereco, sizeof(char)* 100, 1, dados);
	fwrite(medico->nascimento, sizeof(char)* 21, 1, dados);
}

void alterar(FILE* registros, FILE* dados)
{
	Cabecalho *indice = leituraDoCabecalho(registros);
	CabecalhoDados* indiceDat = leCabecalhoDat(dados);

	char alteracao[256];
	int codigoAlvo, opcao, posicao;
	printf("Entre com o codigo do Medico a ser Alterado: ");
	scanf("%d", &codigoAlvo);

	Cadastro* medico = procuraCadastro(registros, dados, codigoAlvo, &posicao);

	if(!medico)
	{
		printf("Medico nao pertencente!\n");
		return;
	}

	else{
		system("CLS");
		
		printf("\n	Codigo: %d\n", medico->codigo);

	    printf("	Nome: %s\n", medico->nome);

	    printf("	Sexo: %c\n", medico->sexo);

	    printf("	CPF: %s\n", medico->cpf);

	    printf("	CRM: %s\n", medico->crm);

	    printf("	Especialidade: %s\n", medico->especialidade);

	    printf("	RG: %s\n", medico->rg);

	    printf("	Telefone: %s\n", medico->telefone);

	    printf("	Celular: %s\n", medico->celular);

	    printf("	Email: %s\n", medico->email);

	    printf("	Endereco: %s\n", medico->endereco);

	    printf("	Data de nascimento: %s\n", medico->nascimento);

		do{
			printf("\n[1] Alterar Telefone\n");
			printf("[2] Alterar Celular\n");
			printf("[3] Alterar E-mail\n");
			printf("[4] Alterar Endereco\n");
			printf("[0] Fechar\n");
			printf("	Opcao: ");
			scanf("%d%*c", &opcao);

			switch(opcao)
			{
				case 1:
					printf("Novo Telefone: ");
					scanf("%[^\n]%*c", alteracao);

					if(validaDado(alteracao))
						strcpy(medico->telefone, alteracao);

					break;
				case 2:
					printf("Novo Celular: ");
					scanf("%[^\n]%*c", alteracao);

					if(validaDado(alteracao))
						strcpy(medico->celular, alteracao);
					break;
				case 3:
					printf("Novo E-mail: ");
					scanf("%[^\n]%*c", alteracao);

					if(alteracao[0])
						strcpy(medico->email, alteracao);
					break;
				case 4:
					printf("Novo Endereco: ");
					scanf("%[^\n]%*c", alteracao);

					if(alteracao[0])
						strcpy(medico->endereco, alteracao);
					break;	
				default:
					printf("Fechando\n");
					break;
			}
			
			alteraRegistro(dados, medico, posicao);
		}while(opcao);

	}
}	