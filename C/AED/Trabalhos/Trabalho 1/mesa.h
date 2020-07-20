#ifndef MESA_H
#define MESA_H

#include "baralho.h"

///
/// \brief imprimeCarta, imprime o valor e naipe da carta, sendo a carta imprimida do tipo '|valor,naipe|'
/// \param carta, estrutura do tipo carta, tendo consigo o seu valor e naipe
/// \pre a carta esteja nos padrões do tipo de carta usado para imprimir
/// \post nenhuma
///
void imprimeCarta(Carta* carta);

///
/// \brief criaMesa, cria e inicializa uma estrutura Mesa* alocando memória para todo o seu conteudo
/// \return retorna a nova mesa com suas pilhas cartas, pilhas naipes, celulas livres e variaveis inicializadas como nulo
/// \pre nenhuma
/// \post nenhuma
///
Mesa* criaMesa();

///
/// \brief comecarJogo, cria o baralho, embaralha ele e distrui as cartas para cada uma das pilhas de cartas
/// \param mesa inicializa e contendo pilhas de cartas, pilhas de naipes e celulas livres vazias
/// \pre mesa estar inicializada
/// \post as pilhas de cartas agora contém as 52 cartas do baralho
///
void comecarJogo(Mesa* mesa);

///
/// \brief vazia, verifica se a pilha esta vazia, ou seja, não tem topo
/// \param pilha que será verifica se está vazia
/// \return o inverso do topo da pilha, se tem algo no topo, volta 0, se não tem, volta 1
/// \pre pilha inicializada
/// \post nenhuma
///
int vazia(Pilha* pilha);

///
/// \brief mostrarMesa, limpa a tela e imprime em sequencia: os indicadores, as celulas livres, as pilhas naipes e as pilhas cartas
/// \param mesa, contem os ponteiros para as pilhas de cartas, pilhas de naipes e celulas livres, para imprimir os conteudo
/// \pre mesa inicializada e contendo elementos
/// \post nenhuma
///
void mostrarMesa(Mesa* mesa);

///
/// \brief operacao, verifica qual é o tipo do comando que sera executado
/// \param leituraCMD, string contendo a linha de comando
/// \return o número da determinada operação a ser feita
/// \pre nenhuma
/// \post nenhuma
///
int operacao(char leituraCMD[]);

///
/// \brief operacoes, busca qual o tipo de operação e faz a chamada para essa operação ser feita
/// \param mesa, guarda e guardará qualquer operação a ser feita
/// \return se a operação foi feita ou não
/// \pre a mesa ser inicializada
/// \post a mesa vai ter seu conteudo alterado dependendo do tipo de operação feita
///
int operacoes(Mesa* mesa);

#endif // MESA_H
