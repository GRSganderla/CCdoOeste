#include<time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include "tempo.h"

///
/// \brief ordenaN, faz todas as ordenação e compara os tempos
/// \param vet, vetor a ser ordenado por todos os metodos
/// \param tam, tamanho maximo do vetor
/// \pre nenhuma
/// \post vetor é ordenado
///
float ordenaN(int vet[], char *tipoSort, int tam)
{
    int i;
    clock_t tempo;
    int *vAux =(int*)malloc(sizeof(int)*tam);

    //copia o vet para um auxiliar
    for(i = 0; i < tam; i++)
        vAux[i] = vet[i];

    //inicia o tempo
    tempo = clock();
    float tempoGasto;

    //verifica qual o tipo de ordenação e chama o metodo
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

    //finaliza e determina o tempo total
    tempo = clock() - tempo;

    //determina em segundos o tempo
    tempoGasto = ((float)tempo)/CLOCKS_PER_SEC;

    //copia o vetor auxiliar de volta para o original, ordenado
    for(i = 0; i < tam; i++)
        vet[i] = vAux[i];

    //desaloca o auxiliar e retorna o tempo
    free(vAux);
    return tempoGasto;
}

///
/// \brief imprimeNoArqN, imprime no Arq o conteudo ordenado do vetor
/// \param v, vetor que vai ser ordenado e imprimido
/// \param a, estrutura com os argumentos, contendo o tipo de metodo de ordenação e o nome do arquivo de saida
/// \pre nenhuma
/// \post nenhuma
///
void imprimeNoArqN(int v[], ArgumentosCMD* a)
{
    //cria um arquivo com o nome de saida
    FILE* f = fopen(a->arqSaida, "w+");
    //ordena o vetor e volta o tempo de execução
    float tempo = ordenaN(v, a->tipoSort, a->quantN);

    //imprime o nome do metodo e o tempo de execução
    fprintf(f, "%s: \nTempo de Exec: %4f\n{\n", a->tipoSort, tempo);

    int i, j, linha = 0;

    //imprime os valores do vetor até o numero maximo do vetor
    for(i = 0; linha < a->quantN; i++)
    {
        //imprime os valores ate o numero maximo de valores por linha
        for(j = 0; j < 15 && linha < a->quantN ; j++)
        {
            fprintf(f, " %d[%d]", v[linha++], linha);
        }
        fprintf(f, "\n");
    }
    fprintf(f, "}");
}
///
/// \brief comparaTempoN, faz todas as ordenação e compara os tempos
/// \param vet, vetor a ser ordenado por todos os metodos
/// \param tam, tamanho maximo do vetor
/// \pre nenhuma
/// \post vetor é ordenado
///
void comparaTempoN(int vet[], int tam)
{
    float tempo;

    int *v1 =(int*)malloc(sizeof(int)*tam);
    int *v2 =(int*)malloc(sizeof(int)*tam);
    int *v3 =(int*)malloc(sizeof(int)*tam);
    int *v4 =(int*)malloc(sizeof(int)*tam);

    int i;
    //copia para os vetores auxiliares o valor do vetor original
    for(i = 0; i < tam; i++)
    {
        v1[i] = vet[i];
        v2[i] = vet[i];
        v3[i] = vet[i];
        v4[i] = vet[i];
    }

    //determina o tempo das ordenações e imprime o tempo de execução de cada metodo
    tempo = ordenaN(v1, "insertionsort", tam);
    printf("Insertion Sort\t->\t%.4f\n", tempo);

    tempo = ordenaN(v2, "selectionsort", tam);
    printf("Selection Sort\t->\t%.4f\n", tempo);

    tempo = ordenaN(v3, "mergesort", tam);
    printf("Merge Sort\t->\t%.4f\n", tempo);

    tempo = ordenaN(v4, "quicksort", tam);
    printf("Quick Sort\t->\t%.4f\n", tempo);

    tempo = ordenaN(vet, "heapsort", tam);
    printf("Heap Sort\t->\t%.4f\n", tempo);
}

