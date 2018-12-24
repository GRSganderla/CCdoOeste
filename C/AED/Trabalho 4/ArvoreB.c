#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<ctype.h>
#include "ArvoreB.h"

///
/// \brief leituraDoNoh, procura no arquivo a posição do nó a ser lido e guarda em uma variavel tipo ArvoreB 
/// \param binario, arquivo da Arvore-B que contém todos os dados dos nós inseridos 
/// \param posicao, posição aonde o nó esta inserido e quer ser lido 
/// \return uma variavel do tipo ArvoreB que contém os dados do nó da posição lida
/// \pre nenhuma
/// \post nenhuma
///
ArvoreB* leituraDoNoh(FILE* binario, int posicao)
{
	ArvoreB* nois;
	//se a posição buscada não é permitida, retorna nulo
	if(posicao == -1)
	{
		return NULL;
	}

    nois = (ArvoreB*)malloc(sizeof(ArvoreB));
    //busca a posição no arquivo
    fseek(binario, sizeof(Cabecalho) + sizeof(ArvoreB)*posicao , SEEK_SET);
    //lê o nó naquela posição
    fread(nois, sizeof(ArvoreB), 1, binario);
    //retorna o nó
    return nois;
}

///
/// \brief escreveArvore, escreve o nó passado por parametro dentro do arquivo 
/// \param registros, arquivo aonde será escrito 
/// \param galho, nó da Arvore-B que sera escrito no arquivo 
/// \param indice, cabeçalho do arquivo que terá indices atualizados
/// \return a posição aonde foi escrito no arquivo o nó
/// \pre nenhuma
/// \post nenhuma
///
int escreveArvore(FILE* registros, ArvoreB* galho, Cabecalho* indice)
{
	int posicao;
	//se não tem cabeçalho ou nó
	if(!indice || !galho) return -1;

	//pega a posição do nó
	posicao = galho->posicao;	

	//se não foi atribuida
	if(posicao == -1)
	{
		//atribui o topo e escreve o cabeçalho
		posicao = indice->topo++;
		escreveCabecalho(registros, indice);	
	}
	
	//nó recebe sua posição
	galho->posicao = posicao;
	//busca sua posição e escreve o nó lá
	fseek(registros, sizeof(Cabecalho) + sizeof(ArvoreB) * posicao, SEEK_SET);
	fwrite(galho, sizeof(ArvoreB), 1, registros);
	//retorna a posição do nó
	return posicao;
}

///
/// \brief overflow, funcao que testa se o nó atual esta com o numero de chaves com o maximo possivel de chaves
/// \param r, nó atual que contem o numero de chaves
/// \return 1, se tiver overflow, ou, 0, se n tiver overflow
/// \pre nenhuma
/// \post nenhuma
///
int overflow(ArvoreB* r)
{
	return (r->numChaves == ORDEM);
}

///
/// \brief vazia, testa se o nó é vazio
/// \param r, nó da Arvore-B que será testado
/// \return 1, se for vazia, 0 se não for
/// \pre nenhuma
/// \post nenhuma
///
int vazia(ArvoreB* r)
{
	return (r == NULL);
}

///
/// \brief split, reparte o nó atual pela metade e cria um novo nó que contem a outra metade
/// \param x, nó que tem overflow e vai ser repartido
/// \param m, variavel que recebe a chave mediana do nó x
/// \return um nó y, que contem a outra metade do nó x repartido
/// \pre nenhuma
/// \post nenhuma
///
ArvoreB* split(ArvoreB* x, RegistrosDat *m) 
{
	//cria uma novo nó
	ArvoreB* nova = inicializaArvore();

	//o novo nó recebe a metade do número de chaves da árvore pai
	int q = (ORDEM-1)/2;
	nova->numChaves =  q;
	x->numChaves = q;
	
	//o ponteiro de Registro recebe a chave do meio
	*m = x->chave[q];
	int i = 0;
	
	//atualiza os filhos e chaves do pai e insere as chaves e filhos no novo nó
	nova->filho[0] = x->filho[q+1];
	
	for(i = 0; i < nova->numChaves; i++)
	{
		nova->chave[i] = x->chave[q+i+1];
		nova->filho[i+1] = x->filho[q+i+2];
	}

	//retorna o novo nó
	return nova;
}

