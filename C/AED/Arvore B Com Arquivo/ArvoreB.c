#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ArvoreB.h"

int validaCPF(char *s)
{	
	if(s[0] == '\0')
		return 1;

	int i;
	for(i = 0; i < strlen(s); i++)
		if(s[i] < '0' && s[i] > '9')
			if(s[i] == '-' && i != 9)
				return 1;

	return 0;
}

int validaTelefone(char *s)
{
	if(s[0] == '\0')
		return 1;

	int i;
	for(i = 0; i < strlen(s); i++)
		if(s[i] < '0' && s[i] > '9')
			if(s[i] == '-' && (i != 2 || i != 7))
				return 1;

	return 0;
}

int validaCelular(char *s)
{
	if(s[0] == '\0')
		return 1;

	int i;
	for(i = 0; i < strlen(s); i++)
		if(s[i] < '0' && s[i] > '9')
			if(s[i] == '-' && (i != 2 || i != 8))
				return 1;

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
	fread(&novo->cpf, sizeof(char)* 12, 1, dados);
	fread(&novo->crm, sizeof(char)* 20, 1, dados);
	fread(&novo->especialidade, sizeof(char)* 100, 1, dados);
	fread(&novo->rg, sizeof(char)* 12, 1, dados);
	fread(&novo->telefone, sizeof(char)* 13, 1, dados);
	fread(&novo->celular, sizeof(char)* 14, 1, dados);
	fread(&novo->email, sizeof(char)* 100, 1, dados);
	fread(&novo->endereco, sizeof(char)* 100, 1, dados);
	fread(&novo->nascimento, sizeof(char)* 11, 1, dados);

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


int escreverRegistro(FILE* dados, CabecalhoDados* indice, Cadastro* medico)
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

	fwrite(&medico->codigo, sizeof(int), 1, dados);
	fwrite(medico->nome, sizeof(char)* 100, 1, dados);
	fwrite(&medico->sexo, sizeof(char), 1, dados);
	fwrite(medico->cpf, sizeof(char)* 12, 1, dados);
	fwrite(medico->crm, sizeof(char)* 20, 1, dados);
	fwrite(medico->especialidade, sizeof(char)* 100, 1, dados);
	fwrite(medico->rg, sizeof(char)* 12, 1, dados);
	fwrite(medico->telefone, sizeof(char)* 13, 1, dados);
	fwrite(medico->celular, sizeof(char)* 14, 1, dados);
	fwrite(medico->email, sizeof(char)* 100, 1, dados);
	fwrite(medico->endereco, sizeof(char)* 100, 1, dados);
	fwrite(medico->nascimento, sizeof(char)* 11, 1, dados);

	return pos;
}