///
/// \brief lerArq, abre e le o arquivo de entrada, guardando em um vetor de strings que é retornado
/// \param nome, nome do arquivo a ser aberto e escaneado
/// \param tam, variavel que vai receber a quantidade de strings que estão contidas no arquivo
/// \return retorna um vetor de strings contendo todas as palavras dentro do arquivo
/// \pre nenhuma
/// \post é alocado o espaço dinamicamente para o vetor de strings
///
char** lerArq(char* nome, int *tam)
{
    int i, tamC;
    //abre o arquivo de entrada
    FILE* arq = fopen(nome, "r");
    if(arq == NULL) return NULL;

    char** c;
    char v[300];

    tamC= 2;
    //aloca o vetor com um tamanho de ponteiro
    c = (char**)malloc(sizeof(char*) * tamC);

    //enquanto não for o final do arquivo
    for(i = 0; !feof(arq); i++)
    {
        //se o tamanho do arquivo é maior que o tamanho alocado
        if(i+1 > tamC)
        {
            //duplica o tamanho e realoca
            tamC *= 2;
            c = (char**)realloc(c, sizeof(char*) * tamC);
        }

        //escaneia até o contra-barra e elimina-o
        fscanf(arq, "%[^\n]%*c", v);
        //coloca no vetor, a string lida
        c[i] = strcpy(malloc(sizeof(char) * strlen(v) + 1), v);
    }

    //realoca o vetor para o tamanho total de strings
    tamC = i;
    c = (char**)realloc(c, sizeof(char*) * tamC);

    //referencia a quantidade total de strings e retorna o vetor
    *tam = tamC;
    return c;
}

///
/// \brief ordenaC, ordena o vetor de strings e determina o tempo de execução
/// \param v, vetor de strings a ser ordenado
/// \param tipoSort, tipo do algoritmo a ser usado para ordenar
/// \param tam, quantidade de strings armazenada no vetor de strings
/// \return retorna a quantidade de tempo total da execução da ordenação
/// \pre nenhuma
/// \post nenhuma
///
float ordenaC(char* v[], char* tipoSort, int tam)
{
    char** vAux = (char**)malloc(sizeof(char*)*tam);

    int i;
    //copia o vetor original para um auxiliar
    for(i = 0; i < tam; i++)
        vAux[i] = v[i];

    clock_t tempo;
    float tempoGasto;
    //inicia o tempo
    tempo = clock();

    //verifica qual o metodo de ordenação e chama a função do metodo
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

    //determina o tempo total
    tempo = clock() - tempo;

    //coloca em segundos o tempo
    tempoGasto = ((float)tempo)/CLOCKS_PER_SEC;

    //copia o vetor auxiliar no original, tornando ele ordenado
    for(i = 0; i < tam; i++)
        v[i] = vAux[i];

    //desaloca o vetor auxiliar e volta o tempo
    free(vAux);
    return tempoGasto;
}

///
/// \brief comparaTempoC, ordena o vetor de strings em todos os metodos de ordenação e imprime os tempos de cada ordenação
/// \param vet, vetor de strings a ser ordenado pelos varios metodos de ordenação
/// \param tam, quantidade de strings dentro do vetor
/// \pre nenhuma
/// \post nenhuma
///
void comparaTempoC(char *vet[], int tam)
{
    float tempo;
    char *v1[tam], *v2[tam], *v3[tam], *v4[tam];

    int i;
    //copia o vetor original em cada  vetor auxiliar
    for(i = 0; i < tam; i++)
    {
        v1[i] = vet[i];
        v2[i] = vet[i];
        v3[i] = vet[i];
        v4[i] = vet[i];
    }

    //determina o tempo de cada algoritmo de ordenação e imprime o tempo
    tempo = ordenaC(v1, "insertionsort", tam);
    printf("Insertion Sort\t->\t%.4f\n", tempo);

    tempo = ordenaC(v2, "selectionsort", tam);
    printf("Selection Sort\t->\t%.4f\n", tempo);

    tempo = ordenaC(v3, "mergesort", tam);
    printf("Merge Sort\t->\t%.4f\n", tempo);

    tempo = ordenaC(v4, "quicksort", tam);
    printf("Quick Sort\t->\t%.4f\n", tempo);

    tempo = ordenaC(vet, "heapsort", tam);
    printf("Heap Sort\t->\t%.4f\n", tempo);
}

///
/// \brief imprimeNoArqC, manda ordenar o vetor de strings e imprime no arquivo de saida o vetor
/// \param v, vetor a ser ordenado e imprimido
/// \param a, estrutura que contém o tipo de ordenção e arquivo de saida
/// \pre nenhuma
/// \post nenhuma
///
void imprimeNoArqC(char* v[], ArgumentosCMD* a)
{
    //cria o arquivo de saida
    FILE* saida = fopen(a->arqSaida, "w+");

    //ordena o vetor de strings e recebe o tempo da execução do algoritmo
    float ab = ordenaC(v, a->tipoSort, a->quantN);

    fprintf(saida, "%s:\n", a->tipoSort);
    fprintf(saida, "Tempo para Ordenar: %.4f\n{\n", ab);

    int i;
    //imprime as strings de cada indice do vetor
    for(i = 0; i < a->quantN; i++)
    {
        fprintf(saida, "%s\n", v[i]);
    }
}
