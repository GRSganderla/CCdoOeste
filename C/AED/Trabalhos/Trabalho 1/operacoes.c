#include "operacoes.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

///
/// \brief mostrarAjuda, mostra as regras do jogo e todos os comandos possiveis
/// \pre nenhuma
/// \post nenhuma
///
void mostrarAjuda()
{
    char c;

    //limpa a tela e pergunta qual é a ajuda
    system("CLS");
    printf("    Se deseja saber as regras do jogo digite 'R' ou se quer saber os comandos digite 'C'\n");

    //scaneia qual o tipo de ajuda requerida
    scanf("%c", &c);

    //se for para saber os comandos
    if(c == 'C')
    {
        printf("    Comandos:\n");
        printf("        -Para salvar:\n salvar 'nome do arquivo'\n");
        printf("        -Para mover uma carta para outra coluna:\n      'quantidade de cartas''coluna atual' = 'coluna desejada'\n");
        printf("        -Para colocar a carta nas celulas de naipes:\n      !'coluna da carta desejada'\n");
        printf("        -Para colocar a carta em uma das celulas livres:\n      +'coluna da carta desejada' > 'coluna da celula livre que queira colocar'\n");
        printf("        -Para tirar uma carta de uma das celulas livre e colocar na mesa:\n         -'coluna da celula livre da carta desejada' > 'coluna que quer colocar essa carta'\n");
        printf("        -Para acabar o jogo: '*'\n");
    }
    //se for para saber quais são as regras
    if(c == 'R')
    {
        printf("    Regras:\n");
        printf("        -As cartas devem ser agrupadas em ordem decrescente, de cima para baixo, sendo a ordem:\n       A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K.\n");
        printf("        -As cartas devem ter uma cor e naipe diferente da proxima carta, sendo a cor definida pelos os naipes:\n        E(espadas) e P(paus) tem cor azul, enquanto C(copas) e O(ouros) tem cor vermelha\n");
        printf("        -As celulas de A a D na parte superior sao celulas para colocar uma carta, se eh oque deseja:\n         Ela pode guardar a carta ate ter a necessidade de usar essa carta.\n");
        printf("        -As celulas O E C P na parte superior sao celulas para discartar a carta, sendo o objetivo do jogo:\n       Completar as 4 celulas com todas as cartas em sequencia de ordem crescente do mesmo naipe, comecando com A ate o K.\n");
        printf("        -Os indices na parte de baixo de A ate H, indicam as colunas das cartas,\n      Use-as para os comandos, que estes podem ser explicado usando o comando 'C', la contem os comandos validos para o jogo!\n");
    }
}

///
/// \brief casoCartaLivre, caso queira pegar uma carta de uma pilha I e colocar em uma celula livre F
/// \param mesa, mesa que contém os dados de cada operação feita, cada pilha e celula
/// \param colunaI, coluna inicial, ou coluna origem da carta, da onde ela será tirada
/// \param colunaD, coluna destino da carta, aonde a carta irá ocupar se a operação for feita
/// \pre o topo da pilha colunaI não pode ser nulo
/// \post a carta será tirada do topo da pilha I e colocada na celula D, que não será mais vazia
///
void casoCartaLivre(Mesa* mesa, char colunaI, char colunaD)
{
    //se a pilha da coluna de saida não está vazia
    if(mesa->celulasPilhasDeCartas[colunaI%65]->topo)
    {
        //se a coluna de cartas livres tem uma carta ja ocupando-a, avisa que ta ocupado e não faz nada
        if(mesa->cartaLivres[colunaD%65])
            printf("Ja esta ocupado!\n");
        //se a coluna destino de cartas livres está vazia
        else
        {
            //cria um nó e faz ele receber o nó retirado da pilha de carta
            Noh* nois = removerDoTipoPilha(mesa->celulasPilhasDeCartas[colunaI%65]);

            //coloca a carta do nó na coluna escolhida nas cartas livres
            mesa->cartaLivres[colunaD%65] = nois->carta;

            //diminui a quantidade de cartas livres
            mesa->quantDeCartaLivres -= 1;

            //se a pilha de carta daonde a carta saiu ficou vazia
            if(!(mesa->celulasPilhasDeCartas[colunaI%65]->tamanho))
            {
                //aumenta a quantidade de pilha de cartas vazia
                mesa->quantDePilhasDeCartasLivres++;
            }
            //libera o nó usado
            free(nois);
        }
    }//se a pilha de cartas está vazia, imprime um aviso
    else
        printf("Nao tem nenhuma carta na pilha para ser colocada nas cartas livres!\n");
}

