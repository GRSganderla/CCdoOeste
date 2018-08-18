#include<time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include "tempo.h"

float ordN(int vet[], char *tipoSort, int tam)
{
    clock_t tempo;
    int vAux[tam];

    copiaVet(vet, vAux, tam);

    tempo = clock();
    float tempoGasto;

    if(!strcmp(tipoSort, "insertionsort") || !strcmp(tipoSort, "INSERTIONSORT"))
        insertionSortN(vAux, tam);

    else if(!strcmp(tipoSort, "selectionsort") || !strcmp(tipoSort, "SELECTIONSORT"))
        selectionSortN(vAux, tam);

    else if(!strcmp(tipoSort, "mergesort") || !strcmp(tipoSort, "MERGESORT"))
        mergeSortN(vAux, 0, tam);

    else if(!strcmp(tipoSort, "quicksort") || !strcmp(tipoSort, "QUICKSORT"))
        quickSortN(vAux, 0, tam-1);

    else if(!strcmp(tipoSort, "heapsort") || !strcmp(tipoSort, "HEAPSORT"))
        heapSortN(tam, vAux-1);

    tempo = clock() - tempo;

    tempoGasto = ((float)tempo)/CLOCKS_PER_SEC;

    copiaVet(vAux, vet, tam);
    free(vAux);
    return tempoGasto;
}

void ordArq(int v[], ArgumentosCMD* a)
{
    FILE* f = fopen(a->arqSaida, "w+");
    float tempo = ordN(v, a->tipoSort, a->quantN);

    fprintf(f, "%s: \nTempo de Exec: %4f\n{\n", a->tipoSort, tempo);

    int i, j, linha = 0, numPorLinha = 20;

    for(i = 0; i < ceil(((double)a->quantN)/numPorLinha); i++)
    {
        for(j = 0; j < numPorLinha && linha < a->quantN ; j++)
        {
            fprintf(f, " %d ", v[linha++]);
        }
        fprintf(f, "\n");
    }
    fprintf(f, "}");
}

void fazOpN(int v[], ArgumentosCMD* arg)
{
    if(arg->tipoSort == NULL)
        fazTodasOrdN(v, arg->quantN);

    else{
        if(arg->arqSaida == NULL)
            ordN(v, arg->tipoSort, arg->quantN);
        else{
            ordArq(v, arg);
        }
    }
}

void fazTodasOrdN(int vet[], int tam)
{
    float tempo;

    tempo = ordN(vet, "INSERTIONSORT", tam);
    printf("Insertion Sort levou %.4f\n", tempo);

    tempo = ordN(vet, "SELECTIONSORT", tam);
    printf("Selection Sort levou %.4f\n", tempo);

    tempo = ordN(vet, "MERGESORT", tam);
    printf("Merge Sort levou %.4f\n", tempo);

    tempo = ordN(vet, "QUICKSORT", tam);
    printf("Quick Sort levou %.4f\n", tempo);

    tempo = ordN(vet, "HEAPSORT", tam);
    printf("Heap Sort levou %.4f\n", tempo);

}

void copiaVet(int vet[], int vAux[], int tam)
{
    int i;
    for(i = 0; i < tam; i++)
        vAux[i] = vet[i];
}

