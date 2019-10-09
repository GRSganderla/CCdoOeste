#include<stdio.h>
#include<stdlib.h>

// estrutura para o nó da fila
typedef struct no
{
	// info guarda o valor
	int info;
	// prox aponta para o proximo nó, ant aponta para o nó anterior
	struct no* prox, *ant;
}No;

// estrutura principal para a Fila
typedef struct fila
{
	// tamanho da fila
	int n;
	// cabeca da fila
	struct no* inicio;
	// cauda da fila
	struct no* final;
}Fila;

/**
 * @brief  cria e inicializa com nulo uma Fila*
 * @retval uma variavel do tipo Fila* alocada
 */
Fila* start();

/**
 * @brief  verifica se a fila está vazia ou não
 * @param  f: fila a ser verificada
 * @retval 1 se estiver vazia e 0 se não estiver
 */
int empty(Fila* f);

/**
 * @brief  cria uma variavel do tipo No* e aloca os campos dela
 * @param  dados: valor a ser guardado dentro do No*
 * @retval uma variavel do tipo No* alocada e com o campo info atribuido
 */
No* criaNo(int dados);

/**
 * @brief  insere na cauda da fila um novo nó contendo o dado a ser inserido
 * @param  f: fila a ter um novo nó na cauda
 * @param  dados: dado a ser inserido no nó novo da fila
 * @retval None
 */
void enqueue(Fila* f, int dados);

/**
 * @brief  retira da fila o primeiro nó, ou seja, remove o nó da cabeca
 * @param  f: fila a ter o nó da cabeça removido
 * @retval o valor do campo info do nó removido
 */
int dequeue(Fila* f);