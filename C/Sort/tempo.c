#include<time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include "tempo.h"

float ordN(int vet[], char *tipoSort, int tam)
{
    clock_t tempo;
    int *vAux =(int*)malloc(sizeof(int)*tam);

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
    else
    {
        printf("Algoritmo de Ordenacao nao correto = %s\n", tipoSort);
    }

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
            printf("Arquivo de Saida nao selecionado\n");
        else{
            ordArq(v, arg);
        }
    }
}

void fazTodasOrdN(int vet[], int tam)
{
    float tempo1, tempo2, tempo3, tempo4, tempo5;

    int vet1[tam], vet2[tam], vet3[tam], vet4[tam], vet5[tam];

    copiaVet(vet,vet1, tam);
    copiaVet(vet,vet2, tam);
    copiaVet(vet,vet3, tam);
    copiaVet(vet,vet4, tam);
    copiaVet(vet,vet5, tam);

    tempo1 = ordN(vet1, "insertionsort", tam);
    tempo2 = ordN(vet2, "selectionsort", tam);
    tempo3 = ordN(vet3, "mergesort", tam);
    tempo4 = ordN(vet4, "quicksort", tam);
    tempo5 = ordN(vet5, "heapsort", tam);

    printf("Insertion Sort\t->\t%.4f\n", tempo1);
    printf("Selection Sort\t->\t%.4f\n", tempo2);
    printf("Merge Sort\t->\t%.4f\n", tempo3);
    printf("Quick Sort\t->\t%.4f\n", tempo4);
    printf("Heap Sort\t->\t%.4f\n", tempo5);

    free(vet1);
    free(vet2);
    free(vet3);
    free(vet4);
    free(vet5);
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

void copiaVetC(char* v[], char* vet[], int tam)
{
    int i;

    for(i = 0; i < tam; i++)
        vet[i] = v[i];
}

float tempoC(char* v[], char* tipoSort, int tam)
{
    char** vAux = (char**)malloc(sizeof(char*)*tam);

    copiaVetC(v, vAux, tam);

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

    copiaVetC(vAux, v, tam);
    free(vAux);
    return tempoGasto;
}

void comparaTempo(char *vet[], int tam)
{
    float tempo1, tempo2, tempo3, tempo4, tempo5;

    char** vetAUX1 = (char**)malloc(sizeof(char*)*tam);
    char** vetAUX2 = (char**)malloc(sizeof(char*)*tam);
    char** vetAUX3 = (char**)malloc(sizeof(char*)*tam);
    char** vetAUX4 = (char**)malloc(sizeof(char*)*tam);
    char** vetAUX5 = (char**)malloc(sizeof(char*)*tam);

    copiaVetC(vet,vetAUX1, tam);
    copiaVetC(vet,vetAUX2, tam);
    copiaVetC(vet,vetAUX3, tam);
    copiaVetC(vet,vetAUX4, tam);
    copiaVetC(vet,vetAUX5, tam);

    tempo1 = tempoC(vetAUX1, "insertionsort", tam);
    tempo2 = tempoC(vetAUX2, "selectionsort", tam);
    tempo3 = tempoC(vetAUX3, "mergesort", tam);
    tempo4 = tempoC(vetAUX4, "quicksort", tam);
    tempo5 = tempoC(vetAUX5, "heapsort", tam);

    printf("Insertion Sort\t->\t%.4f\n", tempo1);
    printf("Selection Sort\t->\t%.4f\n", tempo2);
    printf("Merge Sort\t->\t%.4f\n", tempo3);
    printf("Quick Sort\t->\t%.4f\n", tempo4);
    printf("Heap Sort\t->\t%.4f\n", tempo5);

    free(vetAUX1);
    free(vetAUX2);
    free(vetAUX3);
    free(vetAUX4);
    free(vetAUX5);
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

void fazOpC(char* v[], ArgumentosCMD* a)
{
    if(a->tipoSort == NULL)
        comparaTempo(v, a->quantN);
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

void copiaVet(int vet[], int vAux[], int tam)
{
    int i;
    for(i = 0; i < tam; i++)
        vAux[i] = vet[i];
}

