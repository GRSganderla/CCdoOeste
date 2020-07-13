#include<stdio.h>
#include<stdlib.h>
#include "fila.h"

///
/// \brief start, cria e inicializa os campos de uma estrutura fila
/// \return uma variavel do tipo Fila inicializada
/// \pre nenhuma
/// \post nenhuma
///
Fila* start()
{
	//cria e aloca, inicializando todo os campos
	Fila* aux = (Fila*)malloc(sizeof(Fila));

	aux->final = NULL;
	aux->inicio = NULL;
	aux->n = 0;
	//retorna a nova fila
	return aux;
}

///
/// \brief empty, verifica se a fila é vazia
/// \param f, fila que será verificada se é vazia
/// \return 1 se for vazia e 0 se não
/// \pre nenhuma
/// \post nenhuma
///
int empty(Fila* f)
{
	return (f->inicio) ? 0: 1;
}

///
/// \brief criaNo, cria um nó do tipo de estrutura nó usando o dado passado
/// \param dados, informação a ser inserida
/// \return uma variavel do tipo No*
/// \pre nenhuma
/// \post nenhuma
///
No* criaNo(void* dados)
{
	No* aux = (No*)malloc(sizeof(No));

	aux->info = dados;
	aux->prox = NULL;
	aux->ant = NULL;

	return aux;
}

///
/// \brief clean, limpa a Fila usada no programa, desalocando-a 
/// \param fileira, Fila usada no programa ser desalocada
/// \return uma Fila desalocada
/// \pre nenhuma
/// \post nenhuma
///
Fila* clean(Fila* fileira)
{
	//se não é vazia a fila
	if(!empty(fileira))
	{
		No* aux;
		//enquanto tiver um inicio
		while(fileira->inicio)
		{
			//pega o nó do inicio e atualiza o inicio da fila
			aux = fileira->inicio;
			fileira->inicio = fileira->inicio->prox;
			//desaloca o nó
			free(aux);
		}
		//desaloca a fila
		free(fileira);
	}
}

///
/// \brief enqueue, enfileira um nó na fila, ou seja, insere um nó na fila
/// \param f, fila a ter nó inserido
/// \param dados, dado a ser inserido em um nó a ser inserido na fila
/// \pre nenhuma
/// \post nenhuma
///
void enqueue(Fila* f, void* dados)
{
	//se a fila não foi alocada
	if(!f)return;

	//cria um novo nó
	No* auxf = criaNo(dados);

	//se é vazio o inicio o final e inicio vira o novo nó
	if(!f->inicio)
		f->inicio = f->final = auxf;
	else{//se não tiver vazia
		//o anterior do nó aponta pro final e o proximo do final é o novo nó e o final é o novo nó
		auxf->ant = f->final;
		f->final->prox = auxf;
		f->final = auxf;
	}
	//tamanho cresçe
	f->n++;
}

///
/// \brief dequeue, remove o primeiro nó da fila, retornando o nó
/// \param f, fila a ter primeiro nó da fila
/// \return o nó removida da fila
/// \pre nenhuma
/// \post nenhuma
///
No *dequeue(Fila* f)
{
	//se é vazia, não há nada a ser feito
	if(empty(f)) return NULL;
	//se não tem inicio, volta
	if(f->inicio == NULL) return NULL;

	//recebe o inicio e atualiza o inicio da fila
	No* aux = f->inicio;
	f->inicio = aux->prox;
	
	//se ainda exite o inicio
	if(f->inicio)
	{
		//o anterior do inicio não existe mais
		f->inicio->ant = NULL;
	}
	else{//se for vazia, limpa o final
		f->final = NULL;
	}

	//diminui o tamanho
	f->n--;

	//retorna o nó do inicio
	return aux;
}