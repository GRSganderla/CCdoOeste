#ifndef GRAMATICA_H
#define GRAMATICA_H

#include<stdio.h>
#include<stdlib.h>
#include "arquivo.h"

///
/// \brief alfabetoCMP, compara se o terminal passado pertence ao alfabeto que o AFD lê
/// \param afd, struct que mantém consigo o alfabeto a ser comparado
/// \param terminal, char terminal que vai ser comparado
/// \return retorna 1 se pertence ao alfabeto e 0 se não pertence
/// \pre afd não vazia
/// \post nenhuma
///
int alfabetoCMP(AFD afd, char terminal);

///
/// \brief fazerTransicao, funcao que busca em qual transição o terminal é lido e retorna o proximo estado
/// \param atual, estado em que se busca a transição na qual é lido o terminal
/// \param terminal, char que vai ser o alvo da busca da transição
/// \return retorna o proximo estado que o estado atual vai após ter lido o terminal
/// \pre nenhuma
/// \post nenhum
///
Estado* fazerTransicao(Estado* atual, char terminal);

///
/// \brief ehFinal, compara os nomes do estado passado com o estado final
/// \param afd, struct que contem os estados finais
/// \param atual, estado que se quer saber se é final ou não
/// \return retorna 1 se o estado passado é o final ou retorna 0 se o estado não é o final
/// \pre struct afd ter os estados finais guardados
/// \post nenhum
///
int ehFinal(AFD* afd, Estado* atual);

///
/// \brief verificaPalavra, verifica em ordem cada letra da passada e verifica se é possivel ser processada
/// \param afd, struct que contem os estados, alfabetos e as transições de cada estado
/// \param str, palavra a ser processada e verifica se é aceita pelo AFD
/// \param atual, estado a qual vai verificar se ele le o terminal da primeira letra da palavra
/// \return 1 se ela for aceita pelo AFD, ou seja, foi processada totalmente ou retorna 0 se não foi processada corretamente
/// \pre afd ter sido inicializado
/// \post nenhum
///
int verificaPalavra(AFD afd, char str[], Estado* atual);

///
/// \brief aceitaOUnao, função que printa se a palavra é aceita ou não pelo AFD
/// \param afd, struct que contém todos os dados para a verificação e processamento da palavra entrada
/// \param str, palavra a ser processada pelo AFD
/// \pre afd não tem estados e,ou, transições guardadas
/// \post nenhuma
///
void aceitaOUnao(AFD afd, char str[]);

///
/// \brief etois, função que retorna a conversão de string para inteiro feito pela função atoi
/// \param alvo, estado a qual vai ter seu nome convertido para inteiro
/// \return retorna o valor inteiro da string convertida
/// \pre estado alvo ter um nome
/// \post nenhum
///
int etois(Estado *alvo);

///
/// \brief printaLinhas, printa as linhas da gramatica que o AFD faz
/// \param afd, struct que guarda todas as informações para imprimir a gramatica
/// \param nTerminal, vetor que contem o nome dos não terminais que serão imprimidos ex: S, A, B...
/// \param atual, estado a qual vai ser verifica qual terminal ele lê e qual é o não terminal que ele corresponde
/// \pre afd conter as informações necessarias e nTerminal não ser vazio
/// \post nenhum
///
void printaLinhas(AFD* afd, char nTerminal[], Estado* atual);

///
/// \brief fazGramatica, determina qual vai ser o não terminal correspondente dos estados e manda imprimir as linhas de cada estado
/// \param afd, struct que contem os estados e seus nomes que serão determinados os não terminais correspondentes
/// \pre afd conter os estados e os nomes desses estados
/// \post nenhuma
///
void fazGramatica(AFD* afd);

#endif // GRAMATICA_H
