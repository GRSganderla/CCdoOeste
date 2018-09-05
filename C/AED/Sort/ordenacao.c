#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordenacao.h"

///
/// \brief selectionSortN, algoritmo de ordenação por metodo de selecção
/// \param v, vetor a ser ordenado
/// \param n, tamanho maximo do vetor
/// \pre nenhuma
/// \post nenhuma
///
void selectionSortN(int v[], int n)
{
    int i, j, min, temp;

    //enquanto não for o penultimo
    for(i = 0; i < n - 1; i++)
    {
        //pega o menor indice
        min = i;

        //procura ate o final, o indice que tem valor menor que o valor do indice min
        for(j = i + 1; j < n; j++)
            if(v[j] < v[min])
                min = j;

        //troca de posição
        temp = v[i];
        v[i] = v[min];
        v[min] = temp;

    }
}

///
/// \brief insertionSortN, algoritmo de ordenação por metodo de inserção
/// \param vet, vetor a ser ordenado
/// \param n, tamanho maximo do vetor
/// \pre nenhuma
/// \post nenhuma
///
void insertionSortN(int vet[], int n)
{
    int i, j, temp;

    //enquanto não for o final
    for (j = 1; j < n; j++)
    {
        //variavel temporaria recebe o valor do indice J
        temp = vet[j];

        //enquanto não for 0 e o vetor I for maior que o da variavel temporaría, avança o vetor para uma posição a frente
        for (i = j-1; i >= 0 && vet[i] > temp; i--)
            vet[i+1] = vet[i];

        //coloca no indice i + 1 a variavel temporaria
        vet[i+1] = temp;
    }
}
///
/// \brief intercala, função auxiliar do algoritmo de ordenação Merge Sort
/// \param vet, vetor a ser ordenado
/// \param inicio, indice do inicio da parte do vetor separada
/// \param meio, indice do meio do vetor partido
/// \param fim, tamanho maximo da partição
/// \pre nenhuma
/// \post nenhuma
///
void intercala(int vet[],int inicio, int meio, int fim)
{
    int i, j, k, *vet_aux;

    //aloca o vetor
    vet_aux = malloc((fim-inicio)*sizeof(int));

    i = inicio; j = meio; k = 0;

    //enquanto não for o meio ou o fim
    while( i < meio && j < fim)
    {
        //se o vetor J é maior ou igual a o vetor I, adiciona o valor de I em K, aumenta ambos
        if(vet[i] <= vet[j])
            vet_aux[k++] = vet[i++];
        else
        {
            //se não é menor ou igual, adiciona o valor de J em K, aumenta ambos
            vet_aux[k++] = vet[j++];
        }
    }

    //enquanto não for o meio, adiciona I em K, aumenta ambos
    while (i < meio)
        vet_aux[k++] = vet[i++];

    //enquanto não for o meio, adiciona J em K, aumenta ambos
    while (j < fim)
        vet_aux[k++] = vet[j++];

    //adiciona no vetor original, o vetor K
    for(i = inicio; i < fim; i++)
        vet[i] = vet_aux[i-inicio];

    //libera o vetor auxiliar
    free(vet_aux);
}

///
/// \brief mergeSortN, algoritmo de ordenação por metodo de separar, ordenar e reajuntar e ordenar...
/// \param v, vetor a ser ordenado
/// \param inicio, indice do inicio do vetor
/// \param fim, tamanho maximo do vetor
/// \pre nenhuma
/// \post nenhuma
///
void mergeSortN(int v[], int inicio, int fim)
{
    if( inicio < fim - 1)
    {
        //chama recursivamente ate tiver um vetor separado com 2 valores
        int meio = (inicio + fim) / 2;
        mergeSortN(v, inicio, meio);
        mergeSortN(v, meio, fim);
        intercala(v, inicio, meio, fim);
    }
}

///
/// \brief separa, função auxiliar do algoritmo de ordenação Quick Sort
/// \param vet, vetor a ser ordenado
/// \param inicio, indice do inicio da partição
/// \param fim, indice do final da partição
/// \return retorna o indice do pivo, esse que esta entre os maiores e os menores ao mesmo tempo
/// \pre nenhuma
/// \post nenhuma
///
int separa(int vet[], int inicio, int fim)
{
    int pivo, j, k, temp;

    //pega o valor do ultimo indice
    pivo = vet[fim];
    j = inicio;

    //percorre do inicio até o fim
    for(k = inicio; k < fim; k++)
    {
        //se for menor que o pivo, troca o inicio com o pivo
        if(vet[k] <= pivo)
        {
            temp = vet[j];
            vet[j] = vet[k];
            vet[k] = temp;
            j++;
        }
    }

    //valor do fim vira o valor de J, j vira o pivo
    vet[fim] = vet[j];
    vet[j] = pivo;

    //retorna o indice do pivo
    return j;
}


///
/// \brief quickSortN, algoritmo de ordenação por metodo de determinar um pivo e separar o vetor a partir dele e ordenar as partes
/// \param vet, vetor a ser ordenado
/// \param inicio, indice do inicio da partição do vetor ou o vetor
/// \param fim, indice do final da partição do vetor ou o vetor
/// \pre nenhuma
/// \post nenhuma
///
void quickSortN(int vet[],int inicio, int fim)
{
    int j;

    //enquanto não for o fim
    if(inicio < fim)
    {
        //recebe o indice do pivo, e separa em partes a partir do pivo
        j = separa(vet, inicio, fim);
        quickSortN(vet, inicio, j-1);
        quickSortN(vet, j+1, fim);
    }
}

