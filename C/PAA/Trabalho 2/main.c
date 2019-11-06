#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "grafo.h"
#include "arquivo.h"
#include "menu.h"

int main(){

    // arquivos de entrada e saida
    FILE* inFile, *outFile;
    // variaveis para o nome do Arq
    char inArq[200], dot[200], outArq[200], aux[200];
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
                // le o nome do arquivo e cria a string com .txt no final
                printf("Entre com o arquivo de entrada (sem .txt): ");
                scanf("%s%*c", inArq);
                strcat(inArq, ".txt");

                // abre o arquivo para leitura
                inFile = fopen(inArq, "r+");

                // se o arquivo não existe ou está vazio
                if(inFile == NULL){

                    printf("Arquivo Invalido!");
                    getchar();
                    break;
                }

                // chama a função de leitura e fecha o arquivo após isso
                g = leArquivo(inFile);
                fclose(inFile);
                break;
            case 2:
                // le o nome do arquivo de saida e cria uma string com .dot no final
                printf("Entre com o arquivo de saida (sem .dot): ");
                scanf("%s%*c", outArq);
                sprintf(dot, "%s.dot", outArq);

                // abre para a leitura do arquivo
                outFile = fopen(dot, "w+");

                // se o grafo carregado existe escreve no arquivo os dados e fecha o arquivo
                if(g != NULL){

                    fazArquivoDot(g, outFile);
                }
                fclose(outFile);
                break;
            case 3:
                //chama a função de menu dos algoritmos
                menu(g, outArq);
                break;
            case 0:
                break;
        }
    }while(opcao != 0);

    return 0;
}