///
/// \brief adicionaDireita, adiciona a chave no vetor de chaves do nó, colocando se precisar todas as outras chaves para a direita do numero
/// \param r, nó que recebe a chave
/// \param pos, posicao da chave
/// \param k, chave a ser adicionada
/// \param p, filho que a chave nova vai ser adiciona
/// \pre nenhuma
/// \post nenhuma
///
void adicionaDireita(ArvoreB* r, int pos, RegistrosDat info, int p)
{
	int i;

	//até a posição desejada
	for(i=r->numChaves; i>pos; i--)
	{
		//avança as chaves e filhos do nó
		r->chave[i] = r->chave[i-1];
		r->filho[i+1] = r->filho[i];
	}
	
	//a chave desejada recebe a nova chave e um novo filho
	r->chave[pos] = info;
	r->filho[pos+1] = p;
	r->numChaves++;
}

///
/// \brief insere_aux, busca e insere o info no arquivo
/// \param registros, arquivo que contem os dados da arvore
/// \param indice, cabecalho do arquivo
/// \param r, arvore que contem os registros
/// \param info, valor que sera guardado no arquivo
/// \pre nenhuma
/// \post nenhuma
///
void insere_aux(FILE* registros, Cabecalho* indice, ArvoreB* r, RegistrosDat info)
{
	int pos = 0;

	//se não achar a posição desejada
	if(!buscaPos(r, info.palavra, &pos))
	{
		//se for folha
		if(eh_folha(r)) 
		{
			//move os dados
			adicionaDireita(r, pos, info, -1);
		}
		else 
		{
			//leio o filho da posição e recursivamente chamo a função
			ArvoreB* aux = leituraDoNoh(registros, r->filho[pos]); 
			insere_aux(registros, indice, aux, info);
			//se der overflow
			if(overflow(aux))
			{
				//quebra o nó e adiciona os novos nó a Arvore-B
				RegistrosDat m;
				ArvoreB* pai = split(aux, &m);
				adicionaDireita(r, pos, m, escreveArvore(registros, pai, indice));
				escreveArvore(registros, aux, indice);

				liberaNoh(pai);
			}
		}
	}

	//escreve a nova arvore gerada
	escreveArvore(registros, r, indice);
}

///
/// \brief insere, insere na Arvore-B o info, guardando no arquivo o resultado da inserção 
/// \param registros, arquivo aonde será buscado os dados e guardado os dados
/// \param info, valor que sera colocado na arvore e guardado no arquivo
/// \pre nenhuma
/// \post nenhuma
///
void insere(FILE* registros, char* palavra, int pos)
{
	//cria o registro para o arquivo
	RegistrosDat info;
	strcpy(info.palavra, palavra);
	info.registroPos = pos;

	//lê o cabeçalho
	Cabecalho *indice = leituraDoCabecalho(registros);
	//lê o nó pai da arvore
	ArvoreB* raiz = leituraDoNoh(registros, indice->raiz);
	ArvoreB* novo;

	//se não tem arvore
	if(!raiz) 
	{
		//inicializa a arvore
		raiz = inicializaArvore();
		//coloca a chave nova e atualiza o numero de chaves
		raiz->chave[0] = info;
		raiz->numChaves = 1;
		//a posição da raiz da arvore recebe a posição dela dentro do arquivo
		indice->raiz = escreveArvore(registros, raiz, indice);
	}
	else //se tem arvore
	{
		//chama função auxiliar
		insere_aux(registros, indice, raiz,info);

		//se der overflow
		if(overflow(raiz))
		{
			//pega a chave do meio e cria um novo nó
			RegistrosDat m;
			novo = split(raiz, &m);
			//inicializa o novo nó
			ArvoreB* novaRaiz = inicializaArvore();
			//a primeira chave recebe a chave do meio do nó com overflow
			novaRaiz->chave[0] = m;
			novaRaiz->filho[0] = indice->raiz;
			novaRaiz->numChaves = 1;
			//o filho dele recebe a posição da segunda parte da metade do nó splitado
			novaRaiz->filho[1] = escreveArvore(registros, novo, indice);

			//nova posição da raiz da arvore
			indice->raiz = escreveArvore(registros, novaRaiz, indice);

			liberaNoh(novo);	
			liberaNoh(novaRaiz);
		}
		//escreve a nova arvore
		escreveArvore(registros, raiz, indice);
	}
	//escreve o novo cabeçalho
	escreveCabecalho(registros, indice);

	liberaNoh(raiz);
	free(indice);
}

