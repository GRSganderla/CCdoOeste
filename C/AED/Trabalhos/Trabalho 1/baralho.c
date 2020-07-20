#include<stdio.h>
#include<stdlib.h>

#include "baralho.h"

///
/// \brief criaPilha, aloca um endereço de memoria para pilha, fazendo seu tamanho e topo serem 0 e nulo, respectivamente
/// \return Pilha inicializada
/// \pre nenhuma
/// \post nenhum
///
Pilha* criaPilha()
{
    //cria uma nova pilha e aloca a memoria dessa pilha para o tamanho da estrutura de pilhas.
    Pilha* novo = (Pilha*)malloc(sizeof(Pilha));

    //a nova pilha tem seu tamanho e topo(cabeça) da pilha iguais a 0 e nulo, respectivamente
    novo->tamanho = 0;
    novo->topo = NULL;

    //retorna a nova pilha inicializada e com tamanho e topo, 0 e nulo.
    return novo;
}

///
/// \brief criaNoh, aloca um endereço de memoria ao nó, tendo seus conteudos carta, o parametro carta, e o ponteiro prox, sendo nulo
/// \param carta, ponteiro da carta a ser inserida no nó
/// \return nó inicializado e contendo uma carta
/// \pre nenhuma
/// \post nenhuma
///
Noh* criaNoh(Carta* carta)
{
    //cria um novo nó e aloca a quantidade de memoria do nó do tamanho da estrutura nó
    Noh* novo = (Noh*)malloc(sizeof(Noh));

    //a estrutura nó tem como conteudo interior a carta passada por parametro e ponteiro para o proximo nó como nulo
    novo->carta = carta;
    novo->prox = NULL;

    //retorna o novo nó inicializado com seus conteudos
    return novo;
}

///
/// \brief inserirDoTipoPilha, insere no topo da pilha o nó alocado contendo uma carta
/// \param pilha, pilha aonde vai ser inserido no topo da mesma o nó com a carta
/// \param carta, carta que vai ser inserida no topo da pilha
/// \return pilha modificada tendo o novo topo o nó com a carta passado por parametro
/// \pre nenhuma
/// \post nenhuma
///
Pilha* inserirDoTipoPilha(Pilha* pilha, Carta* carta)
{
    //se não tem carta, retorna a pilha inalterada
    if(!carta) return pilha;

    //se a pilha não tem topo
    if(!pilha->topo)
    {
        //o topo recebe um novo nó com a carta como conteudo
        pilha->topo = criaNoh(carta);
        //o tamanho da pilha é definido como 1
        pilha->tamanho = 1;
        //retorna a pilha alterada com um topo
        return pilha;
    }
    //nó auxiliar criado contendo a carta a ser inserido na pilha
    Noh* aux = criaNoh(carta);

    //o ponteiro proximo do nó auxiliar recebe o conteudo do topo da pilha
    aux->prox = pilha->topo;
    //o topo da pilha agora aponta para o nó auxiliar
    pilha->topo = aux;
    //tamanho da pilha é aumentado por 1
    pilha->tamanho +=1;
    //retorna a pilha alterada com o novo topo
    return pilha;
}

///
/// \brief removerDoTipoPilha, remove o nó do topo da pilha, avança o topo para o proximo elemento e retorna o nó removido
/// \param pilha, a pilha que vai ter seu topo removido e modificado
/// \return nó que antes era o topo, ele contendo a carta
/// \pre nenhuma
/// \post a pilha perde o topo anterior
///
Noh* removerDoTipoPilha(Pilha* pilha)
{
    //se não há pilha ou o topo da pilha, retorna vazio, nada a ser feito
    if(!pilha) return NULL;
    if(!pilha->topo) return NULL;

    //nó para receber o nó topo da pilha
    Noh* aux;
    aux = pilha->topo;

    //o topo da pilha é alterado para o proximo da pilha, mudando o topo e tirando o topo anterior da pilha
    pilha->topo = pilha->topo->prox;

    //o tamanho da pilha é diminuido por 1
    pilha->tamanho -=1;

    //remove o conteudo do proximo do nó auxiliar, mantendo só o nó
    aux->prox = NULL;

    //retorna o nó auxiliar, antes topo da pilha
    return aux;
}

