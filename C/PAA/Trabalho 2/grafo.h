#ifndef GRAFO_H
#define GRAFO_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// estrutura para guardar o nome de um rotulo ou de um vertice
typedef struct label {
    //variavel para o nome
    char nome[100];
} Label;

// estrutura principal para armazenar os dados do grafo lido pelo arquivo
typedef struct grafo{
    // adjacente seria a matriz de adjacencia, nVertices é o número de vertices que o grafo tem, EhRotulado indica se o vertice tem nome ou se só tem um número
    // pesos são os valores para o peso das arestas
    int **adjacente, nVertices, EhRotulado, **pesos;
    // rotulos são os nomes que estão na aresta, nomes são para quando o vertice tem um nome ao inves de um número
    Label **rotulos, *nomes;
    // orientado indica se o grafo é orientado ou não
    char orientado[4];
} Grafo;

/**
 * @brief  inicia uma variável do tipo Grafo, sendo alocando ele em um endereço de memória e guardando se o grafo é orientado ou não
 * @param  orientado[]: string que indica se o grafo é orientado ou não
 * @retval uma variavel do tipo Grafo* alocada e com o dado orientado preenchida
 */
Grafo* initGrafo(char orientado[]);

/**
 * @brief  inicia uma matriz do tipo Label
 * @param  v: tamanho que a matriz de Label vai ter
 * @retval retorna a matriz alocada mas sem ter algo atribuido
 */
Label** initLabels(int v);

/**
 * @brief  aloca uma matriz de VxV e atribui o valor de cada elemento com 0
 * @param  v: tamanho que a matriz terá, sendo VxV
 * @retval uma matriz alocada com todos os valores iguais a 0
 */
int ** init(int v);

#endif // GRAFO_H