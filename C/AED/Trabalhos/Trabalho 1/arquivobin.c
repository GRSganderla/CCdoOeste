#include "arquivobin.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

///
/// \brief carregarJogo, carrega a mesa do arquivo salvo e coloca seu conteudo em uma estrutura Mesa*
/// \param mesa, estrutura que irá guardar o conteudo do arquivo
/// \param nomeArq, nome do arquivo a ser carregado
/// \return 1 se não foi carregado o jogo, 0 se foi
/// \pre mesa tem que estar inicializada
/// \post mesa irá conter todas as pilhas e cartas livres salvas no arquivo
///
int carregarJogo(Mesa* mesa, char nomeArq[])
{
    FILE* binArq = fopen(nomeArq, "rb");

    //se o arquivo não pode ser aberto, retorna
    if(!binArq) return 1;

    ArqBinario* pilhaAux = leituraDeMesa(binArq);
    NohBinario* nohAux = NULL;
    Carta* cartaAux = NULL;

    int i, valorCarta,prox = 0;

    //para cada uma das celulas naipes e cartas livres
    for(i=0;i<4;i++)
    {
        //se tem algo na carta livre i
        if(pilhaAux->cartaslivre[i] != -1)
        {
            //lê o nó dessa carta e armazena ele em um nó auxiliar
            nohAux = leituraDeNoh(binArq, pilhaAux->cartaslivre[i]);

            //recebe o valor guardado no nó do arquivo e cria uma carta com esse valor
            valorCarta = nohAux->info;
            cartaAux = criaCarta(valorCarta/13, valorCarta%13);

            //coloca a carta criada na carta livre i da estrutura mesa e diminui o número de cartas livres desocupadas
            mesa->cartaLivres[i] = cartaAux;
            mesa->quantDeCartaLivres -=1;

            //libera o nó auxiliar
            free(nohAux);
        }
        //se tem um nó guardado na pilha de naipes i
        if(pilhaAux->celulasNaipes[i] != -1)
        {
            //lê esse nó e guarda em um nó auxiliar
            nohAux = leituraDeNoh(binArq, pilhaAux->celulasNaipes[i]);

            prox = 0;

            //enquanto tiver um nó proximo
            while(prox != -1)
            {
                //recebe o valor da carta e cria uma carta com esse valor
                valorCarta = nohAux->info;
                cartaAux = criaCarta(valorCarta/13, valorCarta%13);

                //insere na pilha de naipes i a carta criada
                mesa->celulasNaipes[i] = inserirDoTipoPilha(mesa->celulasNaipes[i], cartaAux);

                //atualiza o nó para o proximo
                prox = nohAux->prox;

                //libera o nó
                free(nohAux);

                //lê o proximo nó
                nohAux = leituraDeNoh(binArq, prox);
            }
        }
    }
    //para cada uma das pilhas de cartas
    for(i=0; i<8; i++)
    {
        //se tem um nó guardado na pilha i
        if(pilhaAux->celulasCartas[i] != -1)
        {
            //lê o nó guardado e guarda ele em um nó auxiliar
            nohAux = leituraDeNoh(binArq, pilhaAux->celulasCartas[i]);

            prox = 0;

            //enquanto tiver um nó proximo
            while(prox != -1)
            {
                //recebe o valor da carta e cria uma carta
                valorCarta = nohAux->info;
                cartaAux = criaCarta(valorCarta/13, valorCarta%13);

                //insere na pilha de cartas i a carta criada
                mesa->celulasPilhasDeCartas[i] = inserirDoTipoPilha(mesa->celulasPilhasDeCartas[i], cartaAux);

                //verifica se tem um nó proximo
                prox = nohAux->prox;

                //libera o nó auxiliar
                free(nohAux);

                //lê o proximo nó
                nohAux =leituraDeNoh(binArq, prox);

            }
            //atualiza o número de pilhas de cartas vazias
            mesa->quantDePilhasDeCartasLivres--;
        }
    }

    printf("                          Jogo Carregado!\n");

    //fecha o arquivo
    fclose(binArq);

    getch();
    return 0;
}

///
/// \brief criaNohB, inicializa o nó, alocando-o e guardando um valor dentro dele
/// \param info, valor que o nó guardará
/// \return o novo nó inicializado contendo o valor
/// \pre nenhum
/// \post nenhum
///
NohBinario* criaNohB(int info)
{
    //cria e inicializa uma estrutura do tipo nó
    NohBinario* novo = (NohBinario*)malloc(sizeof(NohBinario));

    //nó rebece o valor que irá guardar e tem seu proximo inicializado
    novo->info = info;
    novo->prox = -1;

    //retorna esse novo nó
    return novo;
}

///
/// \brief leituraDeMesa, lê o arquivo
/// \param binario, arquivo pronto para ser lido
/// \return a estrutura mesa lida do arquivo
/// \pre arquivo não vazio
/// \post nenhuma
///
ArqBinario* leituraDeMesa(FILE* binario)
{
    //cria e inicializa uma estrutura de mesa
    ArqBinario* mesa = (ArqBinario*)malloc(sizeof(ArqBinario));

    //posiciona no começo do arquivo
    fseek(binario, 0, SEEK_SET);

    //lê a estrutura mesa
    fread(mesa, sizeof(ArqBinario), 1, binario);

    //retorna essa nova estrutura
    return mesa;
}

