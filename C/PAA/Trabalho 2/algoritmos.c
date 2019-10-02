#include "algoritmos.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int timestamp;

const char *algoritmos[] = {
    "Busca em Profundidade", 
    "Busca em Largura",
    "Bellman-Ford",
    "Kruskal",
    "Prim",
    "Algoritmo de Ford-Fulkerson",
};

const char *algoritmosDot[] = {
    "BuscaProfundidade.dot", 
    "BuscaLargura.dot",
    "Bellman-Ford.dot",
    "Kruskal.dot",
    "Prim.dot",
    "FordFulkerson.dot",
};

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

void beginBuscaProf(Grafo* g, char nomeArq[]){

    int vertice;
    int **res;

    FILE* f = fopen(nomeArq, "w+");

    system("clear");
    printf("Busca em Profundidade\n");

    printf("Vertices={");
    for(int i = 0; i < g->nVertices; i++){

        printf(" %d", i);
        if(g->EhRotulado){
            printf(": %s", g->nomes[i]);
        }

        (i < g->nVertices-1)? printf(","): printf("}\n");
    }

    printf("Entre com o vertice de origem: ");
    scanf("%d%*c", &vertice);

    res = buscaEmProfundidade(g, vertice);
    
    fazArquivoAlg(g, f, res);
}

void menu(Grafo* g, char nomeArq[]){

    int opcao;

    do{

        system("clear");
        printf("Algoritmos com Grafos\n");

        printf("------------------------------\n");

        for(int i = 0; i < 6; i++){
            printf("%d - %s\n", i+1, algoritmos[i]);
        } 
        printf("0 - Sair\n");
        printf("------------------------------\n");
        printf("Opcao: ");

        scanf("%d%*c", &opcao);

        if(nomeArq == NULL){
        
            printf("Entre com o nome do arquivo .dot a ser gerado: ");
            scanf("%s%*c", nomeArq);
        }
        else{
            
            if(opcao > 0){
                char dot[200];
                strcat(nomeArq, algoritmosDot[opcao-1]);
            }
        }

        switch (opcao)
        {
            case 1:
        
                beginBuscaProf(g, nomeArq);
                
                break;
            case 2:

                //beginBuscaLar(g, nomeArq);
                break;
            case 0:
                break;
        }
        
        getchar();

    }while(opcao != 0);
}