///
/// \brief casoCelulaNaipe, caso queira discartar a carta, colocando nas pilhas de naipe
/// \param mesa contém as pilhas de cartas, que será alterada após a operação
/// \param colunaI, coluna inicial da carta, ou coluna origem
/// \pre a carta do topo da pilha colunaI não pode ser nula e a pilha naipe tem que ser inicializada
/// \post a carta colocada na pilha do respectivo naipe não poderá ser mais utilizada
///
void casoPilhaNaipe(Mesa* mesa, char colunaI)
{
    //se tem uma carta ocupando a pilha de cartas da coluna escolhida
    if(mesa->celulasPilhasDeCartas[colunaI%65]->topo)
    {
        //cria dois nós, que recebem o topo da pilha de carta da coluna I e o topo da pilha do respectivo naipe da carta
        Noh* nohI = mesa->celulasPilhasDeCartas[colunaI%65]->topo;
        int naipe = nohI->carta->naipe;
        Noh* nois = mesa->celulasNaipes[naipe]->topo;
        Noh* uso = NULL;

        //se a carta é Ás e a pilha do naipe está vazia, ou, a pilha de naipes não está vazia e a carta da coluna I é sequencia
        if((nohI->carta->hierarquia == 0 && !nois )|| (nois && nohI->carta->hierarquia == nois->carta->hierarquia+1))
        {
            //nó recebe o topo removido da pilha de carta da coluna I
            uso = removerDoTipoPilha(mesa->celulasPilhasDeCartas[colunaI%65]);

            //a pilha do respectivo naipe recebe a carta do topo removido
            mesa->celulasNaipes[naipe] = inserirDoTipoPilha(mesa->celulasNaipes[naipe], uso->carta);

            //se a pilha de carta ficou vazia após ter o topo retirado, aumenta o número de pilhas de cartas livres
            if(mesa->celulasPilhasDeCartas[colunaI%65]->tamanho == 0)
                mesa->quantDePilhasDeCartasLivres++;

            //libera os nós usados
            free(nois);
            free(uso);
            free(nohI);
        }
        //se a carta não atende os requisitos de ser a primeira carta(A) ou ser a sequencia da carta ocupante do naipe
        else
        {
            printf("A Carta");
            imprimeCarta(nohI->carta);
            printf(" nao pode ser coloca na celulas de naipes, verifique se as condicoes para ser colocada estao de ordem com as regras!\n");
        }
    }//se a pilha de cartas da coluna I não tem nenhuma carta
    else
        printf("A Coluna(%c) esta vazia!\n", colunaI);
}

///
/// \brief tiraDaCelulaLivre, função para tirar a carta da celula livre inicial e colocar nas pilhas de carta destino
/// \param mesa
/// \param celulaI, celula livre que a carta está localizada
/// \param colunaD, coluna aonde a carta irá ser colocada
/// \pre a celulaI não pode ser vazia
/// \post a carta será tirada da carta livre, que se tornará vazia, e ocupara o topo da pilha de destino
///
void tiraDaCartaLivre(Mesa* mesa, char cartaL, char colunaD)
{
    //se tem uma carta ocupando as cartas livres na posição escolhida
    if(mesa->cartaLivres[cartaL%65])
    {
        //recebe a carta ocupando aquela posição
        Carta* cartaI = mesa->cartaLivres[cartaL%65], *cartaF = NULL;

        //nó que recebe o topo da pilha de carta escolhida para receber a carta das cartas livres
        Noh* nois = mesa->celulasPilhasDeCartas[colunaD%65]->topo;

        //se a pilha tem um topo, a cartaF recebe a carta que está naquela topo
        if(nois)
            cartaF = nois->carta;

        //se a pilha de carta da coluna escolhida é nula, ou, se a carta de saida e a carta da coluna escolhida seguem a regra
        if(!(nois) || ((cartaI->naipe%2 != cartaF->naipe%2) && (cartaF->hierarquia == cartaI->hierarquia+1)))
        {
            //a pilha escolhida recebe a carta das cartas livres
            mesa->celulasPilhasDeCartas[colunaD%65] = inserirDoTipoPilha(mesa->celulasPilhasDeCartas[colunaD%65], cartaI);

            //a antiga posição da carta nas cartas livres se torna vazia
            mesa->cartaLivres[cartaL%65] = NULL;

            //o número de cartas livres vazias aumenta
            mesa->quantDeCartaLivres += 1;

            //se a pilha de cartas que recebeu a carta era vazia, diminui o número de pilhas de cartas vazias
            if(!nois)
                mesa->quantDePilhasDeCartasLivres -= 1;
        }//se não cumpre a regras de a pilha de cartas ser nula ou as cartas seguirem as regras
        else
        {
            //imprime um aviso
            printf("As Cartas");
            imprimeCarta(cartaI);
            printf(" e ");
            imprimeCarta(cartaF);
            printf(" nao cumpre as regras, eles tem que ser sequencia e de naipes diferentes!\n");
        }
    }else//se não tem uma carta ocupando a posição
        printf("A coluna de cartas livres não tem nenhuma carta a ocupando!\n");
}

