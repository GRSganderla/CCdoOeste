#include "operacao.h"
#include <stdlib.h>

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


ArgumentosCMD* linhaDeArgumentos(ArgumentosCMD* args, char const *argv[], int argc)
{
    args->tipoDado = pegarArg(argv+1);

    if(args->tipoDado == 'N')
        args->quantN = atoi(pegarArg(argv));
    else
        args->arqEntrada = pegarArg(argv+2);

    if(argc-1 > 2)
        args->tipoSort = pegarArg(argv+3);

    if(argc-1 > 3)
        args->arqSaida = pegarArg(argv+4);
}
