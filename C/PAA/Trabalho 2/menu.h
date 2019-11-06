#include "grafo.h"
#include "algoritmos.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief  função que le o número do vertice de fonte e ralo que o usuário quer que seja feito o algoritmo
 * @param  *fonte: variável responsavel por guardar o valor do vertice de fonte que será lido
 * @param  *ralo: variável responsavel por guardar o valor do vertice de ralo que será lido
 * @param  g: grafo carregado do arquivo dessa instância de execução
 * @retval None
 */
void fonte_ralo(int *fonte, int *ralo, Grafo* g);

/**
 * @brief  função que lê o vertice de origem que o usuário deseja usar para os algoritmos
 * @param  g: grafo carregado do arquivo dessa instância de execução
 * @retval o vertice lido
 */
int vertice_origem(Grafo* g);

/**
 * @brief  função de apresentar um menu iterativo onde o usuário escolherá os algoritmos a serem feito sobre o grafo guardado
 * @param  g: grafo carregado que será usado nos algoritmos
 * @param  nomeArq[]: nome do arquivo de saida padrão a ser usado para gerar os .dots dos algoritmos a serem feitos
 * @retval None
 */
void menu(Grafo* g, char nomeArq[]);