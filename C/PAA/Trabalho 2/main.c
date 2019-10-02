#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "grafo.h"
#include "arquivo.h"
#include "algoritmos.h"

int main(){

    FILE* in, *out;
    char nomeArq[200], dot[200];
    int opcao;
    Grafo* g = NULL;

    do{
        system("clear");

        printf("GRAFO SIMULATOR\n");
        printf("---------------------------\n");
        printf("1 - Carregar Grafo\n");
        printf("2 - Desenhar Grafo\n");
        printf("3 - Algoritmos com o Grafo\n");
        printf("0 - Sair\n");
        printf("---------------------------\n");
        printf("Opcao: ");
        scanf("%d%*c", &opcao);

        switch(opcao){

            case 1:

                printf("Entre com o arquivo de entrada (sem .txt): ");
                scanf("%s%*c", nomeArq);
                strcat(nomeArq, ".txt");

                in = fopen(nomeArq, "r+");

                while(in == NULL){

                    printf("Arquivo invalido!\n");
                    printf("Entre com o arquivo de entrada Valido (sem .txt): ");
                    scanf("%s%*c", nomeArq);
                    strcat(nomeArq, ".txt\n");
                    in = fopen(nomeArq, "r+");
                }

                g = leArquivo(in);
                break;
            case 2:

                printf("Entre com o arquivo de saida (sem .dot): ");
                scanf("%s%*c", nomeArq);
                strcpy(dot, nomeArq);

                strcat(dot, ".dot");

                out = fopen(dot, "w+");

                //if(g != NULL){

                fazArquivoDot(g, out);
                //}

                break;
            case 3:
                menu(g, nomeArq);
                break;
            case 0:
                break;
        }
    }while(opcao != 0);

    return 0;
}