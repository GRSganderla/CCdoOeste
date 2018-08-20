#include "operacoes.h"
#include "tempo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXINT 1000000

ArgumentosCMD* inicializa()
{
    ArgumentosCMD* novo = (ArgumentosCMD*)malloc(sizeof(ArgumentosCMD));

    novo->arqEntrada = NULL;
    novo->arqSaida = NULL;
    novo->quantN = 0;
    novo->tipoDado = '\0';
    novo->tipoSort = NULL;

    return novo;
}

char* pegarArg(char const *argv[])
{
    return ((char*)argv[0]);
}

char pegaTipo(char const *argv[])
{
    return argv[0][0];
}

ArgumentosCMD* linhaDeArgumentos(ArgumentosCMD* args, char const *argv[], int argc)
{
    args->tipoDado = pegaTipo(argv+1);

    if(args->tipoDado == 'N')
        args->quantN = atoi(pegarArg(argv+2));
    else
        strcpy(args->arqEntrada, pegarArg(argv+2));

    if(argc-1 > 2)
        strcpy(args->tipoSort, pegarArg(argv+3));

    if(argc-1 > 3)
        strcpy(args->arqSaida, pegarArg(argv+4));

    return args;
}

void limpaArg(ArgumentosCMD *arg)
{
    arg->tipoDado = '\0';

    if(arg->arqEntrada)
        free(arg->arqEntrada);

    if(arg->arqSaida)
        free(arg->arqSaida);

    if(arg->tipoSort)
        free(arg->tipoSort);

    if(arg->quantN)
        arg->quantN = 0;

    free(arg);
}

int* criaVetor(int tam)
{
    int i;
    int *vet = (int*)malloc(sizeof(int)*tam);

    for(i = 0; i < tam; i++)
    {
        vet[i] = (rand() * rand())%MAXINT;
    }

    return vet;
}

void determinaDado(ArgumentosCMD* arg)
{
    if(arg->quantN > 0 && (arg->tipoDado == 'N' || arg->tipoDado == 'n'))
    {
        int* vetN;
        vetN = criaVetor(arg->quantN);
        fazOpN(vetN, arg);
    }
    else if(arg->tipoDado == 'C' || arg->tipoDado == 'c')
    {
        char** vet;
        vet = lerArq(arg->arqEntrada, &arg->quantN);
        fazOpC(vet, arg);
    }
}

void fazOpN(int v[], ArgumentosCMD* arg)
{
    if(arg->tipoSort == NULL)
        fazTodasOrdN(v, arg->quantN);

    else{
        if(arg->arqSaida == NULL)
            printf("Arquivo de Saida nao selecionado\n");
        else{
            ordArq(v, arg);
        }
    }
}

void fazOpC(char* v[], ArgumentosCMD* a)
{
    if(a->tipoSort == NULL)
    {
        comparaTempo(v, a->quantN);
        int i;
        for(i = 0; i < a->quantN; i++)
            printf("%s\n",v[i]);
    }
    else
    {
        if(a->arqSaida == NULL)
        {
            printf("Arquivo de saida nao escolhido!\n");
            return;
        }
        else
            opeArq(v, a);
    }
}