///
/// \brief moverParaTalPilha, função para colocar uma carta em outra coluna de cartas
/// \param mesa, guarda as pilhas, operações e cartas do jogo
/// \param colunaI, coluna origem da carta
/// \param quantDeMovimentos, quantidade de cartas que serão movidas
/// \param colunaF, coluna destino da carta
/// \pre a carta no topo da pilha I não pode ser nula
/// \post a carta sairá do topo da pilha I e ocupara o topo da pilha F
///
void moverParaTalPilha(Mesa* mesa, char colunaI, int quantDeMovimentos, char colunaF)
{
    //se não tem movimentos a ser feitos
    if(quantDeMovimentos == 0) return;

    //se a pilha de cartas de origem da(s) carta(s) a ser movida(s) não é vazia
    if(mesa->celulasPilhasDeCartas[colunaI%65]->topo)
    {
        //variavel para ver a regra do limite de cartas a serem movidas
        int pode = (mesa->quantDeCartaLivres+1) * pow( 2, mesa->quantDePilhasDeCartasLivres);

        //se a quantidade de movimentos selecionada está dentro dos limites
        if(quantDeMovimentos <= pode)
        {
            //nó que recebe o topo da pilha de carta da origem
            Noh* nohI = mesa->celulasPilhasDeCartas[colunaI%65]->topo;

            int movimentoNPossivel = 0;

            int i = 1;

            //verificação de todas as cartas a serem movidas, se cumprem a regra
            while(i < quantDeMovimentos)
            {
                //para o caso de ter mais de um movimento, se tem carta no nó atual e no proximo
                if(nohI && nohI->prox)
                {
                    //se as duas cartas do nó seguem a regra de serem sequencias e naipes diferentes
                    if((nohI->carta->naipe%2 != nohI->prox->carta->naipe%2) && (nohI->prox->carta->hierarquia == nohI->carta->hierarquia+1))
                    {
                        //o movimento é possivel
                        movimentoNPossivel = 0;
                        //avança para o proximo nó
                        nohI = nohI->prox;
                        i++;
                    }
                    else//se as cartas não cumprem as regras
                    {
                        //movimento não possivel
                        movimentoNPossivel = 1;
                        break;
                    }
                }else//se não tem um nó atual ou um nó proximo
                {
                    //movimento não possivel
                    movimentoNPossivel = 1;
                    break;
                }
            }

            //se o movimento for possivel
            if(!movimentoNPossivel)
            {
                //recebe a carta da coluna escolhida e tem um nó que recebe o topo da pilha do destino da carta a ser movida
                Carta* cartaI = nohI->carta;
                Noh* nohF = mesa->celulasPilhasDeCartas[colunaF%65]->topo;
                Noh* nohAux = NULL;

                Carta* cartaF = NULL;
                int i;

                //se o tem uma carta no topo da pilha de cartas de destino, recebe essa carta
                if(nohF)
                    cartaF = mesa->celulasPilhasDeCartas[colunaF%65]->topo->carta;

                //se a pilha de cartas do destino da carta está vazia, ou, se a cartaI e a cartaF cumprem a regra
                if(!(nohF) || ((cartaI->naipe%2 != cartaF->naipe%2) && (cartaF->hierarquia == cartaI->hierarquia+1)))
                {
                    //se a pilha de cartas de destino era vazia, diminui a quantidade de pilhas de cartas vazias
                    if(mesa->celulasPilhasDeCartas[colunaF%65]->tamanho == 0)
                        mesa->quantDePilhasDeCartasLivres--;

                    Pilha* aux = criaPilha();

                    //se a quantidade de movimentos é so uma
                    if(quantDeMovimentos == 1)
                    {
                        //remove a carta do topo da pilha de origem da carta e a coloca na pilha de destino
                        nohAux = removerDoTipoPilha(mesa->celulasPilhasDeCartas[colunaI%65]);
                        mesa->celulasPilhasDeCartas[colunaF%65] = inserirDoTipoPilha(mesa->celulasPilhasDeCartas[colunaF%65], nohAux->carta);
                        free(nohAux);
                    }
                    else//se for mais que um o número de movimentos
                    {
                        //para cada movimento
                        for(i = 0; i < quantDeMovimentos; i++)
                        {
                            //remove a carta do topo da pilha de carta de origem e insere em uma pilha auxiliar
                            nohF = removerDoTipoPilha(mesa->celulasPilhasDeCartas[colunaI%65]);
                            aux = inserirDoTipoPilha(aux, nohF->carta);
                            free(nohF);
                        }
                        //para cada movimento
                        for(; i > 0; i--)
                        {
                            //remove a carta da pilha auxiliar e coloca na pilha de cartas de destino
                            nohF = removerDoTipoPilha(aux);
                            mesa->celulasPilhasDeCartas[colunaF%65] = inserirDoTipoPilha(mesa->celulasPilhasDeCartas[colunaF%65], nohF->carta);
                            free(nohF);
                        }
                    }
                    //se a pilha de cartas de origem ficou vazia, aumenta o número de pilhas de cartas vazias
                    if(mesa->celulasPilhasDeCartas[colunaI%65]->tamanho == 0)
                        mesa->quantDePilhasDeCartasLivres++;

                    free(aux);
                }else
                    printf("A pilha de destino da(s) carta(s) tem que estar dentro das regras, seja o destino vazio ou sequencial e de naipe diferente!\n");
            }else
                printf("O movimento das cartas nao foi possivel!\n");
        }else
            printf("A quantidade de cartas nao pode ser movida\n");
    }else
        printf("Nao existe carta na pilha de origem a ser movida!\n");
}