void criaIndicesArqDat(FILE *binario)
{
	CabecalhoDados indice;

	indice.topo = -1;
	indice.nohsLivre = -1;

	escreveCabecalhoDat(binario, &indice);
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
		fscanf(texto, "%d :", &medicos->codigo);
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
	    
	    fscanf(texto, "%[^\n]", medicos->nascimento);

	    if(!medicos->rg[0] || medicos->codigo == -1 || !medicos->nome[0] || medicos->sexo == '\0' || !medicos->cpf[0] || validaCPF(medicos->cpf) || !medicos->crm[0] || validaTelefone(medicos->telefone) || validaCelular(medicos->celular) || !medicos->nascimento[0])
	    {
	    	printf("Cadastro Invalido!\n");
	    }
	    else
	    {
    		int pos = escreverRegistro(dados, indice, medicos);
    		insere(arvore, medicos->codigo, pos);
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
	Cadastro* novo;

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

/*void printaCadastro(FILE* dados)
{
	int i;
	system("CLS");
	for(i = 0; i < MAX; i++)
	{
	    printf("//----------------------------------------//\n");
		printf("Medico[%d]\n", i);
		printf("Codigo: %d\n", medicos[i].codigo);
		
	    printf("Nome: %s\n", medicos[i].nome);
	    
	    printf("Sexo: %s\n", medicos[i].sexo);
	   
	    printf("CPF: %s\n", medicos[i].cpf);
	    
	    printf("CRM: %s\n", medicos[i].crm);
	    
	    printf("Especialidade: %s\n", medicos[i].especialidade);
	    
	    printf("RG: %s\n", medicos[i].rg);
	    
	    printf("Telefone: %s\n", medicos[i].telefone);
	    
	    printf("Celular: %s\n", medicos[i].celular);
	    
	    printf("Email: %s\n", medicos[i].email);
	    
	    printf("Endereco: %s\n", medicos[i].endereco);
	    
	    printf("Data de Nascimento: %s\n", medicos[i].nascimento);
	}
}


void removeBTree(FILE *fTree, int id) {
    BTreeHeader *header = readBTreeHeader(fTree);
    BTreeNode *root = readBTreeNode(fTree, header->root);

    RegData data = {.id = id, .regPos = -1};

    removeBTreeAux(fTree, header, root, data);

    freeBTreeNode(root);
    free(header);
}

void removeBTreeAux(FILE *fTree, BTreeHeader *header, BTreeNode *node, RegData info) {
    int pos;
    searchBTreePos(node, info.id, &pos);

    if (pos < node->keyNum && node->keys[pos].id == info.id) {
        if (isLeaf(node)) {
            removeFromLeaf(node, pos);
        } else {
            removeFromInnerNode(fTree, header, node, pos);
        }
        writeNodeToFile(fTree, header, node);
    } else {
        if (isLeaf(node)) {
            printf("The value [%d] is not present in tree\n", info);
            return;
        }

        int flag = (pos == node->keyNum);

        BTreeNode *nextNode = readBTreeNode(fTree, node->children[pos]);
//        printf("nextNode->keyNum = %d\n", nextNode->keyNum);
        printBTreeNodeKeys(nextNode);
        if (nextNode->keyNum < ORDER / 2) {
            fill(fTree, header, node, pos);
        }

        BTreeNode *prevNode = NULL;
        BTreeNode *modifiedNode = NULL;
        if (flag && pos > node->keyNum) {
            removeBTreeAux(fTree, header, prevNode = readBTreeNode(fTree, node->children[pos - 1]), info);
            modifiedNode = prevNode;
        } else {
//            printf("removeBTreeAux (0)\n");
            removeBTreeAux(fTree, header, nextNode, info);
            modifiedNode = nextNode;
        }

        if (modifiedNode->keyNum < ORDER / 2) {
            fill(fTree, header, node, pos);
        }

        freeBTreeNode(prevNode);
        freeBTreeNode(nextNode);
    }
}

void removeFromLeaf(BTreeNode *node, int pos) {
    for (int i = pos + 1; i < node->keyNum; ++i) {
        node->keys[i - 1] = node->keys[i];
    }

    node->keyNum--;
}

void removeFromInnerNode(FILE *fTree, BTreeHeader *header, BTreeNode *node, int pos) {
    RegData k = node->keys[pos];

    BTreeNode *leftChildNode = readBTreeNode(fTree, node->children[pos]);
    BTreeNode *rightChildNode = readBTreeNode(fTree, node->children[pos + 1]);

//    printf("removeFromInnerNode (0)\n");

    if (leftChildNode->keyNum >= ORDER / 2) {
        RegData pred = getPred(fTree, node, pos);
        node->keys[pos] = pred;
        removeBTreeAux(fTree, header, leftChildNode, pred);
    } else if (rightChildNode->keyNum >= ORDER / 2) {
        RegData succ = getSucc(fTree, node, pos);
        node->keys[pos] = succ;
        removeBTreeAux(fTree, header, rightChildNode, succ);
    } else {
//        printf("removeFromInnerNode (1)\n");
        merge(fTree, header, node, pos);
        removeBTreeAux(fTree, header, leftChildNode, k);
    }

    writeNodeToFile(fTree, header, leftChildNode);
    writeNodeToFile(fTree, header, rightChildNode);
    writeNodeToFile(fTree, header, node);

    freeBTreeNode(leftChildNode);
    freeBTreeNode(rightChildNode);
}

RegData getPred(FILE *f, BTreeNode *node, int pos) {
    BTreeNode *current = readBTreeNode(f, node->children[pos]);
    BTreeNode *next = NULL;
    RegData pred;

    while (!isLeaf(current)) {
        next = readBTreeNode(f, node->keyNum);
        freeBTreeNode(current);
        current = next;
    }

    pred = current->keys[current->keyNum - 1];
    freeBTreeNode(current);

    return pred;
}


RegData getSucc(FILE *f, BTreeNode *node, int pos) {
    BTreeNode *current = readBTreeNode(f, node->children[pos + 1]);
    BTreeNode *next = NULL;
    RegData succ;

    while (!isLeaf(current)) {
        next = readBTreeNode(f, 0);
        freeBTreeNode(current);
        current = next;
    }

    succ = current->keys[0];
    freeBTreeNode(current);

    return succ;
}

void merge(FILE *fTree, BTreeHeader *header, BTreeNode *node, int pos) {
    BTreeNode *child = readBTreeNode(fTree, pos);
    BTreeNode *sibling = readBTreeNode(fTree, pos + 1);

//    printf("merge (0)\n");

    child->keys[(ORDER - 1) / 2 - 1] = node->keys[pos];

    for (int i = 0; i < sibling->keyNum; ++i) {
        child->keys[i + (ORDER - 1) / 2] = sibling->keys[i];
    }

    if (!isLeaf(child)) {
        for (int i = 0; i <= sibling->keyNum; ++i)
            child->children[i + (ORDER - 1) / 2] = sibling->children[i];
    }

    for (int i = pos + 1; i < node->keyNum; ++i)
        node->keys[i - 1] = node->keys[i];

    for (int i = pos + 2; i <= node->keyNum; ++i)
        node->children[i - 1] = node->children[i];

    child->keyNum += sibling->keyNum + 1;
    node->keyNum--;

    writeNodeToFile(fTree, header, child);
    writeNodeToFile(fTree, header, node);

    writeBTreeFreeNodesList(fTree, header, sibling);

    writeBTreeHeaderToFile(fTree, header);

    freeBTreeNode(sibling);
    freeBTreeNode(child);
}

void fill(FILE *fTree, BTreeHeader *header, BTreeNode *node, int pos) {
    BTreeNode *childPrev = readBTreeNode(fTree, node->children[pos - 1]);
    BTreeNode *childNext = readBTreeNode(fTree, node->children[pos + 1]);

    if (pos != 0 && childPrev->keyNum - 1 >= ORDER / 2) {
//        printf("fill (0)\n");
        borrowFromPrev(fTree, header, node, pos);
    } else if (pos != node->keyNum && childNext->keyNum - 1 >= ORDER / 2) {
        borrowFromNext(fTree, header, node, pos);
    } else {
        if (pos != node->keyNum) {
            merge(fTree, header, node, pos);
        } else {
            merge(fTree, header, node, pos - 1);
        }
    }

    freeBTreeNode(childNext);
    freeBTreeNode(childPrev);
}

void borrowFromPrev(FILE *fTree, BTreeHeader *header, BTreeNode *node, int pos) {
    BTreeNode *child = readBTreeNode(fTree, node->children[pos]);
    BTreeNode *sibling = readBTreeNode(fTree, node->children[pos - 1]);

    for (int i = child->keyNum - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!isLeaf(child)) {
        for (int i = child->keyNum; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    child->keys[0] = node->keys[pos - 1];

    if (!isLeaf(child))
        child->children[0] = sibling->children[sibling->keyNum];

    node->keys[pos - 1] = sibling->keys[sibling->keyNum - 1];

    child->keyNum += 1;
    sibling->keyNum -= 1;

    writeNodeToFile(fTree, header, child);
    writeNodeToFile(fTree, header, sibling);
    writeNodeToFile(fTree, header, node);

    freeBTreeNode(child);
    freeBTreeNode(sibling);
}

void borrowFromNext(FILE *fTree, BTreeHeader *header, BTreeNode *node, int pos) {
    BTreeNode *child = readBTreeNode(fTree, node->children[pos]);
    BTreeNode *sibling = readBTreeNode(fTree, node->children[pos + 1]);

    child->keys[(child->keyNum)] = node->keys[pos];

    if (!isLeaf(child)) {
        child->children[(child->keyNum) + 1] = sibling->children[0];
    }

    child->keys[pos] = node->keys[0];

    for (int i = 1; i < sibling->keyNum; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
    }

    if (!isLeaf(sibling)) {
        for (int i = 1; i <= sibling->keyNum; ++i) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    child->keyNum += 1;
    sibling->keyNum -= 1;

    writeNodeToFile(fTree, header, child);
    writeNodeToFile(fTree, header, sibling);
    writeNodeToFile(fTree, header, node);

    freeBTreeNode(child);
    freeBTreeNode(sibling);
}*/

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

    if (!medico->rg[0] || medico->codigo == -1 || !medico->nome[0] || medico->sexo == '\0' || !medico->cpf[0] || validaCPF(medico->cpf) || !medico->crm[0] 
    	|| validaTelefone(medico->telefone) || validaCelular(medico->celular) || !medico->nascimento[0]) {

        printf("Cadastro Invalido!\n");

    } else {
        CabecalhoDados *indice = leCabecalhoDat(dados);
        int pos = escreverRegistro(dados, indice, medico);

        insere(registros, medico->codigo, pos);

        free(indice);
    }

    free(medico);
}

void imprimeInOrd(FILE *registros, Cabecalho *indice, FILE *dados, CabecalhoDados *raizDat, ArvoreB *raiz) {
    ArvoreB *aux = NULL;
    Cadastro *medico = NULL;

    if (!raiz)
        return;

    for (int i = 0; i < raiz->numChaves; ++i) 
    {
        imprimeInOrd(registros, indice, dados, raizDat, aux = leituraDoNoh(registros, raiz->filho[i]));
        printMedico(medico = leDados(dados, raizDat, raiz->chave[i].registroPos));
        
        printf("\n");

        liberaNoh(aux);
        free(medico);
    }

    imprimeInOrd(registros, indice, dados, raizDat, aux = leituraDoNoh(registros, raiz->filho[raiz->numChaves]));
    liberaNoh(aux);
}

void imprimeRegistro(FILE *registros, FILE *dados) 
{
    Cabecalho *indice = leituraDoCabecalho(registros);
    CabecalhoDados *raizDat = leCabecalhoDat(dados);

    ArvoreB *raiz = leituraDoNoh(registros, indice->topo);

    if (raiz) {
        imprimeInOrd(registros, indice, dados, raizDat, raiz);
    }

    free(indice);
    free(raizDat);
}

void procuraCadastro(FILE *registro, FILE *dados) 
{
    Cabecalho *indice = leituraDoCabecalho(registro);
    CabecalhoDados *indiceDat = leCabecalhoDat(dados);
    ArvoreB *raiz = leituraDoNoh(registro, indice->topo);
    ArvoreB *aux = raiz;
    int codigo, pos, achou;

    if (raiz) 
    {
        printf("Digite o codigo a ser pesquisado: ");
        scanf("%d", &codigo);

        while (!(achou = buscaPos(aux, codigo, &pos)) && !eh_folha(aux)) {
            liberaNoh(aux);
            aux = leituraDoNoh(registro, pos);
        }

        if (achou) {
            system("CLS");
            Cadastro *medico= leDados(dados, indiceDat, aux->chave[pos].registroPos);
            printMedico(medico);
            free(medico);
            liberaNoh(aux);
        } else {
            printf("Registro nao encontrado!\n");
        }


    }

    free(indice);
    free(indiceDat);
}