#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "fila.h"
#define MAX 100
#define ORDEM 5

//estrutura para o cabecalho do arquivo da Arvore-B
typedef struct noBArq
{
	//variaves do arquivo, sendo a raiz do arquivo, a quantidade de nós, a raiz dos nós livres e sua quantidade
	int topo;
	int quantidade;
	int nohsLivre;
	int quantidadeLivre;
}Cabecalho;

//estrutura dos dados que serão guardados no arquivo da Arvore-B
typedef struct registros
{
	//variavel que será a chave da Arvore-B
	int codigo;
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

//estrutura para os nós livres dentro do arquivo
typedef struct nohLivre
{
	//aponta para um valor que é o proximo nó dessa estrutura
	int prox;
}Livres;

//estrutura que guarda os dados do medico
typedef struct cadastro
{
	//codigo que é a chave do medico dentro da Arvore-B
	int codigo;
	//variaveis que guardam os dados pessoais do medico
	char nome[100];
	char sexo;
	char cpf[22];
	char crm[30];
	char especialidade[100];
	char rg[22];
	char telefone[23];
	char celular[24];
	char email[100];
	char endereco[100];
	char nascimento[21];
}Cadastro;

//estrutura para o Arquivo de Cadastro
typedef struct noBArqDat
{
	//variaves da cabeca do arquivo e a raiz dos nós livres
	int topo;
	int nohsLivre;
}CabecalhoDados;

//estrutura para os cadastro livres
typedef struct livre
{
	//recebe o valor do proximo nó livre
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

///
/// \brief leDados, lê do arquivo passado por parametro, os dados da posição indice 
/// \param dados, arquivo de cadastro aonde esta guardado todos os medicos cadastrados.
/// \param raiz, cabeçalho do arquivo de cadastro
/// \param indice, posição que está os dados a serem lidos dentro do arquivo 
/// \return uma estrutura do tipo Cadastro com as informações lidas daquela posição
/// \pre o arquivo de dados não estar vazio
/// \post nenhuma
///
Cadastro* leDados(FILE* dados, CabecalhoDados* raiz, int indice);

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
/// \brief escreveCabecalhoDat, escreve na posição 0 do arquivo os dados da estrutura do tipo CabecalhoDat 
/// \param registros, arquivo aonde será escrito 
/// \param indice, estrutura que será escrita no arquivo
/// \pre nenhuma
/// \post cabeçalho do arquivo de cadastro atualizado
///
void escreveCabecalhoDat(FILE* registros, CabecalhoDados* indice);

///
/// \brief leLivres, lê os dados guardados na parte dos nós livre dentro do arquivo
/// \param registros, arquivo que contém os nós inseridos
/// \param posicao, posição aonde esta o nó livre 
/// \return uma variavel do tipo Livres, que contém o valor da posição do nó livre
/// \pre ter um nó livre no arquivo
/// \post nenhuma
///
Livres* leLivres(FILE* registros, int posicao);

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
/// \brief escreverRegistro, escreve no arquivo o novo cadastro 
/// \param dados, arquivo de cadastro dos medicos 
/// \param indice, cabeçalho do arquivo de cadastro
/// \param medico, estrutura que contém os dados do novo medico inserido
/// \return a posição do cadastro dentro do arquivo
/// \pre nenhuma
/// \post nenhuma
///
int escreverRegistro(FILE* dados, CabecalhoDados* indice, Cadastro* medico);

///
/// \brief lerArquivo, lê o arquivo .txt que contém os dados dos medicos a serem inserido e os insere dentro do arquivo da Arvore-B
/// \param dados, arquivo que será inserido os novos cadastros
/// \param arvore, arquivo da Arvore-B que vai ser inserido novos nós
/// \param nome, nome do arquivo que será aberto e lido 
/// \pre o arquivo que será aberto deve existir 
/// \post nenhuma
///
void lerArquivo(FILE* dados, FILE* arvore, char* nome);

///
/// \brief leCabecalhoDat, lê o cabeçalho do arquivo de cadastro e retorna o que lêu 
/// \param dados, arquivo dos cadastro de medicos 
/// \return uma estrutura do tipo CabecalhoDados que contém o cabeçalho do arquivo
/// \pre nenhuma
/// \post nenhuma
///
CabecalhoDados* leCabecalhoDat(FILE* dados);

///
/// \brief criaNohLivre, cria uma variavel da estrutura Livres e a inicializa  
/// \return uma variavel do tipo Livres alocada
/// \pre nenhuma
/// \post nenhuma
///
Livres* criaNohLivre();

///
/// \brief leituraDoCabecalho, lê os dados da posição 0 do arquivo e os guarda 
/// \param binario, arquivo a ser lido 
/// \return uma estrutura com os dados lidos do arquivo
/// \pre nenhuma
/// \post nenhuma
///
Cabecalho* leituraDoCabecalho(FILE* binario);

///
/// \brief escreveNosLivres, escreve o nó removido na posição dos nós livres reservada no arquivo 
/// \param registros, arquivo a ser escrito o nó livres 
/// \param indice, cabeçalho que contém os dados do arquivo
/// \param raiz, nó a ser inserido nos livres
/// \pre nenhuma
/// \post nenhuma
///
void escreveNosLivres(FILE* registros, Cabecalho* indice, ArvoreB* raiz);

///
/// \brief remocao, remove o nó do arquivo 
/// \param registros, arquivo que terá nó removido
/// \pre o arquivo ter o nó buscado
/// \post o nó é removido do arquivo
///
void remocao(FILE *registros);

///
/// \brief remocaoAux, função que verifica qual a remoção é melhor para remover essa chave da Arvore-B 
/// \param registros, arquivo da Arvore-B que será alterada 
/// \param indice, cabeçalho do arquivo da Arvore-B
/// \param raiz, nó raiz da Arvore-B 
/// \param info, dado a ser removido 
/// \pre a arvore não ser vazia
/// \post nenhuma
///
void remocaoAux(FILE *registros, Cabecalho *indice, ArvoreB *raiz, RegistrosDat info);

///
/// \brief removerDaFolha, remove a chave da folha e arruma as outras chaves 
/// \param raiz, nó a ter a chave removida 
/// \param pos, posição aonde esta a chave a ser removida.
/// \pre nenhuma
/// \post nenhuma
///
void removerDaFolha(ArvoreB *raiz, int pos);

///
/// \brief , 
/// \param , 
/// \return ,
/// \pre 
/// \post 
///
void remocaoDoInterior(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos);

///
/// \brief pegaPrecessor, procura a maior chave do nó anterior 
/// \param registros, arquivo da Arvore-B 
/// \param raiz, nó que será buscado a maior chave
/// \param pos, posição do nó raiz
/// \return uma variavel que contém os dados 
/// \pre nenhuma
/// \post nenhuma
///
RegistrosDat pegaPrecessor(FILE *registros, ArvoreB *raiz, int pos);

///
/// \brief pegaSucessor, procura a menor chave do nó atual
/// \param registros, arquivo da Arvore-B
/// \param raiz, raiz que será buscado a menor chave
/// \param pos, posição que do nó raiz
/// \return uma variavel que contem a chave e posição do cadastro
/// \pre nenhuma
/// \post nenhuma
///
RegistrosDat pegaSucessor(FILE *registros, ArvoreB *raiz, int pos);

///
/// \brief merge, função que ajunta dois nós
/// \param registros, arquivo da Arvore-B
/// \param indice, cabeçalho do arquivo da Arvore-B
/// \param raiz, nó que será ajuntado com o outro 
/// \param pos, posição do nó raiz
/// \pre nenhuma
/// \post nenhuma
///
void merge(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos);

///
/// \brief , 
/// \param , 
/// \pre 
/// \post 
///
void enche(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos);

///
/// \brief , 
/// \param , 
/// \pre 
/// \post 
///
void emprestimoDoAnt(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos);

///
/// \brief , 
/// \param , 
/// \pre 
/// \post 
///
void emprestimoDoProx(FILE *registros, Cabecalho *indice, ArvoreB *raiz, int pos);

///
/// \brief printMedico, imprime os dados do medico na tela 
/// \param medico, cadastro a ser imprimido na tela 
/// \pre se os dados estão completos, ele imprime
/// \post nenhuma
///
void printMedico(Cadastro *medico);

///
/// \brief leituraEmCMD, insere o medico no arquivo de Arvore-B e no arquivo de cadastros a partir da entrada de dados via linha de comando
/// \param registros, arquivo que será inserido a nova chave do medico  
/// \param dados, arquivo de cadastro que será inserido as informações do medico 
/// \pre se o medico cumpre os requisitos, ele é inserido
/// \post nenhuma
///
void leituraEmCMD(FILE *registros, FILE *dados);

///
/// \brief imprimeInOrd, imprime os cadastros a partir da ordem crescente
/// \param registros, arquivo que será buscado os cadastros em ordem 
/// \param indice, cabeçalho do arquivo de Arvore-B 
/// \param dados, arquivo que será buscado as informações do medico 
/// \param raizDat, cabeçalho do arquivo de cadastro 
/// \param raiz, nó da raiz do arquivo 
/// \pre nenhuma
/// \post nenhuma
///
void imprimeInOrd(FILE *registros, Cabecalho *indice, FILE *dados, CabecalhoDados *raizDat, ArvoreB *raiz);

///
/// \brief imprimeRegistro, função inicial que imprime os cadastro em ordem crescente por codigo dos medicos
/// \param registros, arquivo que contém a Arvore-B
/// \param dados, arquivo de cadastros
/// \pre nenhuma
/// \post nenhuma
///
void imprimeRegistro(FILE *registros, FILE *dados);

///
/// \brief procuraCadastro, procura o cadastro do medico pela a Arvore-B do arquivo de registro e imprime na tela o resultado 
/// \param registros, arquivo da Arvore-B
/// \param dados, arquivo de cadastro
/// \param codigo, chave a ser buscada na arvore
/// \param posicaoRegistro, variavel que recebe a posição do cadastro dentro do arquivo de cadastro
/// \return uma estrutura que contém os dados do medico procurado
/// \pre nenhuma
/// \post nenhuma
///
Cadastro* procuraCadastro(FILE *registro, FILE *dados, int codigo, int *posicaoRegistro);

///
/// \brief altera, busca pelo codigo do medico e pode alterar os dados do medico 
/// \param registros, arquivo de onde será buscado a posição do medico 
/// \param dados, arquivo de cadastro do medico, aonde será atualizado a alteração
/// \pre nenhuma
/// \post nenhuma
///
void alterar(FILE* registros, FILE* dados);