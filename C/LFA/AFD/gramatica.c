#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
#define MAXQ 20
#define MAXF 10
#define MAXA 20

#include "gramatica.h"

///
/// \brief alfabetoCMP, compara se o terminal passado pertence ao alfabeto que o AFD lê
/// \param afd, struct que mantém consigo o alfabeto a ser comparado
/// \param terminal, char terminal que vai ser comparado
/// \return retorna 1 se pertence ao alfabeto e 0 se não pertence
/// \pre afd não vazia
/// \post nenhuma
///
int alfabetoCMP(AFD afd, char terminal)
{
    int i;
    //percorre todo o alfabeto guardado em afd
    for(i =0; i < strlen(afd.alfa); i++)
        if(afd.alfa[i] == terminal)
            return 1;

    return 0;
}

///
/// \brief fazerTransicao, funcao que busca em qual transição o terminal é lido e retorna o proximo estado
/// \param atual, estado em que se busca a transição na qual é lido o terminal
/// \param terminal, char que vai ser o alvo da busca da transição
/// \return retorna o proximo estado que o estado atual vai após ter lido o terminal
/// \pre nenhuma
/// \post nenhum
///
Estado* fazerTransicao(Estado* atual, char terminal)
{
    int i;
    //percorre ate o tamanho total de transições
    for(i = 0; i < atual->tamanhoT; i++)
        if(atual->transicoes[i].terminal == terminal)
        {
            //retorna o proximo estado que o atual vai apos ter lido o terminal
            return atual->transicoes[i].proximoEstado;
        }
    return NULL;
}

///
/// \brief ehFinal, compara os nomes do estado passado com o estado final
/// \param afd, struct que contem os estados finais
/// \param atual, estado que se quer saber se é final ou não
/// \return retorna 1 se o estado passado é o final ou retorna 0 se o estado não é o final
/// \pre struct afd ter os estados finais guardados
/// \post nenhum
///
int ehFinal(AFD* afd, Estado* atual)
{
    int i;

    //percorre ate a quantidade total de estados finais e retorna se acho ou não
    for(i = 0; i < afd->tamanhoF; i++)
        if(!strcmp(afd->finais[i]->nome, atual->nome))
            return 1;

    return 0;
}

///
/// \brief verificaPalavra, verifica em ordem cada letra da passada e verifica se é possivel ser processada
/// \param afd, struct que contem os estados, alfabetos e as transições de cada estado
/// \param str, palavra a ser processada e verifica se é aceita pelo AFD
/// \param atual, estado a qual vai verificar se ele le o terminal da primeira letra da palavra
/// \return 1 se ela for aceita pelo AFD, ou seja, foi processada totalmente ou retorna 0 se não foi processada corretamente
/// \pre afd ter sido inicializado
/// \post nenhum
///
int verificaPalavra(AFD afd, char str[], Estado* atual)
{
    //se não tiver um estado atual
    if(!atual)
        return 0;

    char terminal = str[0];

    printf("[%s] %s\n", atual->nome, str);

    //se não tem mais letras a serem verificadas, retorna se o estado é final ou não
    if(terminal == '\0') return ehFinal(&afd, atual);
    //se não pertence ao alfabeto
    if(!alfabetoCMP(afd, terminal)) return 0;

    //retorna e abre recursivamente a função para o estado proximo após a transição ser feita
    return verificaPalavra(afd, str+1, fazerTransicao(atual, terminal));
}

///
/// \brief aceitaOUnao, função que printa se a palavra é aceita ou não pelo AFD
/// \param afd, struct que contém todos os dados para a verificação e processamento da palavra entrada
/// \param str, palavra a ser processada pelo AFD
/// \pre afd não tem estados e,ou, transições guardadas
/// \post nenhuma
///
void aceitaOUnao(AFD afd, char str[])
{
    //verifica se a palavra é aceita ou não pelo AFD
    if(verificaPalavra(afd, str, afd.inicial))
        printf("ACEITA\n");
    else
        printf("REJEITA\n");
}

///
/// \brief etois, função que retorna a conversão de string para inteiro feito pela função atoi
/// \param alvo, estado a qual vai ter seu nome convertido para inteiro
/// \return retorna o valor inteiro da string convertida
/// \pre estado alvo ter um nome
/// \post nenhum
///
int etois(Estado *alvo)
{
    //retorna o valor inteiro da string nome
    return atoi(alvo->nome+1);
}

///
/// \brief printaLinhas, printa as linhas da gramatica que o AFD faz
/// \param afd, struct que guarda todas as informações para imprimir a gramatica
/// \param nTerminal, vetor que contem o nome dos não terminais que serão imprimidos ex: S, A, B...
/// \param atual, estado a qual vai ser verifica qual terminal ele lê e qual é o não terminal que ele corresponde
/// \pre afd conter as informações necessarias e nTerminal não ser vazio
/// \post nenhum
///
void printaLinhas(AFD* afd, char nTerminal[], Estado* atual)
{
    int i;

    int local = etois(atual);

    printf("%c -> ", nTerminal[local]);

    //ate o total de transições
    for(i = 0; i < atual->tamanhoT; i++)
    {
        //printa o terminal lido e o proximo estado e verifica se o estado tem mais uma transição
        printf("%c%c ", atual->transicoes[i].terminal, nTerminal[etois(atual->transicoes[i].proximoEstado)]);

        if(atual->tamanhoT > i + 1)
        {
            printf("| ");

        }
    }

    //se for o estado final, printa a palavra vazia
    if(ehFinal(afd, atual))
        printf("| @");

    printf("\n");
}

///
/// \brief fazGramatica, determina qual vai ser o não terminal correspondente dos estados e manda imprimir as linhas de cada estado
/// \param afd, struct que contem os estados e seus nomes que serão determinados os não terminais correspondentes
/// \pre afd conter os estados e os nomes desses estados
/// \post nenhuma
///
void fazGramatica(AFD* afd)
{
    int i, letra, nTerminalInd;
    char nTerminal[MAXQ];

    //coloca em indice o valor da string do estado inicial que foi convertida em inteiro
    nTerminalInd = etois(afd->inicial);

    //o vetor de não terminais recebe no indice do estado incial a palavra S
    nTerminal[nTerminalInd] = 'S';

    //ate o numero de estados contidos
    for(i = letra = 0; i < afd->tamanhoE; i++)
    {
        //se não é o estado inicial
        if(strcmp(afd->estados[i].nome, afd->inicial->nome))
        {
            //guarda o valor inteiro da string nome do estado e coloca no vetor com indice desse valor da string a letra não terminal correspondente ao estado
            nTerminalInd = etois(&afd->estados[i]);
            nTerminal[nTerminalInd] = 'A' + letra++;
        }
    }

    //printa a linha do estado inicial e suas transições
    printaLinhas(afd, nTerminal, afd->inicial);

    //ate o número de estados contidos
    for(i = 0; i < afd->tamanhoE; i++)
    {
        //se não é o estado inicial, printa as transições desse estado
        if(strcmp(afd->estados[i].nome, afd->inicial->nome))
        {
            printaLinhas(afd, nTerminal, &afd->estados[i]);
        }
    }
}
