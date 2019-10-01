#include "algoritmos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int timestamp;

void visita_buscaProf(int vertice, Profundidade* busca, int n, int **ordem, int index){

    busca[vertice].cor = 'C';
    timestamp++;
    busca[vertice].d = timestamp;

    for(int i = 0; i < n; i++){

        if(busca[vertice].adj[i] == 1 && busca[i].cor == 'B'){

            ordem[index][i] = 1;
            busca[i].pred = vertice;
            visita_buscaProf(i, busca, n, ordem, i);
        }
    }

    busca[vertice].cor = 'P';
    timestamp++;
    busca[vertice].f = timestamp; 
}

int** buscaEmProfundidade(Grafo* grf, int inicial){

    Profundidade* busca = (Profundidade*)malloc(sizeof(Profundidade)*grf->nVertices);

    for(int i = 0; i < grf->nVertices; i++){
        
        busca[i].cor = 'B';
        busca[i].pred = -1;
        busca[i].adj = (int*)malloc(sizeof(int)*grf->nVertices);

        for(int j = 0; j < grf->nVertices; j++){

            busca[i].adj[j] = (grf->adjacente[i][j] == 1);
        }
    }

    timestamp = 0;
    int atual = inicial, **ordem = init(grf->nVertices), i = 0;

    while(atual < grf->nVertices){

        if(busca[atual].cor == 'B'){
            
            visita_buscaProf(atual, busca, grf->nVertices, ordem, i);
            if(atual == inicial) atual = 0;
        }
        else{

            atual++;
        }
    }

    return ordem;
}