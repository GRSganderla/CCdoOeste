#include <stdio.h>
#include <stdlib.h>
#include "ordenacao.h"

void selectionSortN(int v[], int n)
{
    int i, j, min, temp;

    for(i = 0; i < n - 1; i++)
    {
        min = i;

        for(j = i + 1; j < n; j++)
            if(v[j] < v[min])
                min = j;

        temp = v[i];
        v[i] = v[min];
        v[min] = temp;

    }
}

void insertionSortN(int vet[], int n)
{
    int i, j, temp;

    for (j = 1; j < n; j++)
    {
        temp = vet[j];

        for (i = j-1; i >= 0 && vet[i] > temp; i--)
            vet[i+1] = vet[i];

        vet[i+1] = temp;
    }
}
void intercala(int vet[],int inicio, int meio, int fim)
{
    int i, j, k, *vet_aux;

    vet_aux = malloc((fim-inicio)*sizeof(int));

    i = inicio; j = meio; k = 0;

    while( i < meio && j < fim)
    {
        if(vet[i] <= vet[j])
            vet_aux[k++] = vet[i++];
        else
            vet_aux[k++] = vet[j++];
    }

    while (i < meio)
        vet_aux[k++] = vet[i++];

    while (j < fim)
        vet_aux[k++] = vet[j++];

    for(i = inicio; i < fim; i++)
        vet[i] = vet_aux[i-inicio];

    free(vet_aux);
}

void mergeSortN(int v[], int inicio, int fim)
{
    if( inicio < fim - 1)
    {
        int meio = (inicio + fim) / 2;
        mergeSortN(v, inicio, meio);
        mergeSortN(v, meio, fim);
        intercala(v, inicio, meio, fim);
    }
}

int separa(int vet[], int inicio, int fim)
{
    int pivo, j, k, temp;

    pivo = vet[fim];
    j = inicio;

    for(k = inicio; k < fim; k++)
    {
        if(vet[k] <= pivo)
        {
            temp = vet[j];
            vet[j] = vet[k];
            vet[k] = temp;
            j++;
        }
    }

    vet[fim] = vet[j];
    vet[j] = pivo;

    return j;
}

void quickSortN(int vet[],int inicio, int fim)
{
    int j;

    if(inicio < fim)
    {
        j = separa(vet, inicio, fim);
        quickSortN(vet, inicio, j-1);
        quickSortN(vet, j+1, fim);
    }
}

void insereHeap(int m, int vet[])
{
    int f = m + 1;

    while (f > 1 && vet[f/2] < vet[f])
    {
        int t = vet[f/2];
        vet[f/2] = vet[f];
        vet[f] = t;

        f = f/2;
    }
}

void sacodeHeap(int m, int v[])
{
    int t, f = 2;

    while (f <= m)
    {
        if(f < m && v[f] < v[f+1])
            ++f;

        if(v[f/2] >= v[f])
            break;

        t = v[f/2];
        v[f/2] = v[f];
        v[f] = t;

        f *= 2;
    }
}

void heapSortN(int n, int vet[])
{
    int m;

    for(m = 1; m < n; m++)
        insereHeap(m,vet);

    for(m = n; m > 1; m--)
    {
        int t = vet[1];
        vet[1] = vet[m];
        vet[m] = t;
        sacodeHeap(m-1,vet);
    }
}
