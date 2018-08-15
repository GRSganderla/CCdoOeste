#ifndef ARQUIVO_H
#define ARQUIVO_H

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define MAX 100
#define MAXQ 20
#define MAXF 10
#define MAXA 20

///declarando a struct estado para ser
struct estado;

//struct que guarda as informações de cada transições
typedef struct transicao
{
    //terminal que a transição lê
    char terminal;
    //ponteiro que guarda qual é o proximo estado após ter lido o terminal
    struct estado *proximoEstado;
}Transicao;

//struct que guarda as informações de cada estado
typedef struct estado
{
    //nome do estado
    char nome[MAX];
    //transições que ele faz
    Transicao transicoes[MAX];
    //quantidade de transições que ele faz
    int tamanhoT;
}Estado;

//struct controle de todo o AFD
typedef struct afd
{
    //alfabeto que o AFD lê
    char alfa[MAXA];
    //vetor de cada estado que ele pode ter
    Estado estados[MAXQ];
    //quantidade de estados que ele tem
    int tamanhoE;
    //quantidade de estados finais que ele tem
    int tamanhoF;
    //vetor de estados finais, que são referenciados
    Estado *finais[MAXF];
    //referencia do estado inicial
    Estado *inicial;
}AFD;

///
/// \brief qualEstado, procura por todos os estados guardados do AFD o estado que tenha tal nome
/// \param afd, struct com os estados a serem pesquisados
/// \param str, nome do estado que está sendo buscado
/// \return retorna o indice a qual o estado esta dentro do vetor de estados do AFD ou -1 se não for encontrado
/// \pre nenhum
/// \post nenhum
///
int qualEstado(AFD* afd, char str[]);

///
/// \brief entrada, função que abre o arquivo do nome de entrada e guarda as informações que o AFD precisa conter
/// \param s, string com o nome do arquivo a ser aberto
/// \param afds, struct que ira guardar as informações do AFD a ser usado
/// \return retorna 1 se for aberto corretamente ou 0 se não foi aberto corretamente
/// \pre o arquivo de nome s tem que ter sido criado e estar contido no computador
/// \post o afds conterá cada um das informações do AFD que será usado
///
int entrada(char s[], AFD *afds);

#endif // ARQUIVO_H