///
/// \brief inverterParaPrintar, função usada para criar uma copia da pilha invertida, usada na hora de imprimir a pilha
/// \param nohs, nó cabeça da pilha que ira ser invertida
/// \return o nó cabeça(topo) da pilha invertida
/// \pre a pilha nao ser nula
/// \post nenhuma
///
Noh* inverterParaPrintar(Noh* nohs)
{
    //se não tem nó, retorna vazio
    if(!nohs) return NULL;

    //nó auxiliar contendo o conteudo do nó(nohs)
    Noh* nohAux = nohs;

    //pilha usada para inverter a sequencia encadeada dos nó, ela é inicializada
    Pilha* aux = criaPilha();

    //enquanto não for nulo o nó auxiliar
    while(nohAux)
    {
        //insere no topo da pilha aux o conteudo(carta) do nó
        aux = inserirDoTipoPilha(aux, nohAux->carta);
        //nó é avançado para o proximo nó
        nohAux = nohAux->prox;
    }
    //retorna o topo da pilha, sendo a cabeça e contendo os encadeamentos invertidos do nó(nohs)
    return aux->topo;
}

///
/// \brief criaBaralho, aloca e cria cada uma das 52 cartas, tendo 13 de cada naipe(4)
/// \param baralho, vetor da estrutura carta
/// \pre nenhuma
/// \post vetor tem cartas alocadas
///
void criaBaralho(Carta* baralho[])
{
    //variaveis para determinar o naipe, valor e posição da carta
    int tipoDoNaipe, qualOValor, posicao = 0;

    //para cada naipe(O,E,C,P) é determinado o valor da carta de 0 até 12
    for(tipoDoNaipe = 0; tipoDoNaipe<4; tipoDoNaipe++)
        for(qualOValor = 0;qualOValor <13;qualOValor ++)
        {
            //colocando a carta na posição no baralho que ela pertence
            baralho[posicao] = criaCarta(tipoDoNaipe, qualOValor);
            //incrementa a posição da carta no baralho
            posicao++;
        }
}

///
/// \brief criaCarta, aloca a carta e coloca nela o tipo do naipe e a hierarquia da carta
/// \param tipoDoNaipe, naipe que a carta pertence
/// \param valor, hierarquia(ordem) da carta
/// \return carta alocada e tendo naipe e valor
/// \pre nenhuma
/// \post nenhuma
///
Carta* criaCarta(int tipoDoNaipe, int valor)
{
    //criado uma nova estrutura carta e inicializada com quantidade de memoria do tamanho da estrutura carta
    Carta* novaCarta = (Carta*)malloc(sizeof(Carta));

    //a carta recebe o tipo do naipe e o tipo da ordem(rank, hierarquia ...) dela
    novaCarta->naipe = tipoDoNaipe;//pode ser 'Ouros', 'Espadas', 'Coração' e 'Paus'
    novaCarta->hierarquia = valor;//podendo ser A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q ou K, sendo essa a hierarquia

    //retorna a estrutura contendo o naipe e a ordem da carta
    return novaCarta;
}

///
/// \brief embaralhar, embaralha as cartas do vetor de cartas
/// \param baralho, vetor de cartas que vai ser embaralhado
/// \pre vetor de cartas tem que estar inicializado
/// \post baralho é embaralhado
///
void embaralhar(Carta* baralho[])
{
    //variavel para repetição
    int i;

    //enquanto i for menor que o número maximo de cartas(52)
    for(i=0;i<MAX_CARTAS;i++)
    {
        //variavel que recebe um numero aleatório com limite ate 52
        int j = rand()%52;
        //estrutura auxiliar que recebe a carta de posição atual
        Carta* aux = baralho[i];
        //carta atual é trocada pela carta de posição aleatória
        baralho[i] = baralho[j];
        //carta na posição aleatória troca com a carta atual
        baralho[j] = aux;
    }
}

///
/// \brief desalocar, libera a memoria alocada do(s) nó(s) alocados durante o tempo de execução
/// \param noh, nó que tera sua memoria desalocada
/// \pre nenhuma
/// \post memoria(conteudo) que havia no nó sera apagado
///
void desalocar(Noh* nohs)
{
    //nó auxiliar para desalocar os nós
    Noh* aux;

    //enquanto tiver nó para ser desalocado
    while(nohs)
    {
        //aux recebe o nó para desaloca-lo
        aux = nohs;
        //o nó para ser desalocado é avançado para o proximo
        nohs = nohs->prox;
        //desaloca o nó
        free(aux);
    }

    //libera(desaloca) o nó;
    free(nohs);
}