///
/// \brief insereHeap, função auxiliar do algoritmo Heap Sort, que arruma o vetor para o maior fica em primeiro
/// \param m, tamanho maximo do vetor
/// \param vet, vetor a ser arrumado
/// \pre nenhuma
/// \post nenhuma
///
void insereHeap(int m, int vet[])
{
    int f = m + 1;

    //enquanto o indice a frente for maior do que o do indice de sua metade
    while (f > 1 && vet[f/2] < vet[f])
    {
        //troca eles de posição
        int t = vet[f/2];
        vet[f/2] = vet[f];
        vet[f] = t;

        f = f/2;
    }
}


///
/// \brief sacodeHeap, faz com que o vetor vire Max Heap
/// \param m, tamanho maximo do vetor
/// \param v, vetor a virar Max Heap
/// \pre nenhuma
/// \post nenhuma
///
void sacodeHeap(int m, int v[])
{
    int t, f = 2;

    //enquanto o indice não for menor ou igual a 2
    while (f <= m)
    {
        //se o proximo for maior que o atual, aumenta o indice
        if(f < m && v[f] < v[f+1])
            ++f;

        //se o indice da metade de um é maior ou igual a ele, termina aqui
        if(v[f/2] >= v[f])
            break;

        //troca os valores das posições
        t = v[f/2];
        v[f/2] = v[f];
        v[f] = t;

        f *= 2;
    }
}

///
/// \brief heapSortN, algoritmo de ordenação que usa sistema de arvore binaria
/// \param n, tamanho maximo do vetor
/// \param vet, vetor a ser ordenado
/// \pre nenhuma
/// \post nenhuma
///
void heapSortN(int n, int vet[])
{
    int m;

    //enquanto não for o final, faz o insereHeap
    for(m = 1; m < n; m++)
        insereHeap(m,vet);

    //enquanto não for 1
    for(m = n; m > 1; m--)
    {
        //pega o valor do segundo indice e troca com o indice M
        int t = vet[1];
        vet[1] = vet[m];
        vet[m] = t;
        sacodeHeap(m-1,vet);
    }
}

//Algoritmos de ordenação de cadeias de caracteres

void selectionSortC(char* v[], int n)
{
    int i, j, min;
    char* x;

    for(i = 0; i < n - 1; i++)
    {
        min = i;

        for(j = i + 1; j < n; j++)
            if(strcmp(v[j], v[min]) < 0)
                min = j;

        x = v[i];
        v[i] = v[min];
        v[min] = x;

    }
}

void insertionSortC(char* vet[], int n)
{
    int i, j;
    char* temp;

    for (j = 1; j < n; j++)
    {
        temp = vet[j];

        for (i = j-1; i >= 0 && (strcmp(vet[i], temp) > 0); i--)
            vet[i+1] = vet[i];

        vet[i+1] = temp;
    }
}

void intercalaC(char* vet[],int inicio, int meio, int fim)
{
    int i, j, k;
    char **vet_aux;

    vet_aux = malloc((fim-inicio)*sizeof(char*));

    i = inicio; j = meio; k = 0;

    while( i < meio && j < fim)
    {
        if(strcmp(vet[i], vet[j]) <= 0)
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

void mergeSortC(char* v[], int inicio, int fim)
{
    if( inicio < fim - 1)
    {
        int meio = (inicio + fim) / 2;
        mergeSortC(v, inicio, meio);
        mergeSortC(v, meio, fim);
        intercalaC(v, inicio, meio, fim);
    }
}

int separaC(char* vet[], int inicio, int fim)
{
    int j, k;
    char* temp,* pivo;

    pivo = vet[fim];
    j = inicio;

    for(k = inicio; k < fim; k++)
    {
        if(strcmp(vet[k], pivo) <=0)
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

void quickSortC(char* vet[],int inicio, int fim)
{
    int j;

    if(inicio < fim)
    {
        j = separaC(vet, inicio, fim);
        quickSortC(vet, inicio, j-1);
        quickSortC(vet, j+1, fim);
    }
}

void insereHeapC(int m, char* vet[])
{
    int f = m + 1;

    while (f > 1 && strcmp(vet[f/2], vet[f])  < 0)
    {
        char* t = vet[f/2];
        vet[f/2] = vet[f];
        vet[f] = t;

        f = f/2;
    }
}

void sacodeHeapC(int m, char* v[])
{
    char* t;
    int f = 2;

    while (f <= m)
    {
        if(f < m && (strcmp(v[f], v[f+1]) < 0))
            ++f;

        if(strcmp(v[f/2], v[f]) >= 0)
            break;

        t = v[f/2];
        v[f/2] = v[f];
        v[f] = t;

        f *= 2;
    }
}

void heapSortC(int n, char* vet[])
{
    int m;

    for(m = 1; m < n; m++)
        insereHeapC(m,vet);

    for(m = n; m > 1; m--)
    {
        char* t = vet[1];
        vet[1] = vet[m];
        vet[m] = t;
        sacodeHeapC(m-1,vet);
    }
}
