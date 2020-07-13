#include<stdio.h>
#include<stdlib.h>

//estrutura para um nó da fila
typedef struct no
{
	//ponteiro de void para guardar os dados
	void* info;
	//ponteiro para o proximo nó e outro 
	struct no* prox, *ant;
}No;

//estrutura para a fila
typedef struct fila
{
	//tamanho da fila
	int n;
	//inicio da fila
	struct no* inicio;
	//final da fila
	struct no* final;
}Fila;

///
/// \brief start, cria e inicializa os campos de uma estrutura fila
/// \return uma variavel do tipo Fila inicializada
/// \pre nenhuma
/// \post nenhuma
///
Fila* start();

///
/// \brief empty, verifica se a fila é vazia
/// \param f, fila que será verificada se é vazia
/// \return 1 se for vazia e 0 se não
/// \pre nenhuma
/// \post nenhuma
///
int empty(Fila* f);

///
/// \brief criaNo, cria um nó do tipo de estrutura nó usando o dado passado
/// \param dados, informação a ser inserida
/// \return uma variavel do tipo No*
/// \pre nenhuma
/// \post nenhuma
///
No* criaNo(void* dados);

///
/// \brief clean, limpa a Fila usada no programa, desalocando-a 
/// \param fileira, Fila usada no programa ser desalocada
/// \return uma Fila desalocada
/// \pre nenhuma
/// \post nenhuma
///
Fila* clean(Fila* fileira);

///
/// \brief enqueue, enfileira um nó na fila, ou seja, insere um nó na fila
/// \param f, fila a ter nó inserido
/// \param dados, dado a ser inserido em um nó a ser inserido na fila
/// \pre nenhuma
/// \post nenhuma
///
void enqueue(Fila* f, void* dados);

///
/// \brief dequeue, remove o primeiro nó da fila, retornando o nó
/// \param f, fila a ter primeiro nó da fila
/// \return o nó removida da fila
/// \pre nenhuma
/// \post nenhuma
///
No* dequeue(Fila* f);