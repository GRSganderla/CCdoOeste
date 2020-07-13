#include<stdio.h>
#include<stdlib.h>
#include "ArvoreB.h"

//estrutura para a logica do programa
typedef struct menu
{
	//variaveis para os arquivos de entrada 
	char *arquivoStop;
	char *arquivoCaminho;
	//variaveis para as palavras dentro dos arquivos de entrada
	char **stopWord;
	char **caminho;
	//variavel para a quantidade das palavras
	int quantCaminho;
	int quantStopsWord;
}Menu;

///
/// \brief ehStopWord, verifica se o nome passada é Stop Word ou não
/// \param nome, palavra a ser verificada
/// \param stopWords, matriz de strings de stop words
/// \param quant, quantidade de stopWords
/// \return 1 se é stopWord, 0 se não
/// \pre nenhuma
/// \post nenhuma
///
int ehStopWord(char *nome, char **stopWords, int quant);

/// 
/// \brief abreArqCMD, pega o nome do arquivo passado por paramêtro e copia os dados dentro dele
/// \param nomeArq, nome do arquivo a ser lido
/// \return um vetor de Strings, contendo os dados o arquivo
/// \pre se o arquivo não é vazio, lê até o final do arquivo
/// \post nehhuma
///
char** abreArqCMD(char *nomeArq, int *tamanho);

/// 
/// \brief pegaArq, pega a primeira palavra da string da linha de comando
/// \param argv, variavel que guarda os dados da linha de comando
/// \return uma string que é a primeira palavra da string da linha de comando
/// \pre a linha de comando tem que ter 3 palavras para ser executado essa função
/// \post nenhuma
///
char* pegaArg(const char* argv[]);

/// 
/// \brief leLinhaCMD, lê a linha de comando passada por paramêtro e guarda o que foi lido
/// \param agrv, variavel que guarda a linha de comando
/// \param nomeStop, variavel que irá guardar o nome do arquivo que contém as stop words
/// \param nomeDir, variavel que irá guardar o nome do arquivo que contém os diretorios
/// \param argc, variavel que guarda a quantidade de palavras na linha de comando
/// \return 1 se a operação der certo, 0 se não
/// \pre se a linha de comando tiver mais de 2 palavras, ela é aceita
/// \post se é aceita, o programa executa normalmente
///
int leLinhaCMD(const char* argv[], char *nomeStop, char *nomeDir, int argc);

///
/// \brief criaMenu, cria uma variavel do tipo Menu e aloca seus campos
/// \return uma variavel do tipo Menu inicializada
/// \pre nenhuma
/// \post nenhuma
///
Menu* criaMenu();

///
/// \brief imprimeStopWords, pega o vetor de Strings e imprime suas strings 
/// \param stopWords, vetor de strings contendo as stop words
/// \param quant, quantidade de strings dentro do vetor
/// \pre nenhuma
/// \post nenhuma
///
void imprimeStopWords(char **stopWords, int quant);

/// 
/// \brief charValido, verifica se o char é valido 
/// \param c, char a ser verificado
/// \return 1 se for valido e 0 se não for valido
/// \pre nenhuma
/// \post nenhuma
///
int charValido(char c);

///
/// \brief temPalavra, verica se tem palavra ainda no arquivo atual
/// \param palavra, palavra que receberá a palavra que está no arquivo
/// \param atual, arquivo a ser retirada a palavra
/// \return 1 se tem palavra no arquivo e 0 se não
/// \pre nenhuma
/// \post nenhum
///
int temPalavra(char *palavra, FILE* atual);

///
/// \brief leArquivo, le o arquivo atual e pega as palavras permitida e insere no arquivo de Arvore-B
/// \param atual, o arquivo a ser buscada as palavras
/// \param invertido, arquivo a ser inserido as palavras
/// \param stopWords, matriz de strings a ser verificado se a palavra é permitida ou não
/// \param quantStop, quantidade de strings de Stop Words
/// \param registros, arquivo a ser inserido o Dado
/// \param numeroArq, indice que representa o número do arquivo 
/// \pre nenhuma
/// \post nenhuma
/// 
void leArquivo(FILE *atual, FILE *invertido, char **stopWords, int quantStop, FILE* registros, int numeroArq);