///
/// \brief printaArvore, busca os dados do arquivo e imprime na tela 
/// \param registros, arquivo que contem os dados do Arvore-B
/// \pre nenhuma
/// \post nenhuma
///
void printaArvore(FILE* registros)
{
	//lê o cabeçalho do arquivo da Arvore-B
	Cabecalho* indice = leituraDoCabecalho(registros);
	//procura a raiz
	ArvoreB* raiz = leituraDoNoh(registros, indice->raiz);
	//inicia a fila e insere a raiz
	Fila* fileira = start();
	enqueue(fileira, raiz);
	//pega o tamanho da fila
	int n;
	n = fileira->n;
	//enquanto não percorrer toda a fila
	while(n)
	{
		while(n)
		{
			//tira o inicio da fila
			No* noh = dequeue(fileira);
			//cria um novo nó que recebe o incio da fila
			ArvoreB* nova = (ArvoreB*)noh->info;

			//imprime as chaves do nó atual 
			printf("[");
			for(int i = 0; i < nova->numChaves-1; i++)
				printf(" %s,", nova->chave[i].palavra);
			printf(" %s ", nova->chave[nova->numChaves-1].palavra);
			printf("] ");

			//para cada filho desse nó
			int j;
			for(j = 0; j <= nova->numChaves; j++)
			{
				//se tem um filho, insere ele na fila
				if(nova->filho[j] != -1)
				{
					enqueue(fileira, leituraDoNoh(registros, nova->filho[j]));
				}
			}
			//diminui o tamanho da fila e libera os nós
			n--;
			free(noh);
			liberaNoh(nova);
		}
		//atualiza o contador
		n = fileira->n;
		printf("\n");
	}

	//limpa o nó e a fila
	liberaNoh(raiz);
	clean(fileira);
}

///
/// \brief eh_folha, verifica se o nó atual não tem filho
/// \param r, nó da Arvore-B
/// \return 1, se for folha, 0 se não for
/// \pre nenhuma
/// \post nenhuma
///
int eh_folha(ArvoreB* r) 
{
	return (r->filho[0] == -1);
}

///
/// \brief buscaPos, busca na Arvore passado por parametro se info pertence a ela
/// \param r, nó atual a ser buscado
/// \param info, valor a ser buscado na arvore
/// \param pos, variavel que recebe qual a posicao que se encontra o info
/// \return 1, se tiver na Arvore-B, 0, se n tiver
/// \pre nenhuma
/// \post nenhuma
///
int buscaPos(ArvoreB* r, char* info, int * pos) 
{
	//para cada chave
	for((*pos)=0; (*pos) < r->numChaves; (*pos)++)
	{
		//compara se é a chave desejada, se for, retorna verdadeiro
		if(!strcmp(info, r->chave[(*pos)].palavra))
			return 1;
		else if(strcmp(info, r->chave[(*pos)].palavra) < 0)// se a chave desejada for menor que as atuais, quebra a repetição
			break;
	}

	//retorna falso
	return 0;
}

///
/// \brief escreveCabecalho, escreve no arquivo passado as informações dos indices do Cabeçalho
/// \param registros, arquivo que tera o cabeçalho atualizado
/// \param indice, variavel que contém as informações que serão escritas no arquivo
/// \pre arquivo esteja aberto e guardado
/// \post nenhuma
///
void escreveCabecalho(FILE* registros, Cabecalho* indice)
{
	//se não tem cabeçalho
	if(!indice)
		return;
	//busca o topo
	fseek(registros, 0, SEEK_SET);
	//escreve o novo cabeçalho
	fwrite(indice, sizeof(Cabecalho), 1, registros);
}

