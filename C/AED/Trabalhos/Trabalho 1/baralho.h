#ifndef BARALHO_H
#define BARALHO_H

#define MAX_CARTAS 52
#define MAX_PILHAS 8
#define MAX_STRING 64

//estrutura tendo hierarquia e naipe da carta;
typedef struct carta
{
    //hierarquia, ordem da carta, valor, {A,2,3,4,5,6,7,8,9,Q,J,K}
    char hierarquia;
    //naipe, tipo da carta, o(ouros), c(coração), e(espadas) e p(paus);
    char naipe;
}Carta;

//estrutura Noh, para a criação das colunas de cartas e home e, ou free cells;
typedef struct noh
{
    //apontador para a estrutura carta;
    Carta* carta;
    //ponteiro de encadeação da pilha;
    struct noh* prox;
}Noh;

//estrutura para as colunas, do tipo pilha;
typedef struct pilha
{
    //tamanho da pilha;
    int tamanho;
    //topo da pilha;
    Noh* topo;
}Pilha;

typedef struct mesa
{
    //variaveis que mostram a quantidade de celulas livres, celulas cartas livres e se as celulas naipes estao cheias;
    int quantDeCartaLivres, quantDePilhasDeCartasLivres;
    //celulas livres que guardam uma carta cada, para usos quando for necessario;
    Carta* cartaLivres[4];
    //pilha de naipes, objetivo do jogo é completar as pilhas com cartas, e as celulas pilhas, aonde se tem o baralho, contendo as cartas;
    Pilha* celulasNaipes[4], *celulasPilhasDeCartas[8];
}Mesa;


///
/// \brief criaPilha, aloca um endereço de memoria para pilha, fazendo seu tamanho e topo serem 0 e nulo, respectivamente
/// \return Pilha inicializada
/// \pre nenhuma
/// \post nenhum
///
Pilha* criaPilha();

///
/// \brief criaNoh, aloca um endereço de memoria ao nó, tendo seus conteudos carta, o parametro carta, e o ponteiro prox, sendo nulo
/// \param carta, ponteiro da carta a ser inserida no nó
/// \return nó inicializado e contendo uma carta
/// \pre nenhuma
/// \post nenhuma
///
Noh* criaNoh(Carta* carta);

///
/// \brief inserirDoTipoPilha, insere no topo da pilha o nó alocado contendo uma carta
/// \param pilha, pilha aonde vai ser inserido no topo da mesma o nó com a carta
/// \param carta, carta que vai ser inserida no topo da pilha
/// \return pilha modificada tendo o novo topo o nó com a carta passado por parametro
/// \pre nenhuma
/// \post nenhuma
///
Pilha* inserirDoTipoPilha(Pilha* pilha, Carta* carta);

///
/// \brief removerDoTipoPilha, remove o nó do topo da pilha, avança o topo para o proximo elemento e retorna o nó removido
/// \param pilha, a pilha que vai ter seu topo removido e modificado
/// \return nó que antes era o topo, ele contendo a carta
/// \pre a pilha nao ser nula
/// \post a pilha perde o topo anterior
///
Noh *removerDoTipoPilha(Pilha* pilha);

///
/// \brief inverterParaPrintar, função usada para criar uma copia da pilha invertida, usada na hora de imprimir a pilha
/// \param nohs, nó cabeça da pilha que ira ser invertida
/// \return o nó cabeça(topo) da pilha invertida
/// \pre a pilha nao ser nula
/// \post nenhuma
///
Noh *inverterParaPrintar(Noh* nohs);

///
/// \brief criaCarta, aloca a carta e coloca nela o tipo do naipe e a hierarquia da carta
/// \param tipoDoNaipe, naipe que a carta pertence
/// \param valor, hierarquia(ordem) da carta
/// \return carta alocada e tendo naipe e valor
/// \pre nenhuma
/// \post nenhuma
///
Carta* criaCarta(int tipoDoNaipe, int valor);

///
/// \brief criaBaralho, aloca e cria cada uma das 52 cartas, tendo 13 de cada naipe(4)
/// \param baralho, vetor da estrutura carta
/// \pre nenhuma
/// \post vetor tem cartas alocadas
///
void criaBaralho(Carta* baralho[]);

///
/// \brief embaralhar, embaralha as cartas do vetor de cartas
/// \param baralho, vetor de cartas que vai ser embaralhado
/// \pre vetor de cartas tem que estar inicializado
/// \post baralho é embaralhado
///
void embaralhar(Carta* baralho[]);

///
/// \brief desalocar, libera a memoria alocada do(s) nó(s) alocados durante o tempo de execução
/// \param noh, nó que tera sua memoria desalocada
/// \pre nenhuma
/// \post memoria(conteudo) que havia no nó sera apagado
///
void desalocar(Noh* nohs);

#endif // BARALHO_H
