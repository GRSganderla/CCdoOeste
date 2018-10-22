#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Arquivos.h"


///
/// \brief overflow, funcao que testa se o nó atual esta com o numero de chaves com o maximo possivel de chaves
/// \param r, nó atual que contem o numero de chaves
/// \return 1, se tiver overflow, ou, 0, se n tiver overflow
/// \pre nenhuma
/// \post nenhuma
///
int overflow(ArvoreB* r);

///
/// \brief vazia, testa se o nó é vazio
/// \param r, nó da Arvore-B que será testado
/// \return 1, se for vazia, 0 se não for
/// \pre nenhuma
/// \post nenhuma
///
int vazia(ArvoreB* r);


///
/// \brief split, reparte o nó atual pela metade e cria um novo nó que contem a outra metade
/// \param x, nó que tem overflow e vai ser repartido
/// \param m, variavel que recebe a chave mediana do nó x
/// \return um nó y, que contem a outra metade do nó x repartido
/// \pre nenhuma
/// \post nenhuma
///
ArvoreB* split(ArvoreB* x, RegistrosDat *m);


///
/// \brief buscaPos, busca na Arvore passado por parametro se info pertence a ela
/// \param r, nó atual a ser buscado
/// \param info, valor a ser buscado na arvore
/// \param pos, variavel que recebe qual a posicao que se encontra o info
/// \return 1, se tiver na Arvore-B, 0, se n tiver
/// \pre nenhuma
/// \post nenhuma
///
int buscaPos(ArvoreB* r, int info, int * pos);


///
/// \brief eh_folha, verifica se o nó atual não tem filho
/// \param r, nó da Arvore-B
/// \return 1, se for folha, 0 se não for
/// \pre nenhuma
/// \post nenhuma
///
int eh_folha(ArvoreB* r);


///
/// \brief adicionaDireita, adiciona a chave no vetor de chaves do nó, colocando se precisar todas as outras chaves para a direita do numero
/// \param r, nó que recebe a chave
/// \param pos, posicao da chave
/// \param k, chave a ser adicionada
/// \param p, filho que a chave nova vai ser adiciona
/// \pre nenhuma
/// \post nenhuma
///
void adicionaDireita(ArvoreB* r, int pos, RegistrosDat k, int p);


///
/// \brief insere_aux, busca e insere o info no arquivo
/// \param registros, arquivo que contem os dados da arvore
/// \param indice, cabecalho do arquivo
/// \param r, arvore que contem os registros
/// \param info, valor que sera guardado no arquivo
/// \pre nenhuma
/// \post nenhuma
///
void insere_aux(FILE* registros, Cabecalho* indice, ArvoreB* r, RegistrosDat info);


///
/// \brief insere, insere na Arvore-B o info, guardando no arquivo o resultado da inserção 
/// \param registros, arquivo aonde será buscado os dados e guardado os dados
/// \param info, valor que sera colocado na arvore e guardado no arquivo
/// \pre nenhuma
/// \post nenhuma
///
void insere(FILE* registros, int info, int pos);

///
/// \brief printaArvore, busca os dados do arquivo e imprime na tela 
/// \param registros, arquivo que contem os dados do Arvore-B
/// \pre nenhuma
/// \post nenhuma
///
void printaArvore(FILE* registros);

Livres* criaNohLivre();

void lerArquivo(FILE* dados, FILE* arvore, char* nome);

CabecalhoDados* leCabecalhoDat(FILE* dados);

void imprimeCadastro(FILE* registros, FILE* dados);

void inOrdem(FILE* dados, FILE* registros, ArvoreB *raiz);