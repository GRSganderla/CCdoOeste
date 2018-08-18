#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operacao.c"

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

int main(int argc, const char *argv[])
{
    ArgumentosCMD* args = inicializa();
    args = linhaDeArgumentos(args, argv, argc);
    printf("%c\n", args->tipoDado);
    printf("%d\n", args->quantN);
    printf("%s\n", args->arqEntrada);
    printf("%s\n", args->tipoSort);
    printf("%s\n", args->arqSaida);
    return 0;
}

/*selectionSort(v, 10);
insertionSort(v2, 10);
bubbleSort(v3, 10);
mergeSort(v4, 0, 10);
quickSort(v5, 0, 9);
heapSort(10, v6-1);*/