/// 
/// \brief arquivoInvertido, abre os arquivos de registros e o arquivo para a Arvore-B e abre os arquivos de cada uma dos diretorios
/// \param menu, variavel da estrutura Menu* que contém todo os dados que foi passado por cmd
/// \pre nenhuma
/// \post nenhuma
///
void arquivoInvertido(Menu* menu);

///
/// \brief printaArqQuant, pega o dado do arquivo de registro e imprime a quantidade que apareceu e o arquivo que apareceu
/// \param registros, arquivo com os dados
/// \param pos, posição do dado no arquivo de registro
/// \pre nenhuma
/// \post nenhuma
///
void printaArqQuant(FILE* registros, int pos);

///
/// \brief imprimeTabela, função que pega os nós da Arvore-B e imprime a sua chave
/// \param invertido, arquivo que contém a Arvore-B
/// \param registros, arquivo que contém todos os dados
/// \param raiz, nó do começo da Arvore-B
/// \pre nenhuma
/// \post nenhuma
///
void imprimeTabela(FILE* invertido, FILE* registros, ArvoreB* raiz);

///
/// \brief imprimeIndices, função que abre os arquivos da Arvore-B e o arquivo de registros, chamando a função para imprimir a tabela
/// \pre nenhuma
/// \post nenhuma
///
void imprimeIndices();

///
/// \brief separaPesquisa, separa a string de pesquisa pela as palavras dentro dela, voltando essas palavras
/// \param pesquisa, string a ser pego as palavras dentro dela
/// \param quantPalavra, ponteiro para a quantidade de palavras dentro da string
/// \return um vetor de strings, essas que são as palavras dentro da string pesquisa
/// \pre nenhuma
/// \post nenhuma
///
char** separaPesquisa(char *pesquisa, int *quantPalavra);

///
/// \brief atualizaDados, atualiza os dados dentro do vetor de Dados  
/// \param registros, arquivo com todos os Dados
/// \param busca, dado a ser buscado para atualizar o vetor de dados
/// \param dados, vetor de dados atual
/// \param tamanho, ponteiro para a quantidade de Dados lida
/// \return vetor de Dados atualizados
/// \pre nenhuma
/// \post nenhuma
///
Dado** atualizaDados(FILE* registros, Dado* busca, Dado** dados, int *tamanho);

///
/// \brief todosOsDados, procura todos os dados proximos do Dado atual
/// \param registros, arquivo aonde estão os dados
/// \param atual, dado atual da palavra
/// \param tamanho, ponteiro para a quantidade de palavras procuradas
/// \return os dados das palavras 
/// \pre nenhuma
/// \post nenhuma
///
Dado** todosOsDados(FILE* registros, Dado* atual, int *tamanho);

///
/// \brief pesquisaEmArq, pesquisa se as palavras pertence nos arquivos e mostra, a quantidade e os caminhos do arquivo
/// \param caminhos, os diretorios de cada arquivo a ser aberto e lido
/// \param quant, a qunatidade de diretorios
/// \param invertido, arquivo da Arvore B
/// \param registros, arquivo com os dados
/// \param palavraDeConsulta, vetor de strings contendo as palavras a serem pesquisadas
/// \param quantPalavra, quantidade de palavras a serem pesquisadas
/// \pre nenhuma
/// \post nenhuma
///
void pesquisaEmArq(char**caminhos, int quant, FILE* invertido, FILE* registros, char* palavraDeConsulta[], int quantPalavra);

///
/// \brief consultar, função que inicializa a pesquisa nos arquivos de registros, abre os arquivos de registro e de Arvore-B
/// \param caminhos, vetor de strings que contém os diretorios dos arquivos
/// \param quant, quantidade de strings dentro do vetor
/// \pre nenhuma
/// \post nenhuma
///
void consultar(char* caminhos[], int quant);

///
/// \brief operacoes, menu das opções que o programa faz 
/// \param menu, estrutura que contém as informações principais
/// \param palavras, estrutura que guarda as palavras lidas dos arquivos
/// \pre é posto ao usuário qual operação deve ser feita, enquanto tiver uma opção do usuário, o programa continua a executar
/// \post nenhuma
///
void operacoes(Menu* menu);
