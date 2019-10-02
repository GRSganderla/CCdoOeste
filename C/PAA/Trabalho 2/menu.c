#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

char *algoritmos[] = {
    "Busca em Profundidade", 
    "Busca em Largura",
    "Bellman-Ford",
    "Kruskal",
    "Prim",
    "Algoritmo de Ford-Fulkerson",
};

char *algoritmosDot[] = {
    "BuscaProfundidade.dot", 
    "BuscaLargura.dot",
    "Bellman-Ford.dot",
    "Kruskal.dot",
    "Prim.dot",
    "FordFulkerson.dot",
};

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

        if(opcao == 0) break;

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

        int vertice = vertice_origem(g);
        int **res;

        FILE* f = fopen(nomeArq, "w+");

        switch (opcao)
        {
            case 1:
        
                res = buscaEmProfundidade(g, vertice);
                break;
            case 2:

                res = buscaEmLargura(g, vertice);
                break;
            case 0:
                break;
        }

        if(res != NULL){

            fazArquivoAlg(g, f, res);
        }
        
    }while(opcao != 0);
}