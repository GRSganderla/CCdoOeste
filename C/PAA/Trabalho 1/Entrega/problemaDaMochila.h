#include<stdio.h>
#include<stdlib.h>
#define MAX(X, Y) (((X) > (Y)) ? (1) : (0))

//estrutura para os itens
typedef struct objeto
{
    //peso e valor do item
    int w, c;
}Objeto;

///
/// \brief prog_dinamica, função para o problema da mochila com técnica de programação dinâmica
/// \param ob, vetor de itens
/// \param W, capacidade maxima da mochila
/// \param n, quantidade de itens
/// \return o maior valor possivel conseguido colocando os itens que juntos não tem peso maior que a capacidade maxima da mochila
///
int prog_dinamica(Objeto *ob, int W, int n);
///
/// \brief desaloca, função que desaloca cada uma das variaveis globais dinamicas
/// \param n, quantidade de itens
///
void desaloca(int n);
///
/// \brief aloca, função que aloca cada uma das variaveis globais
/// \param n, quantidade de itens
/// \param W, capacidade da mochila
///
void aloca(int n, int W);
///
/// \brief mochila, função principal do problema da mochila, prepara os dados e chama o metódo selecionado
///
void mochila(void);
///
/// \brief atualiza, função que o valor final dos itens na mochila, o peso total desses itens e o vetor solução final
/// \param ob, vetor com os itens
/// \param n, quantidade de itens
/// \param temp, vetor de solução com os valores binarios de se o item está ou não na mochila
///
void atualiza(Objeto *ob, int n, int *temp);
///
/// \brief pesos, função que calcula o peso total do objetos dentro da mochila
/// \param n, quantidade de itens
/// \param temp, vetor de solução binario, diz se o item está totalmente ou não na mochila
/// \param ob, vetor com os itens e seus valores e pesos
/// \return o peso total dos itens na mochila
///
int pesos(int n, int *temp, Objeto* ob, int W);
///
/// \brief backtracking, função principal do problema da mochila com backtracking
/// \param ob, vetor de itens
/// \param W, capacidade total da mochila
/// \param i, indice do intervalo que está verificando, começa vendo o ultimo, depois o ultimo com o penultimo, após isso verifica o ultimo com o penultimo e o antepenultimo...
/// \param n, quantidade de itens
/// \param tempX, vetor solução temporario atual
///
void backtracking(Objeto *ob, int W, int i, int n, int *tempX);
