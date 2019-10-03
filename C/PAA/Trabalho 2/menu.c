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

char *linhaDeComandoDot(char dot[]){

    char *linha =  (char*)malloc(sizeof(char)*300), nome[200];

    printf("Digite o nome do arquivo para ser gerado o .png (sem o .png): ");
    scanf("%s%*c", nome);

    sprintf(linha, "/bin/dot -Tpng /home/sganchine/Git/CCdoOeste/C/PAA/Trabalho 2/%s -o /home/sganchine/%s.png", dot, nome);
    printf("%s", linha);

    return linha;
}

void menu(Grafo* g, char nomeArq[]){

    char dotGerado[300], *command;
    int opcao;

    do{
        
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

        if(opcao == 0) break;

        if(nomeArq == NULL){
        
            printf("Entre com o nome do arquivo .dot a ser gerado: ");
            scanf("%s%*c", dotGerado);
        }
        else{
            
            if(opcao > 0){
                strcat(dotGerado, algoritmosDot[opcao-1]);
            }
        }

        int vertice = vertice_origem(g);
        int **res;

        FILE* f = fopen(dotGerado, "w+");

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
            command = linhaDeComandoDot(dotGerado);
            strcat(command, " > log.txt");
            system(command);
        }
        
    }while(opcao != 0);
}