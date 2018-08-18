#include "operacoes.h"
#include <stdlib.h>
#include <string.h>

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
        args->arqEntrada = pegarArg(argv+2);

    if(argc-1 > 2)
        args->tipoSort = pegarArg(argv+3);

    if(argc-1 > 3)
        args->arqSaida = pegarArg(argv+4);

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

void determinaOp(ArgumentosCMD* arg)
{
    if(arg->quantN > 0 && (arg->tipoDado == 'N' || arg->tipoDado == 'n'))
    {
        int vetN[arg->quantN];
        criaVetor(vetN, arg->quantN);

    }
    else if((arg->tipoDado == 'C' || arg->tipoDado == 'c'))
    {
        char vetC;
        abreArq;
    }
}
