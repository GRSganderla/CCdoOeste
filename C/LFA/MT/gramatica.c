#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#define MAX 100
#define MAXQ 20
#define MAXF 10
#define MAXA 20

#include "gramatica.h"

///
/// \brief alfabetoCMP, compara se o terminal passado pertence ao alfabeto que o MT lê
/// \param mt, struct que mantém consigo o alfabeto a ser comparado
/// \param terminal, char terminal que vai ser comparado
/// \return retorna 1 se pertence ao alfabeto e 0 se não pertence
/// \pre mt não vazia
/// \post nenhuma
///
int alfabetoCMP(MT mt, char terminal)
{
    int i;
    //percorre todo o alfabeto guardado em MT
    for(i =0; i < strlen(mt.alfa); i++)
        if(mt.alfa[i] == terminal)
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
Transicao* fazerTransicao(Estado* atual, char terminal)
{
    int i;
    //percorre ate o tamanho total de transições
    for(i = 0; i < atual->tamanhoT; i++)
    {
        if(atual->transicoes[i].terminal == terminal)
        {
            //retorna o proximo estado que o atual vai apos ter lido o terminal
            return &atual->transicoes[i];
        }
    }
    return NULL;
}

///
/// \brief ehFinal, compara os nomes do estado passado com o estado final
/// \param mt, struct que contem os estados finais
/// \param atual, estado que se quer saber se é final ou não
/// \return retorna 1 se o estado passado é o final ou retorna 0 se o estado não é o final
/// \pre struct mt ter os estados finais guardados
/// \post nenhum
///
int ehFinal(MT* mt, Estado* atual)
{
    int i;

    //percorre ate a quantidade total de estados finais e retorna se acho ou não
    for(i = 0; i < mt->tamanhoF; i++)
    {
        if(!strcmp(mt->final[i]->nome, atual->nome))
        {
            return 1;
        }
    }

    return 0;
}

///
/// \brief verificaPalavra, verifica em ordem cada letra da passada e verifica se é possivel ser processada
/// \param mt, struct que contem os estados, alfabetos e as transições de cada estado
/// \param str, palavra a ser processada e verifica se é aceita pelo MT
/// \param atual, estado a qual vai verificar se ele le o terminal da primeira letra da palavra
/// \return 1 se ela for aceita pelo MT, ou seja, foi processada totalmente ou retorna 0 se não foi processada corretamente
/// \pre mt ter sido inicializado
/// \post nenhum
///
int verificaPalavra(MT mt, char str[], Estado* atual, int pos)
{
    //se não tiver um estado atual
    if(!atual)
        return 0;

    char terminal = str[pos], aux[MAX];

    strncpy(aux, str, pos);
    aux[pos] = 0;

    printf("%s", aux);
    printf("[%s]", atual->nome);
    strcpy(aux, str+pos);
    printf("%s\n", aux);

    //se não pertence ao alfabeto
    if(!alfabetoCMP(mt, terminal)) return 0;

    Transicao* auxT = fazerTransicao(atual, terminal);
    //se não tem mais letras a serem verificadas, retorna se o estado é final ou não
    if(auxT == NULL) return ehFinal(&mt, atual);

    str[pos] = auxT->sobrescreve;

    //retorna e abre recursivamente a função para o estado proximo após a transição ser feita
    return verificaPalavra(mt, str, auxT->proximoEstado, pos+auxT->direcao);
}

///
/// \brief aceitaOUnao, função que printa se a palavra é aceita ou não pelo MT
/// \param mt, struct que contém todos os dados para a verificação e processamento da palavra entrada
/// \param str, palavra a ser processada pelo MT
/// \pre mt não tem estados e, ou, transições guardadas
/// \post nenhuma
///
void aceitaOUnao(MT mt, char str[])
{
    //verifica se a palavra é aceita ou não pelo MT
    if(verificaPalavra(mt, str, mt.estado, 1))
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