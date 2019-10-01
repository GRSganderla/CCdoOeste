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
    }

    return lab;
}

Grafo* initGrafo(char orientado[]){

    Grafo* novo = (Grafo*)malloc(sizeof(Grafo));

    strcpy(novo->orientado, orientado);

    return novo;
}