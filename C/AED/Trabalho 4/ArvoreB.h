#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "fila.h"
#include "registros.h"
#define MAX 100
#define ORDEM 5

//estrutura para o cabecalho do arquivo da Arvore-B
typedef struct noBArq
{
	//variaves do arquivo, sendo a raiz do arquivo, a quantidade de nós
	int topo;
	int raiz;
}Cabecalho;

//estrutura dos dados que serão guardados no arquivo da Arvore-B
typedef struct registros
{
	//variavel que será a chave da Arvore-B
	char palavra[MAX];
	//posição aonde está guardado os dados do medico no arquivo de dados do cadastro de medicos
	int registroPos;
}RegistrosDat;

//estrutura de um nó da Arvore do Tipo B
typedef struct arvoreB
{
	//quantidade de chaves dentro do nó 
	int numChaves;
	//posicao aonde está guardado no arquivo da Arvore-B
	int posicao;
	//vetor da estrutura de Registro de Dados, que guarda o codigo e posição dos dados no arquivo de cadastro
	RegistrosDat chave[ORDEM];
	//vetor com os nó que são filho deste nó
	int filho[ORDEM];
}ArvoreB;

///
/// \brief liberaNoh, desaloca o nó da Arvore-B da memoria
/// \param alvo, libera a memoria usada pelo nó
/// \pre nenhuma
/// \post a area ocupada pelo nó sera desocupada
///
void liberaNoh(ArvoreB* alvo);

///
/// \brief criaIndicesArq, inicializa uma variavel do tipo da estrutura Cabeçalho e escreve no arquivo binario 
/// \param binario, arquivo aonde terá seu cabeçalho escrito com os indices.
/// \pre nenhuma
/// \post nenhuma
///
void criaIndicesArq(FILE *binario);

///
/// \brief inicializaArvore, cria uma variavel da estrutura ArvoreB e inicializa as variaveis dentro da estrutura. 
/// \return retorna uma variavel do tipo ArvoreB inicializa e alocada
/// \pre nenhuma
/// \post nenhuma
///
ArvoreB* inicializaArvore();

///
/// \brief escreveCabecalho, escreve no arquivo passado as informações dos indices do Cabeçalho
/// \param registros, arquivo que tera o cabeçalho atualizado
/// \param indice, variavel que contém as informações que serão escritas no arquivo
/// \pre arquivo esteja aberto e guardado
/// \post nenhuma
///
void escreveCabecalho(FILE* registros, Cabecalho* indice);

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
int buscaPos(ArvoreB* r, char* info, int * pos);

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
void insere(FILE* registros, char* info, int pos);

///
/// \brief printaArvore, busca os dados do arquivo e imprime na tela 
/// \param registros, arquivo que contem os dados do Arvore-B
/// \pre nenhuma
/// \post nenhuma
///
void printaArvore(FILE* registros);

///
/// \brief leituraDoNoh, procura no arquivo a posição do nó a ser lido e guarda em uma variavel tipo ArvoreB 
/// \param binario, arquivo da Arvore-B que contém todos os dados dos nós inseridos 
/// \param posicao, posição aonde o nó esta inserido e quer ser lido 
/// \return uma variavel do tipo ArvoreB que contém os dados do nó da posição lida
/// \pre nenhuma
/// \post nenhuma
///
ArvoreB* leituraDoNoh(FILE* binario, int posicao);

///
/// \brief escreveArvore, escreve o nó passado por parametro dentro do arquivo 
/// \param registros, arquivo aonde será escrito 
/// \param galho, nó da Arvore-B que sera escrito no arquivo 
/// \param indice, cabeçalho do arquivo que terá indices atualizados
/// \return a posição aonde foi escrito no arquivo o nó
/// \pre nenhuma
/// \post nenhuma
///
int escreveArvore(FILE* registros, ArvoreB* galho, Cabecalho* indice);

///
/// \brief leituraDoCabecalho, lê os dados da posição 0 do arquivo e os guarda 
/// \param binario, arquivo a ser lido 
/// \return uma estrutura com os dados lidos do arquivo
/// \pre nenhuma
/// \post nenhuma
///
Cabecalho* leituraDoCabecalho(FILE* binario);

///
/// \brief procuraDado, procura no arquivo o dado que contém a palavra passada
/// \param registro, arquivo que contém a Arvore-B
/// \param dados, arquivo que contém todos os dados inseridos
/// \param palavra, palavra a ser procurada dentro do arquivo de dados
/// \return o dado encontrado no arquivo
/// \pre nenhuma
/// \post nenhuma
/// 
Dado* procuraDado(FILE *registro, FILE *dados, char *palavra);