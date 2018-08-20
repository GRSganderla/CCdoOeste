#include<time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include "tempo.h"

float ordN(int vet[], char *tipoSort, int tam)
{
    int i;
    clock_t tempo;
    int *vAux =(int*)malloc(sizeof(int)*tam);

    for(i = 0; i < tam; i++)
        vAux[i] = vet[i];

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
    else
    {
        printf("Algoritmo de Ordenacao nao correto = %s\n", tipoSort);
    }

    tempo = clock() - tempo;

    tempoGasto = ((float)tempo)/CLOCKS_PER_SEC;

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

void fazTodasOrdN(int vet[], int tam)
{
    float tempo;

    tempo = ordN(vet, "insertionsort", tam);
    printf("Insertion Sort\t->\t%.4f\n", tempo);

    tempo = ordN(vet, "selectionsort", tam);
    printf("Selection Sort\t->\t%.4f\n", tempo);

    tempo = ordN(vet, "mergesort", tam);
    printf("Merge Sort\t->\t%.4f\n", tempo);

    tempo = ordN(vet, "quicksort", tam);
    printf("Quick Sort\t->\t%.4f\n", tempo);

    tempo = ordN(vet, "heapsort", tam);
    printf("Heap Sort\t->\t%.4f\n", tempo);
}

char** lerArq(char* nome, int *tam)
{
    int i, tamC;
    FILE* arq = fopen(nome, "r");
    if(arq == NULL) return NULL;

    char** c;
    char v[256];

    tamC= 2;
    c = (char**)malloc(sizeof(char*) * tamC);

    for(i = 0; !feof(arq); i++)
    {
        if(i+1 > tamC)
        {
            tamC *= 2;
            c = (char**)realloc(c, sizeof(char*) * tamC);
        }

        fscanf(arq, "%[^\n]%*c", v);
        c[i] = strcpy(malloc(sizeof(char) * strlen(v) + 1), v);
    }

    tamC = i;
    c = (char**)realloc(c, sizeof(char*) * tamC);

    *tam = tamC;
    return c;
}

float tempoC(char* v[], char* tipoSort, int tam)
{
    char** vAux = (char**)malloc(sizeof(char*)*tam);

    int i;
    for(i = 0; i < tam; i++)
        vAux[i] = v[i];

    clock_t tempo;
    float tempoGasto;
    tempo = clock();

    if(!strcmp(tipoSort, "insertionsort") || !strcmp(tipoSort, "INSERTIONSORT"))
        insertionSortC(vAux, tam);

    else if(!strcmp(tipoSort, "selectionsort") || !strcmp(tipoSort, "SELECTIONSORT"))
        selectionSortC(vAux, tam);

    else if(!strcmp(tipoSort, "mergesort") || !strcmp(tipoSort, "MERGESORT"))
        mergeSortC(vAux, 0, tam);

    else if(!strcmp(tipoSort, "quicksort") || !strcmp(tipoSort, "QUICKSORT"))
        quickSortC(vAux, 0, tam-1);

    else if(!strcmp(tipoSort, "heapsort") || !strcmp(tipoSort, "HEAPSORT"))
        heapSortC(tam, vAux-1);
    else
    {
        printf("Algoritmo de Ordenacao nao correto = %s\n", tipoSort);
    }

    tempo = clock() - tempo;

    tempoGasto = ((float)tempo)/CLOCKS_PER_SEC;

    free(vAux);
    return tempoGasto;
}

void comparaTempo(char *vet[], int tam)
{
    float tempo;

    tempo = tempoC(vet, "insertionsort", tam);
    printf("Insertion Sort\t->\t%.4f\n", tempo);

    tempo = tempoC(vet, "selectionsort", tam);
    printf("Selection Sort\t->\t%.4f\n", tempo);

    tempo = tempoC(vet, "mergesort", tam);
    printf("Merge Sort\t->\t%.4f\n", tempo);

    tempo = tempoC(vet, "quicksort", tam);
    printf("Quick Sort\t->\t%.4f\n", tempo);

    tempo = tempoC(vet, "heapsort", tam);
    printf("Heap Sort\t->\t%.4f\n", tempo);
}

void opeArq(char* v[], ArgumentosCMD* a)
{
    FILE* saida = fopen(a->arqSaida, "w+");

    float ab = tempoC(v, a->tipoSort, a->quantN);

    fprintf(saida, "%s:\n", a->tipoSort);
    fprintf(saida, "Tempo para Ordenar: %.4f\n{", ab);

    int i;
    for(i = 0; i < a->quantN; i++)
    {
        fprintf(saida, "%s\n", v[i]);
    }
}
