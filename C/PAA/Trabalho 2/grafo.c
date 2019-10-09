#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "grafo.h"

/**
 * @brief  aloca uma matriz de VxV e atribui o valor de cada elemento com 0
 * @param  v: tamanho que a matriz terá, sendo VxV
 * @retval uma matriz alocada com todos os valores iguais a 0
 */
int** init(int v){

    // cria e aloca as linhas
    int** alvo = (int**)malloc(sizeof(int*)*v);

    // para cada linha
    for(int i = 0; i < v; i++){

        // aloca as colunas
        alvo[i] = (int*)malloc(sizeof(int)*v);

        // para cada coluna atribui o valor zero
        for(int j = 0; j < v; j++){
            alvo[i][j] = 0;
        }
    }

    return alvo;
}

/**
 * @brief  inicia uma matriz do tipo Label
 * @param  v: tamanho que a matriz de Label vai ter
 * @retval retorna a matriz alocada mas sem ter algo atribuido
 */
Label** initLabels(int v){

    // cria e aloca as linhas da matriz
    Label** lab = (Label**)malloc(sizeof(Label*)*v);

    // para cada linha
    for(int i = 0; i < v; i++){

        // aloca as colunas
        lab[i] = (Label*)malloc(sizeof(Label)*v);
    }

    return lab;
}

/**
 * @brief  inicia uma variável do tipo Grafo, sendo alocando ele em um endereço de memória e guardando se o grafo é orientado ou não
 * @param  orientado[]: string que indica se o grafo é orientado ou não
 * @retval uma variavel do tipo Grafo* alocada e com o dado orientado preenchida
 */
Grafo* initGrafo(char orientado[]){

    Grafo* novo = (Grafo*)malloc(sizeof(Grafo));

    // guarda o valor que indica se é orientado ou não
    strcpy(novo->orientado, orientado);

    return novo;
}