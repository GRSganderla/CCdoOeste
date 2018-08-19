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

void leArq(FILE* f, int *tam, char** vet)
{
    int i;
    char v[300];

    for(i = 0; !feof(f); i++)
    {
        fscanf(f, "%[^\n]%*c", v);
        vet[i] = v;
    }

    *tam = i;
}

void abreArq(char* v[], char* nome, int *tam)
{
    FILE* f = fopen(nome, "r");

    if(f == NULL)
    {
        printf("Arquivo de Entrada vazio\n");
        return;
    }

    leArq(f, tam, v);
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

    char *vet1[tam], *vet2[tam], *vet3[tam], *vet4[tam], *vet5[tam];

    copiaVetC(vet,vet1, tam);
    copiaVetC(vet,vet2, tam);
    copiaVetC(vet,vet3, tam);
    copiaVetC(vet,vet4, tam);
    copiaVetC(vet,vet5, tam);

    tempo1 = tempoC(vet1, "insertionsort", tam);
    tempo2 = tempoC(vet2, "selectionsort", tam);
    tempo3 = tempoC(vet3, "mergesort", tam);
    tempo4 = tempoC(vet4, "quicksort", tam);
    tempo5 = tempoC(vet5, "heapsort", tam);

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
        //else
            //opeArq(v, a->quantN);
    }
}

void copiaVet(int vet[], int vAux[], int tam)
{
    int i;
    for(i = 0; i < tam; i++)
        vAux[i] = vet[i];
}

