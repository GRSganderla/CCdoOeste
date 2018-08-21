#ifndef TEMPOOP_H
#define TEMPOOP_H

#include "operacoes.h"

///
/// \brief fazTodasOrdN, faz todas as ordenação e compara os tempos
/// \param vet, vetor a ser ordenado por todos os metodos
/// \param tam, tamanho maximo do vetor
/// \pre nenhuma
/// \post vetor é ordenado
///
void comparaTempoN(int vet[], int tam);

///
/// \brief ordN, faz a ordenação do tipo de algoritmo passado e pega o tempo de duração da execução do algoritmo
/// \param vet, vetor a ser ordenado
/// \param tipoSort, tipo do metodo de ordenação
/// \param tam, tamanho maximo do vetor
/// \return retorna o tempo total da ordenação
///
float ordenaN(int vet[], char *tipoSort, int tam);

///
/// \brief imprimiNoArqN, imprime no Arq o conteudo ordenado do vetor
/// \param v, vetor que vai ser ordenado e imprimido
/// \param a, estrutura com os argumentos, contendo o tipo de metodo de ordenação e o nome do arquivo de saida
/// \pre nenhuma
/// \post nenhuma
///
void imprimeNoArqN(int v[], ArgumentosCMD* a);

///
/// \brief lerArq, abre e le o arquivo de entrada, guardando em um vetor de strings que é retornado
/// \param nome, nome do arquivo a ser aberto e escaneado
/// \param tam, variavel que vai receber a quantidade de strings que estão contidas no arquivo
/// \return retorna um vetor de strings contendo todas as palavras dentro do arquivo
/// \pre nenhuma
/// \post é alocado o espaço dinamicamente para o vetor de strings
///
char** lerArq(char* nome, int *tam);

///
/// \brief ordenaC, ordena o vetor de strings e determina o tempo de execução
/// \param v, vetor de strings a ser ordenado
/// \param tipoSort, tipo do algoritmo a ser usado para ordenar
/// \param tam, quantidade de strings armazenada no vetor de strings
/// \return retorna a quantidade de tempo total da execução da ordenação
/// \pre nenhuma
/// \post nenhuma
///
float ordenaC(char* v[], char* tipoSort, int tam);

///
/// \brief comparaTempoC, ordena o vetor de strings em todos os metodos de ordenação e imprime os tempos de cada ordenação
/// \param vet, vetor de strings a ser ordenado pelos varios metodos de ordenação
/// \param tam, quantidade de strings dentro do vetor
/// \pre nenhuma
/// \post nenhuma
///
void comparaTempoC(char *vet[], int tam);

///
/// \brief imprimeNoArqC, manda ordenar o vetor de strings e imprime no arquivo de saida o vetor
/// \param v, vetor a ser ordenado e imprimido
/// \param a, estrutura que contém o tipo de ordenção e arquivo de saida
/// \pre nenhuma
/// \post nenhuma
///
void imprimeNoArqC(char* v[], ArgumentosCMD* a);

#endif // TEMPOOP_H
