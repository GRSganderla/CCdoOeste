#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "grafo.h"

int** init(int v){

    int** alvo = (int**)malloc(sizeof(int*)*v);

    for(int i = 0; i < v; i++){

        alvo[i] = (int*)malloc(sizeof(int)*v);

        for(int j = 0; j < v; j++){
            alvo[i][j] = 0;
        }
    }

    return alvo;
}

Label** initLabels(int v){

    Label** lab = (Label**)malloc(sizeof(Label*)*v);

    for(int i = 0; i < v; i++){

        lab[i] = (Label*)malloc(sizeof(Label)*v);

        for(int j = 0; j < v; j++){
            lab[i][j].nome = (char *)malloc(sizeof(char)*v);
        }
    }

    return lab;
}

Grafo* initGrafo(int vertices, char orientado[], char **nomes, int EhRotulado){

    Grafo* novo = (Grafo*)malloc(sizeof(Grafo));

    novo->nVertices = vertices;
    strcpy(novo->orientado, orientado);
    
    novo->nomes = (Label*)malloc(sizeof(Label)*novo->nVertices);

    for(int i = 0; i < novo->nVertices; i++) novo->nomes[i].nome = nomes[i];

    novo->EhRotulado = EhRotulado;
    
    novo->adjacente = init(novo->nVertices);
    novo->pesos = init(novo->nVertices);
    novo->rotulos = initLabels(novo->nVertices);

    return novo;
}