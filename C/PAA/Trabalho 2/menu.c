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
    "BellmanFord.dot",
    "Kruskal.dot",
    "Prim.dot",
    "FordFulkerson.dot",
};

char *linhaDeComandoDot(char dot[]){

    char *linha =  (char*)malloc(sizeof(char)*300), nome[200];

    printf("Digite o nome do arquivo para ser gerado o .png (sem o .png): ");
    scanf("%s%*c", nome);

    sprintf(linha, "/bin/dot -Tpng /home/sganchine/Git/CCdoOeste/C/PAA/Trabalho\\ 2/%s -o /home/sganchine/%s.png", dot, nome);
    printf("%s", linha);

    return linha;
}

void printMat(Grafo* g){

    for(int i = 0; i < g->nVertices; i++){
        for(int j = 0; j < g->nVertices; j++){
            printf("\t[%d][%d] = %d\n", i, j, g->pesos[i][j]);
        }
    }
}

void menu(Grafo* g, char nomeArq[]){

    char dotGerado[300], *command;
    int opcao, feito;

    do{
        feito = 0;
        strcpy(dotGerado, nomeArq);
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

        if(opcao == 0){
            break;
        }   
        else if(opcao > 6){
            continue;
        }

        if(nomeArq[0] == '\0'){
        
            printf("Entre com o nome do arquivo .dot a ser gerado: ");
            scanf("%s%*c", dotGerado);
        }
        else{
            
            strcat(dotGerado, algoritmosDot[opcao-1]);
        }

        int vertice = vertice_origem(g);
        int **res = init(g->nVertices);

        FILE* f = fopen(dotGerado, "w+");

        switch (opcao)
        {
            case 1:
        
                buscaEmProfundidade(g, vertice, res);
                fazArquivoBusca(g,f,res);
                free(res);
                break;
            case 2:

                feito = buscaEmLargura(g, vertice, res);
                if(feito) fazArquivoBusca(g, f, res);
                free(res);
                break;
            case 3:
                feito = BellmanFordAlg(g, vertice, res);
                if(feito) fazArquivoFord(g, f, res);
                free(res);
                break;
            case 0:
                break;
        }

        getchar();
        
    }while(opcao != 0);
}