///
/// \brief leituraDeNoh, lê o nó do arquivo
/// \param binario, arquivo a ser procurado e lido o nó
/// \param posicao, lugar do nó no arquivo
/// \return novo nó inicializado
/// \pre arquivo não vazio
/// \post nenhuma
///
NohBinario* leituraDeNoh(FILE* binario, int posicao)
{
    //cria e inicializa uma estrutura de nó
    NohBinario* nois = (NohBinario*)malloc(sizeof(NohBinario));

    //determina o lugat aonde o nó será buscado

    //posiciona na posição do nó
    fseek(binario, sizeof(ArqBinario) + sizeof(NohBinario)*posicao , SEEK_SET);

    //lê o nó
    fread(nois, sizeof(NohBinario), 1, binario);

    //retorna o novo nó lido
    return nois;
}

///
/// \brief inserirCartaLivreNoArQ, insere nó nas cartas livres do arquivo
/// \param binario, arquivo a ser escrito a carta livre
/// \param id, indice a qual a está a carta livre
/// \param info, valor da carta a ser inserida
/// \pre arquivo inicializado
/// \post carta(nó) é inserida no arquivo
///
void inserirCartaLivreNoArQ(FILE* binario, int id, int info)
{
    //lê a mesa do arquivo
    ArqBinario* arqAux = leituraDeMesa(binario);
    NohBinario* nohAux = criaNohB(info);

    //proximo do nó é colocado como cabeça das cartas livres
    nohAux->prox = arqAux->cartaslivre[id];

    //posição do nó

    //procura a posição do no e escreve o nó no arquivo
    fseek(binario, sizeof(ArqBinario) + sizeof(NohBinario)*arqAux->indF, SEEK_SET);
    fwrite(nohAux, sizeof(NohBinario), 1, binario);

    //muda a cabeça das cartas livres e o final do arquivo
    arqAux->cartaslivre[id] = arqAux->indF;
    arqAux->indF++;

    //procura e escreve a pilha modificada
    fseek(binario, 0, SEEK_SET);
    fwrite(arqAux, sizeof(ArqBinario), 1, binario);

    //libera o nó auxiliar usado
    free(nohAux);
}

///
/// \brief inserirCelulaCartaNoArQ, insere nó nas pilhas de cartas do arquivo
/// \param binario, arquivo a ser escrito
/// \param id, indice da pilha a ser escrita no arquivo
/// \param info, valor da carta a ser escrita
/// \pre arquivo incializado e carta não nula
/// \post nó escrito
///
void inserirPilhaCartaNoArQ(FILE* binario, int id, int info)
{
    //lê a mesa do arquivo
    ArqBinario* arqAux = leituraDeMesa(binario);
    NohBinario* nohAux = criaNohB(info);

    //proximo do nó é a cabeça das pilhas
    nohAux->prox = arqAux->celulasCartas[id];

    //posição do nó

    //procura a posição do nó e escreve o nó
    fseek(binario, sizeof(ArqBinario) + sizeof(NohBinario)*arqAux->indF , SEEK_SET);
    fwrite(nohAux, sizeof(NohBinario), 1, binario);

    //atualiza a cabeça das pilhas e do final do arquivo
    arqAux->celulasCartas[id] = arqAux->indF;
    arqAux->indF++;

    //escreve no arquivo a mesa
    fseek(binario, 0, SEEK_SET);
    fwrite(arqAux, sizeof(ArqBinario), 1, binario);

    //libera o nó auxiliar
    free(nohAux);
}

///
/// \brief inserirCelulaNaipeNoArQ, escreve o nó das pilhas naipes no arquivo
/// \param binario, arquivo a ser alterado
/// \param id, indice da pilha naipe
/// \param info, carta a ser inserida
/// \pre arquivo inicializado e carta não nula
/// \post nó é escrito no arquivo
///
void inserirPilhaNaipeNoArQ(FILE* binario, int id, int info)
{
    //lê a mesa do arquivo
    ArqBinario* arqAux = leituraDeMesa(binario);
    NohBinario* nohAux = criaNohB(info);

    //proximo do nó é a cabeça das pilhas naipes
    nohAux->prox = arqAux->celulasNaipes[id];

    //posição do nó no arquivo

    //procura a posição e escreve o nó no arquivo
    fseek(binario, sizeof(ArqBinario) + sizeof(NohBinario)*arqAux->indF, SEEK_SET);
    fwrite(nohAux, sizeof(NohBinario), 1, binario);

    //atualiza a cabeça das pilhas naipes e do final do arquivo
    arqAux->celulasNaipes[id] = arqAux->indF;
    arqAux->indF++;

    //escreve a mesa modificada no arquivo
    fseek(binario, 0, SEEK_SET);
    fwrite(arqAux, sizeof(ArqBinario), 1, binario);

    //libera o nó auxiliar
    free(nohAux);
}

