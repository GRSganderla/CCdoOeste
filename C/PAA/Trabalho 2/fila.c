#include<stdio.h>
#include<stdlib.h>
#include "fila.h"

/**
 * @brief  cria e inicializa com nulo uma Fila*
 * @retval uma variavel do tipo Fila* alocada
 */
Fila* start()
{
	//aloca a fila
	Fila* aux = (Fila*)malloc(sizeof(Fila));

	// inicializa com 0 ou nulo os campos
	aux->final = NULL;
	aux->inicio = NULL;
	aux->n = 0;

	return aux;
}

/**
 * @brief  verifica se a fila está vazia ou não
 * @param  f: fila a ser verificada
 * @retval 1 se estiver vazia e 0 se não estiver
 */
int empty(Fila* f)
{
	return (f->inicio) ? 0: 1;
}

/**
 * @brief  cria uma variavel do tipo No* e aloca os campos dela
 * @param  dados: valor a ser guardado dentro do No*
 * @retval uma variavel do tipo No* alocada e com o campo info atribuido
 */
No* criaNo(int dados)
{
	// aloca o Nó
	No* aux = (No*)malloc(sizeof(No));

	// atribui os campos
	aux->info = dados;
	aux->prox = NULL;
	aux->ant = NULL;

	return aux;
}

/**
 * @brief  insere na cauda da fila um novo nó contendo o dado a ser inserido
 * @param  f: fila a ter um novo nó na cauda
 * @param  dados: dado a ser inserido no nó novo da fila
 * @retval None
 */
void enqueue(Fila* f, int dados)
{
	// se não existe um fila, retorna
	if(!f)return;

	// cria o Nó e atribui o dado dentro dele
	No* auxf = criaNo(dados);

	// se a fila está vazia, então insere na cabeça e na cauda o novo nó
	if(!f->inicio)
		f->inicio = f->final = auxf;
	else{
		// se não insere no final e atualiza o ponteiro pro final
		auxf->ant = f->final;
		f->final->prox = auxf;
		f->final = auxf;
	}
	// incrementa o tamanho da fila
	f->n++;
}

/**
 * @brief  retira da fila o primeiro nó, ou seja, remove o nó da cabeca
 * @param  f: fila a ter o nó da cabeça removido
 * @retval o valor do campo info do nó removido
 */
int dequeue(Fila* f)
{
	// se não tem nada na fila, então n tem o que remover
	if(empty(f)) return -1;
	// se a fila não tiver alocada, retorna
 	if(f->inicio == NULL) return -1;

	// pega o inicio da fila
	No* aux = f->inicio;
	// atualiza ele para o proximo nó
	f->inicio = aux->prox;
	
	// se tiver ainda mais um nó na fila
	if(f->inicio)
	{
		// atualiza o anterior da nova cabeça
		f->inicio->ant = NULL;
	}
	else{
		// se não houver mais nó na fila, limpa o ponteiro da cauda
		f->final = NULL;
	}

	// diminui o tamanho da fila
	f->n--;

	// retorna o inteiro que estava na cabeça
	return aux->info;
}