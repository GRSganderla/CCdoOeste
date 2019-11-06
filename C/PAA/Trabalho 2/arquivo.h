#ifndef ARQUIVO_H
#define ARQUIVO_H

#include<stdio.h>
#include<stdlib.h>
#include "grafo.h"

#define LINHA_ORIENTADO 1;
#define LINHA_ROTULO_VERTICES 2;
#define LINHA_N_VERTICES 3;
#define LINHA_ARESTAS 4;

/**
 * @brief  função que insere no arquivo .dot a sintaxe para ser usada no comando dot para gerar o grafo resultante dos algoritmos de profundidade e largura
 * @param  g: grafo carregado que terá os dados guardados nesse arquivo .dot
 * @param  out: arquivo .dot a ter a sintaxe inserida
 * @param  res: matriz que contem o resultado do algoritmo de profundidade ou largura
 * @retval None
 */
void fazArquivoBusca(Grafo* g, FILE* out, int** res);

/**
 * @brief  função que insere no arquivo .dot a sintaxe para se criar um grafo com o resultado sendo do algoritmo de Bellman-Ford, Kruskal, Prim ou Ford-Fulkerson
 * @param  grf: grafo carregado a ter dados inserido no arquivo de saida
 * @param  outFile: arquivo .dot que será escrito os dados
 * @param  res: matriz de resultado do algoritmo escolhido
 * @param  fluxo: variavel que pode guardar o valor do fluxo total ou ser 0
 * @param  ralo: variavel que guarda o vertice ralo do grafo, sendo usado quando for o algoritmo de Fulkerson
 * @param  ehFluxo: variavel que diz se o algoritmo que foi executado antes era o de Fulkerson ou não
 * @retval None
 */
void fazArquivoFord(Grafo* grf, FILE* outFile, int** res, int fluxo, int ralo, int ehFluxo);

/**
 * @brief  função que insere no arquivo .dot a sintaxe para criar o grafo
 * @param  grf: grafo a ser inserido no arquivo
 * @param  out: arquivo a ser escrito os dados
 * @retval None
 */
void fazArquivoDot(Grafo* grf, FILE* out);

/**
 * @brief  função que le da linha do arquivo a aresta e guarda os dados do vertice u, v e o peso no grafo
 * @param  linha[]: linha do arquivo lida que contém uma aresta
 * @param  *grf: grafo a ter dados inseridos
 * @retval None
 */
void linha_arestas(char linha[], Grafo *grf);

/**
 * @brief  função que le a linha e pega o nome dos vertices e guarda na estrutura Grafo*
 * @param  linha[]: linha lida do arquivo
 * @param  grf: grafo a ter os dados inseridos
 * @retval None
 */
void linha_rotulo_vertices(char linha[], Grafo* grf);

/**
 * @brief  função que o numero de vertices e guarda na estrutura Grafo*
 * @param  linha[]: linha lida do arquivo
 * @param  grf: grafo a ter o número de vertices atualizado
 * @retval None
 */
void linha_n_vertices(char linha[], Grafo* grf);

/**
 * @brief  função que verifica qual o tipo de orientação do arquivo e aloca a estrutura Grafo* e guarda o dado orientado
 * @param  linha[]: linha do arquivo lida
 * @retval uma variavel do tipo Grafo* alocada e com o campo orientado preenchido
 */
Grafo* linha_orientado(char linha[]);

/**
 * @brief  função que chama os metodos de alocação dos campos da variavel do tipo Grafo*
 * @param  grf: grafo a ter os campos alocados
 * @retval None
 */
void alocaCampos(Grafo* grf);

/**
 * @brief  função que verifica qual o tipo da linha do arquivo está sendo lida, e retorna o tipo dessa linha
 * @param  linha[]: linha lida do arquivo a ter o seu tipo determinada
 * @retval número que indica qual o tipo da linha
 */
int qualLinha(char linha[]);

/**
 * @brief  função que determina quantos nomes tem dentro de uma string 
 * @param  *nome: string que contem varios nomes, separados por virgula
 * @retval um número que será o quanto de nomes há na string
 */
int countVirgula(char *nome);

/**
 * @brief  função que pega o arquivo aberto e lê as linhas dele e armazena em um grafo
 * @param  in: arquivo a ser lido
 * @retval uma variavel do tipo Grafo* contendo os dados do grafo passado por arquivo
 */
Grafo* leArquivo(FILE* in);

#endif // ARQUIVO_H