///
/// \brief criaIndicesArq, inicializa uma variavel do tipo da estrutura Cabeçalho e escreve no arquivo binario 
/// \param binario, arquivo aonde terá seu cabeçalho escrito com os indices.
/// \pre nenhuma
/// \post nenhuma
///
void criaIndicesArq(FILE *binario)
{
	//cria um novo cabeçalho e insere no arquivo
	Cabecalho indice;

	indice.topo = 0;
	indice.raiz = -1;
	escreveCabecalho(binario, &indice);
}

///
/// \brief liberaNoh, desaloca o nó da Arvore-B da memoria
/// \param alvo, libera a memoria usada pelo nó
/// \pre nenhuma
/// \post a area ocupada pelo nó sera desocupada
///
void liberaNoh(ArvoreB* alvo)
{	
	//se tem nó libera-o
	if(alvo)
		free(alvo);
}

///
/// \brief inicializaArvore, cria uma variavel da estrutura ArvoreB e inicializa as variaveis dentro da estrutura. 
/// \return retorna uma variavel do tipo ArvoreB inicializa e alocada
/// \pre nenhuma
/// \post nenhuma
///
ArvoreB* inicializaArvore()
{
	//cria, aloca e inicializa os campos
	ArvoreB* new = (ArvoreB*)malloc(sizeof(ArvoreB));

	new->numChaves = 0;
	new->posicao = -1;
	
	int i;

	for(i = 0; i < ORDEM; i++)
	{
		new->chave[i].palavra[0] = '\0';
		new->chave[i].registroPos = -1;
		new->filho[i] = -1;
	}
	//retorna o novo nó
	return new;
}

///
/// \brief leituraDoCabecalho, lê os dados da posição 0 do arquivo e os guarda 
/// \param binario, arquivo a ser lido 
/// \return uma estrutura com os dados lidos do arquivo
/// \pre nenhuma
/// \post nenhuma
///
Cabecalho* leituraDoCabecalho(FILE* binario)
{
	//cria e aloca
    Cabecalho* cabeca = (Cabecalho*)malloc(sizeof(Cabecalho));
    //busca o topo do arquivo
    fseek(binario, 0, SEEK_SET);
    //lê o cabeçalho do arquivo
    fread(cabeca, sizeof(Cabecalho), 1, binario);
    //retorna o cabeçalho
    return cabeca;
}

///
/// \brief procuraDado, procura no arquivo o dado que contém a palavra passada
/// \param registro, arquivo que contém a Arvore-B
/// \param dados, arquivo que contém todos os dados inseridos
/// \param palavra, palavra a ser procurada dentro do arquivo de dados
/// \return o dado encontrado no arquivo
/// \pre nenhuma
/// \post nenhuma
/// 
Dado* procuraDado(FILE *registro, FILE *dados, char* palavra) 
{
	//lê o cabeçalho do arquivo da Arvore-B e o cabeçalho do arquivo de dados
    Cabecalho *indice = leituraDoCabecalho(registro);
    RegCabecalho *indiceDat = leCabecalhoReg(dados);
    //lê a raiz do arquivo da Arvore-B
    ArvoreB *raiz = leituraDoNoh(registro, indice->raiz);
    ArvoreB *aux = raiz;
    Dado *info = NULL;
    int pos, achou;
    //se existe um nó no topo
    if(raiz)
    {
    	//enquanto não achar e não for folha o nó
        while (!(achou = buscaPos(aux, palavra, &pos)) && !eh_folha(aux)) 
        {
        	//libera e procura o proximo nó
            liberaNoh(aux);
            aux = leituraDoNoh(registro, aux->filho[pos]);
        }
        //se achou o nó
        if (achou) 
        {
        	//lê o dado do indice que o nó guarda
            info = leDado(dados, aux->chave[pos].registroPos);
        }
        //desaloca o nó
        liberaNoh(aux);
    }

    free(indice);
    free(indiceDat);
    //retorna o dado encontrado
    return info;
}
