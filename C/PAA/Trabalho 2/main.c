#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "arquivo.h"

int main(){

    char nomeArq[200], dot[200];

    system("clear");

    printf("Entre com o arquivo de entrada (sem .txt): ");
    scanf("%s%*c", nomeArq);
    strcat(nomeArq, ".txt");

    FILE* in = fopen(nomeArq, "r+");

    while(in == NULL){

        printf("Entre com um arquivo valido!\n");
        printf("Entre com o arquivo de entrada Valido (sem .txt): ");
        scanf("%s%*c", nomeArq);
        strcat(nomeArq, ".txt\n");
        in = fopen(nomeArq, "r+");
    }

    leArquivo(in);

    return 0;
}