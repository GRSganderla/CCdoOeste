#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* pegarArg(char const *argv[])
{
    return ((char*)argv[0]);
}

void pegarArgumentos(int argc, char const *argv[], char* arqEntrada, char* arqSaida, char* tipoSort, int *tam, char* tipoDado)
{
    *tipoDado = pegarArg(argv+1);

    if(*tipoDado == 'N')
        *tam = atoi(pegarArg(argv));
    else
        arqEntrada = pegarArg(argv+2);

    if(argc-1 > 2)
        tipoSort = pegarArg(argv+3);

    if(argc-1 > 3)
        arqSaida = pegarArg(argv+4);
}

int main(int argc, const char *argv[])
{
    char* arqEntrada = NULL, *arqSaida = NULL, *tipoSort = NULL, tipoDado;
    int tam = 0;
    pegarArgumentos(argc, argv, arqEntrada, arqSaida, tipoSort, &tam, &tipoDado);
    printf("%d\n", tam);
    printf("%c\n", tipoDado);
    printf("%s\n", arqEntrada);
    printf("%s\n", tipoSort);
    printf("%s\n", arqSaida);
    return 0;
}

/*selectionSort(v, 10);
insertionSort(v2, 10);
bubbleSort(v3, 10);
mergeSort(v4, 0, 10);
quickSort(v5, 0, 9);
heapSort(10, v6-1);*/
