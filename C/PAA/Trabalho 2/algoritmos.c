#include "algoritmos.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void visita_buscaProf(int vertice, Profundidade* busca, int n, int **ordem){

    busca[vertice].cor = 'C';
    timestamp++;
    busca[vertice].d = timestamp;

    for(int i = 0; i < n; i++){

        if(busca[vertice].adj[i] == 1 && busca[i].cor == 'B'){

            ordem[vertice][i] = 1;
            busca[i].pred = vertice;
            visita_buscaProf(i, busca, n, ordem);
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
    int **ordem = init(grf->nVertices), i = 0;

    if(busca[inicial].cor == 'B'){

        visita_buscaProf(inicial, busca, grf->nVertices, ordem);

    }

    for(int i = 0; i < grf->nVertices; i++){

        if(busca[i].cor == 'B'){

            visita_buscaProf(i, busca, grf->nVertices, ordem);

        }
    }

    return ordem;
}

int vertice_origem(Grafo* g){

    int vertice;
    system("clear");


    printf("Vertices={");
    for(int i = 0; i < g->nVertices; i++){

        printf(" %d", i);
        if(g->EhRotulado){
            printf(": %s", g->nomes[i]);
        }

        (i < g->nVertices-1)? printf(","): printf("}\n");
    }

    do {
        printf("Entre com o vertice de origem: ");
        scanf("%d%*c", &vertice);
    }while(vertice < 0 && vertice > g->nVertices);

    return vertice;
}

int** buscaEmLargura(Grafo* g, int origem){

    Fila* q = start();
    int u, i, j;
    int **res = init(g->nVertices);

    Largura* l = (Largura*)malloc(sizeof(Largura)*g->nVertices);

    for(i = 0; i < g->nVertices; i++){

        if(i != origem){

            l[i].cor = 'B';
            l[i].d = 999999;
            l[i].pred = -1;

            l[i].adj = (int*)malloc(sizeof(int)*g->nVertices);

            for(j = 0; j < g->nVertices; j++){
                l[i].adj[j] = (g->adjacente[i][j] == 1);
            }
        }
    }

    l[origem].cor = 'C';
    l[origem].pred = -1;
    l[origem].d = 0;
    l[origem].adj = (int*)malloc(sizeof(int)*g->nVertices);

    for(j = 0; j < g->nVertices; j++){
        l[origem].adj[j] = (g->adjacente[origem][j] == 1);
    }
    enqueue(q, origem);

    while(!empty(q)){

        imprime(q);
        u = dequeue(q);

        if(u == -1) return NULL;

        for(i = 0; i < g->nVertices; i++){

            if(l[u].adj[i] && l[i].cor == 'B'){
                
                res[u][i] = 1;
                l[i].cor = 'C';
                l[i].d = l[u].d + 1;
                l[i].pred = u;
                enqueue(q, i);
            }
        }

        l[u].cor = 'P';
    }

    return res;
}