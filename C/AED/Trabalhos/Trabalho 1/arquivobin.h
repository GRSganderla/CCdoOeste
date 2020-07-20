#ifndef ARQUIVOBINN_H
#define ARQUIVOBINN_H

#include "operacoes.h"
#include<stdio.h>
#include<stdlib.h>

//estrutura para guardar todas as pilhas e cartas livres
typedef struct binario
{
    //vetor de variaveis que guardam os valores de cada uma das cartas livres
    int cartaslivre[4];
    //vetor que recebe o valor de cada uma das pilhas de naipes
    int celulasNaipes[4];
    //vetor que recebe o valor de cada uma das pilhas de cartas
    int celulasCartas[8];
    //final do arquivo
    int indF;
}ArqBinario;

//estrutura nó
typedef struct nohBin
{
    //conteudo que o nó guarda
    int info;
    //proximo nó
    int prox;
}NohBinario;

///
/// \brief carregarJogo, carrega a mesa do arquivo salvo e coloca seu conteudo em uma estrutura Mesa*
/// \param mesa, estrutura que irá guardar o conteudo do arquivo
/// \param nomeArq, nome do arquivo a ser carregado
/// \return 1 se não foi carregado o jogo, 0 se foi
/// \pre mesa tem que estar inicializada
/// \post mesa irá conter todas as pilhas e cartas livres salvas no arquivo
///
int carregarJogo(Mesa* mesa, char nomeArq[]);

///
/// \brief criaNohB, inicializa o nó, alocando-o e guardando um valor dentro dele
/// \param info, valor que o nó guardará
/// \return o novo nó inicializado contendo o valor
/// \pre nenhum
/// \post nenhum
///
NohBinario* criaNohB(int info);

///
/// \brief leituraDeMesa, lê o arquivo
/// \param binario, arquivo pronto para ser lido
/// \return a estrutura mesa lida do arquivo
/// \pre arquivo não vazio
/// \post nenhuma
///
ArqBinario* leituraDeMesa(FILE* binario);

///
/// \brief leituraDeNoh, lê o nó do arquivo
/// \param binario, arquivo a ser procurado e lido o nó
/// \param posicao, lugar do nó no arquivo
/// \return novo nó inicializado
/// \pre arquivo não vazio
/// \post nenhuma
///
NohBinario* leituraDeNoh(FILE* binario, int posicao);

///
/// \brief inserirCartaLivreNoArQ, insere nó nas cartas livres do arquivo
/// \param binario, arquivo a ser escrito a carta livre
/// \param id, indice a qual a está a carta livre
/// \param info, valor da carta a ser inserida
/// \pre arquivo inicializado
/// \post carta(nó) é inserida no arquivo
///
void inserirCelulaLivreNoArQ(FILE* binario, int id, int info);

///
/// \brief inserirCelulaCartaNoArQ, insere nó nas pilhas de cartas do arquivo
/// \param binario, arquivo a ser escrito
/// \param id, indice da pilha a ser escrita no arquivo
/// \param info, valor da carta a ser escrita
/// \pre arquivo incializado e carta não nula
/// \post nó escrito
///
void inserirCelulaCartaNoArQ(FILE* binario, int id, int info);

///
/// \brief inserirCelulaNaipeNoArQ, escreve o nó das pilhas naipes no arquivo
/// \param binario, arquivo a ser alterado
/// \param id, indice da pilha naipe
/// \param info, carta a ser inserida
/// \pre arquivo inicializado e carta não nula
/// \post nó é escrito no arquivo
///
void inserirCelulaNaipeNoArQ(FILE* binario, int id, int info);

///
/// \brief iniciaArQBin, inicializa a "mesa" alocando todo o seu conteudo
/// \param arqbin, arquivo a ser escrito
/// \pre nenhuma
/// \post "mesa" é colocada no arquivo
///
void iniciaArQBin(FILE* arqbin);

///
/// \brief salvarOJogo, mesa é copiado no arquivo binário, salvando o jogo
/// \param mesa, tem todas as operações e conteudos das pilhas e cartas livres
/// \param nomeArQ, como o arquivo será nomeado
/// \pre nenhuma
/// \post a mesa é guardada no arquivo, salvando o progresso do jogo
///
void salvarOJogo(Mesa* mesa, char nomeArQ[]);

#endif // ARQUIVOBINN_H