///
/// \brief iniciaArQBin, inicializa a "mesa" alocando todo o seu conteudo
/// \param arqbin, arquivo a ser escrito
/// \pre nenhuma
/// \post "mesa" é colocada no arquivo
///
void iniciaArQBin(FILE* arqbin)
{
    //cria e aloca uma estrutura de pilhas e cartas livres
    ArqBinario* novoArq = (ArqBinario*)malloc(sizeof(ArqBinario));

    int i;

    //para cada uma das pilhas naipes e cartas livres
    for(i=0; i < 4; i++)
    {
        //inicializa elas
        novoArq->cartaslivre[i] = -1;
        novoArq->celulasNaipes[i] = -1;
    }

    //para cada uma das pilhas de cartas
    for(i=0;i<8;i++)
    {
        //inicializa elas
        novoArq->celulasCartas[i] = -1;
    }

    //indice do final do arquivo é inicializado
    novoArq->indF = 0;

    //escreve no topo do arquivo a estrutura de pilhas e cartas livres
    fseek(arqbin, 0, SEEK_SET);
    fwrite(novoArq, sizeof(ArqBinario), 1, arqbin);

    //libera a estrutura
    free(novoArq);
}

///
/// \brief criaCartaBinEInsere, determina o valor da carta e a insere no arquivo a partir do lugar dela na mesa
/// \param arqBin, arquivo a ser inserido o valor
/// \param topo, carta que pertence a Mesa*, ela pode ser das cartas livres ou do topo das pilhas naipes ou pilhas de cartas
/// \param indColuna, posição das cartas livres ou coluna das pilhas aonde a carta pertencia
/// \param tipoDeCarta, tipo de carta a ser inserida no arquivo
/// \pre arquivo não vazio
/// \post arquivo possuirá as novas cartas
///
void criaCartaBinEInsere(FILE* arqBin, Carta* topo, int indColuna, int tipoDeCarta)
{
    int valorDaCarta = 0;

    //determina o valor total da carta
    valorDaCarta = topo->naipe*13 + topo->hierarquia;

    //se é para inserir nas cartas livres
    if(tipoDeCarta == 1)
    {
        //insere no arquivo o valor da carta total
        inserirCartaLivreNoArQ(arqBin, indColuna, valorDaCarta);
    }
    //se é para inserir nas pilhas naipes
    if(tipoDeCarta == 2)
    {
        //insere no arquivo o valor da carta total
        inserirPilhaNaipeNoArQ(arqBin, indColuna, valorDaCarta);
    }
    //se é para inserir nas pilhas de cartas
    if(tipoDeCarta == 3)
    {
        //insere no arquivo o valor da carta total
        inserirPilhaCartaNoArQ(arqBin, indColuna, valorDaCarta);
    }
}

///
/// \brief salvarOJogo, mesa é copiado no arquivo binário, salvando o jogo
/// \param mesa, tem todas as operações e conteudos das pilhas e cartas livres
/// \param nomeArQ, como o arquivo será nomeado
/// \pre nenhuma
/// \post a mesa é guardada no arquivo, salvando o progresso do jogo
///
void salvarOJogo(Mesa* mesa, char nomeArQ[])
{
    FILE* arqbin = fopen(nomeArQ, "wb+");

    Noh* nohAux = NULL;

    Carta* carta = NULL;

    int i, valorDaCarta = 0;

    //inicializa a estrutura que será escrita dentro do arquivo
    iniciaArQBin(arqbin);

    //para cada uma das 4 pilhas de naipes e das 4 cartas livres
    for(i=0; i < 4; i++)
    {
        //verifica se tem uma carta na coluna i das cartas livres
        if(mesa->cartaLivres[i])
        {
            carta = mesa->cartaLivres[i];

            valorDaCarta = carta->naipe*13 + carta->hierarquia;
            //função que determina o valor da carta e a insere no tipo de lugar
            inserirCartaLivreNoArQ(arqbin, i, valorDaCarta);
        }

        //nó recebe a cabeça do topo da pilha do naipe i
        nohAux = mesa->celulasNaipes[i]->topo;

        //enquanto tiver um nó na pilha naipe
        while(nohAux)
        {
            carta = nohAux->carta;

            valorDaCarta = carta->naipe*13 + carta->hierarquia;
            //função que determina o valor da carta e a insere no tipo de lugar
            inserirPilhaNaipeNoArQ(arqbin, i, valorDaCarta);

            //avança para o proximo nó da pilha naipe
            nohAux = nohAux->prox;
        }
    }

    for(i = 0; i < 8; i++)
    {
        //nó recebe o topo da pilha de cartas da coluna i
        nohAux = mesa->celulasPilhasDeCartas[i]->topo;

        //enquanto tem algo no nó
        while(nohAux)
        {
            carta = nohAux->carta;

            valorDaCarta = carta->naipe*13 + carta->hierarquia;
            //determina o valor da carta e a insere no tipo de lugar
            inserirPilhaCartaNoArQ(arqbin, i, valorDaCarta);

            //avança para o proximo nó
            nohAux = nohAux->prox;
        }
    }

    printf("                            Jogo Salvo!\n");

    //fecha o arquivo
    fclose(arqbin);
}
