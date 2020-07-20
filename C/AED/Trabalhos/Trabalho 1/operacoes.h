#ifndef OPERACOES_H
#define OPERACOES_H

#include "mesa.h"

///
/// \brief mostrarAjuda, mostra as regras do jogo e todos os comandos possiveis
/// \pre nenhuma
/// \post nenhuma
///
void mostrarAjuda();

///
/// \brief nohVazio, verifica e retorna 1 ou 0, dependendo se o nó está vazio ou se não está vazio
/// \param alvo, nó que sera verificado o conteudo
/// \return 1 se for vazio, 0 se não for vazio
/// \pre nenhuma
/// \post nenhuma
///
int nohVazio(Noh* alvo);

///
/// \brief casoCartaLivre, caso queira pegar uma carta de uma pilha I e colocar em uma celula livre F
/// \param mesa, mesa que contém os dados de cada operação feita, cada pilha e celula
/// \param colunaI, coluna inicial, ou coluna origem da carta, da onde ela será tirada
/// \param colunaD, celula destino da carta, aonde a carta irá ocupar se a operação for feita
/// \pre o topo da pilha colunaI não pode ser nulo
/// \post a carta será tirada do topo da pilha I e colocada na celula D, que não será mais vazia
///
void casoCartaLivre(Mesa* mesa, char colunaI, char colunaD);

///
/// \brief casoCelulaNaipe, caso queira discartar a carta, colocando nas pilhas de naipe
/// \param mesa contém as pilhas de cartas, que será alterada após a operação
/// \param colunaI, coluna inicial da carta, ou coluna origem
/// \pre a carta do topo da pilha colunaI não pode ser nula e a pilha naipe tem que ser inicializada
/// \post a carta colocada na pilha do respectivo naipe não poderá ser mais utilizada
///
void casoPilhaNaipe(Mesa* mesa, char colunaI);

///
/// \brief tiraDaCartaLivre, função para tirar a carta da celula livre inicial e colocar nas pilhas de carta destino
/// \param mesa
/// \param celulaI, celula livre que a carta está localizada
/// \param colunaD, coluna aonde a carta irá ser colocada
/// \pre a celulaI não pode ser vazia
/// \post a carta será tirada da celula livre, que se tornará vazia, e ocupara o topo da pilha de destino
///
void tiraDaCartaLivre(Mesa* mesa, char cartaL, char colunaD);

///
/// \brief moverParaTalPilha, função para colocar uma carta em outra coluna de cartas
/// \param mesa, guarda as pilhas, operações e cartas do jogo
/// \param colunaI, coluna origem da carta
/// \param quantDeMovimentos, quantidade de cartas que serão movidas
/// \param colunaF, coluna destino da carta
/// \pre a carta no topo da pilha I não pode ser nula
/// \post a carta sairá do topo da pilha I e ocupara o topo da pilha F
///
void moverParaTalPilha(Mesa* mesa, char colunaI, int quantDeMovimentos, char colunaF);

///
/// \brief vitoria, verifica se todas as pilhas de naipes estão cheias, ou seja, contendo 13 cartas cada uma
/// \param mesa, estrutura que contém as informações sobre a pilha estar cheia ou não
/// \return 1 se estiver todas cheias, 0 se não
/// \pre mesa inicializada
/// \post nenhuma
///
int vitoria(Mesa* mesa);

#endif // OPERACOES_H
