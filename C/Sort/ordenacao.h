#ifndef SORTS_H
#define SORTS_H

void selectionSortN(int v[], int n);

void insertionSortN(int vet[], int n);

void intercala(int vet[],int inicio, int meio, int fim);

void mergeSortN(int v[], int inicio, int fim);

int separa(int vet[], int inicio, int fim);

void quickSortN(int vet[],int inicio, int fim);

void insereHeap(int m, int vet[]);

void sacodeHeap(int m, int v[]);

void heapSortN(int n, int vet[]);

void selectionSortC(char *v[], int n);

///Algoritmos de ordenação de cadeias de caracter

void insertionSortC(char *vet[], int n);

void intercalaC(char* vet[],int inicio, int meio, int fim);

void mergeSortC(char *v[], int inicio, int fim);

int separaC(char* vet[], int inicio, int fim);

void quickSortC(char *vet[], int inicio, int fim);

void insereHeapC(int m, char* vet[]);

void sacodeHeapC(int m, char* v[]);

void heapSortC(int n, char *vet[]);

#endif // SORTS_H
