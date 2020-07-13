#ifndef SORTS_H
#define SORTS_H

///
/// \brief selectionSortN, algoritmo de ordenação por metodo de selecção
/// \param v, vetor a ser ordenado
/// \param n, tamanho maximo do vetor
/// \pre nenhuma
/// \post nenhuma
///
void selectionSortN(int v[], int n);

///
/// \brief insertionSortN, algoritmo de ordenação por metodo de inserção
/// \param vet, vetor a ser ordenado
/// \param n, tamanho maximo do vetor
/// \pre nenhuma
/// \post nenhuma
///
void insertionSortN(int vet[], int n);

///
/// \brief intercala, função auxiliar do algoritmo de ordenação Merge Sort
/// \param vet, vetor a ser ordenado
/// \param inicio, indice do inicio da parte do vetor separada
/// \param meio, indice do meio do vetor partido
/// \param fim, tamanho maximo da partição
/// \pre nenhuma
/// \post nenhuma
///
void intercala(int vet[],int inicio, int meio, int fim);

///
/// \brief mergeSortN, algoritmo de ordenação por metodo de separar, ordenar e reajuntar e ordenar...
/// \param v, vetor a ser ordenado
/// \param inicio, indice do inicio do vetor
/// \param fim, tamanho maximo do vetor
/// \pre nenhuma
/// \post nenhuma
///
void mergeSortN(int v[], int inicio, int fim);

///
/// \brief separa, função auxiliar do algoritmo de ordenação Quick Sort
/// \param vet, vetor a ser ordenado
/// \param inicio, indice do inicio da partição
/// \param fim, indice do final da partição
/// \return retorna o indice do pivo, esse que esta entre os maiores e os menores ao mesmo tempo
/// \pre nenhuma
/// \post nenhuma
///
int separa(int vet[], int inicio, int fim);

///
/// \brief quickSortN, algoritmo de ordenação por metodo de determinar um pivo e separar o vetor a partir dele e ordenar as partes
/// \param vet, vetor a ser ordenado
/// \param inicio, indice do inicio da partição do vetor ou o vetor
/// \param fim, indice do final da partição do vetor ou o vetor
/// \pre nenhuma
/// \post nenhuma
///
void quickSortN(int vet[],int inicio, int fim);

///
/// \brief insereHeap, função auxiliar do algoritmo Heap Sort, que arruma o vetor para o maior fica em primeiro
/// \param m, tamanho maximo do vetor
/// \param vet, vetor a ser arrumado
/// \pre nenhuma
/// \post nenhuma
///
void insereHeap(int m, int vet[]);

///
/// \brief sacodeHeap, faz com que o vetor vire Max Heap
/// \param m, tamanho maximo do vetor
/// \param v, vetor a virar Max Heap
/// \pre nenhuma
/// \post nenhuma
///
void sacodeHeap(int m, int v[]);

///
/// \brief heapSortN, algoritmo de ordenação que usa sistema de arvore binaria
/// \param n, tamanho maximo do vetor
/// \param vet, vetor a ser ordenado
/// \pre nenhuma
/// \post nenhuma
///
void heapSortN(int n, int vet[]);

///Algoritmos de ordenação de cadeias de caracter

///
/// \brief selectionSortC, algoritmo de ordenação por metodo de selecção
/// \param v, vetor a ser ordenado
/// \param n, tamanho maximo do vetor
/// \pre nenhuma
/// \post nenhuma
///
void selectionSortC(char *v[], int n);

///
/// \brief insertionSortC, algoritmo de ordenação por metodo de inserção
/// \param vet, vetor a ser ordenado
/// \param n, tamanho maximo do vetor
/// \pre nenhuma
/// \post nenhuma
///
void insertionSortC(char *vet[], int n);

///
/// \brief intercalaC, função auxiliar do algoritmo de ordenação Merge Sort
/// \param vet, vetor a ser ordenado
/// \param inicio, indice do inicio da parte do vetor separada
/// \param meio, indice do meio do vetor partido
/// \param fim, tamanho maximo da partição
/// \pre nenhuma
/// \post nenhuma
///
void intercalaC(char* vet[],int inicio, int meio, int fim);

///
/// \brief mergeSortC, algoritmo de ordenação por metodo de separar, ordenar e reajuntar e ordenar...
/// \param v, vetor a ser ordenado
/// \param inicio, indice do inicio do vetor
/// \param fim, tamanho maximo do vetor
/// \pre nenhuma
/// \post nenhuma
///
void mergeSortC(char *v[], int inicio, int fim);

///
/// \brief separaC, função auxiliar do algoritmo de ordenação Quick Sort
/// \param vet, vetor a ser ordenado
/// \param inicio, indice do inicio da partição
/// \param fim, indice do final da partição
/// \return retorna o indice do pivo, esse que esta entre os maiores e os menores ao mesmo tempo
/// \pre nenhuma
/// \post nenhuma
///
int separaC(char* vet[], int inicio, int fim);

///
/// \brief quickSortC, algoritmo de ordenação por metodo de determinar um pivo e separar o vetor a partir dele e ordenar as partes
/// \param vet, vetor a ser ordenado
/// \param inicio, indice do inicio da partição do vetor ou o vetor
/// \param fim, indice do final da partição do vetor ou o vetor
/// \pre nenhuma
/// \post nenhuma
///
void quickSortC(char *vet[], int inicio, int fim);

///
/// \brief insereHeapC, função auxiliar do algoritmo Heap Sort, que arruma o vetor para o maior fica em primeiro
/// \param m, tamanho maximo do vetor
/// \param vet, vetor a ser arrumado
/// \pre nenhuma
/// \post nenhuma
///
void insereHeapC(int m, char* vet[]);

///
/// \brief sacodeHeapC, faz com que o vetor vire Max Heap
/// \param m, tamanho maximo do vetor
/// \param v, vetor a virar Max Heap
/// \pre nenhuma
/// \post nenhuma
///
void sacodeHeapC(int m, char* v[]);

///
/// \brief heapSortC, algoritmo de ordenação que usa sistema de arvore binaria
/// \param n, tamanho maximo do vetor
/// \param vet, vetor a ser ordenado
/// \pre nenhuma
/// \post nenhuma
///
void heapSortC(int n, char *vet[]);

#endif // SORTS_H
