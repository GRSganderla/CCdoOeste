#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Arquivos.h"
#include "fila.h"
#define MAX 100
#define ORDEM 5

//estrutura para o cabecalho do arquivo
typedef struct noBArq
{
	//variaves da cabeca do arquivo, sendo a raiz do arquivo, a quantidade de nós, a raiz dos nós livres e sua quantidade
	int topo;
	int quantidade;
	int nohsLivre;
	int quantidadeLivre;
}Cabecalho;

typedef struct registros
{
	int codigo;
	int registroPos;
}RegistrosDat;

typedef struct arvoreB
{
	int numChaves;
	int posicao;
	RegistrosDat chave[ORDEM];
	int filho[ORDEM];
}ArvoreB;

typedef struct nohLivre
{
	int prox;
}Livres;

typedef struct cadastro
{
	int codigo;
	char nome[100];
	char sexo;
	char cpf[12];
	char crm[20];
	char especialidade[100];
	char rg[12];
	char telefone[13];
	char celular[14];
	char email[100];
	char endereco[100];
	char nascimento[11];
}Cadastro;

typedef struct noBArqDat
{
	//variaves da cabeca do arquivo e a raiz dos nós livres
	int topo;
	int nohsLivre;
}CabecalhoDados;

typedef struct livre
{
	int proxLivre; 
}RegistrosLivres;

///
/// \brief criaIndicesArqDat, cria os indices do arquivo do tipo de dados, que são a raiz do arquivo e a raiz dos nós livres
/// \param binario, arquivo que vai inserir os indices
/// \pre nenhuma
/// \post arquivo passado terá seus indices e primeiras linha escritas
///
void criaIndicesArqDat(FILE *binario);

///
/// \brief inicializaCadastro, aloca e inicializa as variaveis da estrutura Cadastro
/// \return uma estrutura de dados do tipo Cadastro alocada
/// \pre nenhuma
/// \post nenhuma
///
Cadastro* inicializaCadastro();

///
/// \brief liberaNoh, desaloca o nó da Arvore-B da memoria
/// \param alvo, libera a memoria usada pelo nó
/// \pre nenhuma
/// \post a area ocupada pelo nó sera desocupada
///
void liberaNoh(ArvoreB* alvo);

void criaIndicesArq(FILE *binario);

ArvoreB* inicializaArvore();

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

int validaCPF(char *s);

int validaTelefone(char *s);

int validaCelular(char *s);

Cadastro* leDados(FILE* dados, CabecalhoDados* raiz, int indice);

ArvoreB* leituraDoNoh(FILE* binario, int posicao);

void escreveCabecalhoDat(FILE* registros, CabecalhoDados* indice);

Livres* leLivres(FILE* registros, int posicao);

int escreveArvore(FILE* registros, ArvoreB* galho, Cabecalho* indice);

void adicionaDireita(ArvoreB* r, int pos, RegistrosDat info, int p);

void insere(FILE* registros, int dado, int pos);

int escreverRegistro(FILE* dados, CabecalhoDados* indice, Cadastro* medico);

void lerArquivo(FILE* dados, FILE* arvore, char* nome);

CabecalhoDados* leCabecalhoDat(FILE* dados);

void criaIndicesArq(FILE *binario);

Livres* criaNohLivre();

Cabecalho* leituraDoCabecalho(FILE* binario);

void escreveNosLivres(FILE* registros, Cabecalho* indice, ArvoreB* raiz);

void removerArvoreB(FILE *registros, int id);

void removerArvoreBAux(FILE *registros, Cabecalho *indice, ArvoreB *raiz, RegistrosDat info);

void removerDaFolha(ArvoreB *raiz, int pos);

void removerDoInteirior(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos);

RegistrosDat pegaPrecessor(FILE *f, ArvoreB *raiz, int pos);

RegistrosDat pegaSucessor(FILE *f, ArvoreB *raiz, int pos);

void merge(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos);

void fill(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos);

void emprestimoDoAnt(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos);

void emprestimoDoProx(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos);

void printMedico(Cadastro *medico) ;

void leituraEmCMD(FILE *registros, FILE *dados) ;

void imprimeInOrd(FILE *registros, Cabecalho *indice, FILE *dados, CabecalhoDados *raizDat, ArvoreB *raiz) ;

void imprimeRegistro(FILE *registros, FILE *dados) ;

void procuraCadastro(FILE *registro, FILE *dados) ;