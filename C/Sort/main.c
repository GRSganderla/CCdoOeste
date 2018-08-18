#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operacoes.h"

int main(int argc, const char *argv[])
{
    ArgumentosCMD* args = inicializa();

    args = linhaDeArgumentos(args, argv, argc);

    determinaOp(args);

    printf("%c\n", args->tipoDado);
    printf("%d\n", args->quantN);
    printf("%s\n", args->arqEntrada);
    printf("%s\n", args->tipoSort);
    printf("%s\n", args->arqSaida);

    limpaArg(args);
    return 0;
}

/*selectionSort(v, 10);
insertionSort(v2, 10);
bubbleSort(v3, 10);
mergeSort(v4, 0, 10);
quickSort(v5, 0, 9);
heapSort(10, v6-1);*/
