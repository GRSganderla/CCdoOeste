#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "arquivo.h"

int main(){

    char nomeArq[200];

    printf("Entre com o arquivo de entrada: ");
    scanf("%s", nomeArq);

    FILE* in = fopen(nomeArq, "r+");

    if(in == NULL){
        printf("Entre com um arquivo valido!\n");
    }

    printf("Entre com o arquivo de saida: ");
    scanf("%s", nomeArq);

    FILE* out = fopen(nomeArq, "w+");

    leArquivo(in, out);

    return 0;
}