#include<stdio.h>
#include<stdlib.h>

//estrutura para o dado do arquivo
typedef struct dado
{
	//o arquivo sendo a chave, a posicao da palavra, a quantidade e a proxima posicao
	int arquivo, posicao, quantidade, proxPos;
}Dado;

//estrutura do cabeçalho do arquivo de registros
typedef struct cabecalhoreg
{
	//qual a posicao do topo
	int topo;
}RegCabecalho;

///
/// \brief criaArqReg, cria e inicializa o campo que ficará como cabecalho do arquivo de registros
/// \param arq, arquivo que será posto o cabeçalho
/// \pre nenhuma
/// \post o arquivo terá espaço guardado com o cabeçalho do arquivo
///
void criaArqReg(FILE* arq);

///
/// \brief criaDados, aloca e inicializa cada um dos campos do tipo da estrutura Dado
/// \return uma variável do tipo Dado com os campos inicializado
/// \pre nenhuma
/// \post nenhuma
///
Dado* criaDados();

///
/// \brief escreveRegCabecalho, pega os dados da estrutura RegCabecalho e escreve no topo do arquivo
/// \param arq, arquivo que terá os dados do cabecalho escritos
/// \param indice, estrutura que contem o campo que será escrito no arquivo
/// \pre se não está alocado o indice, não insere
/// \post o arquivo terá topo atualizado
///
void escreveRegCabecalho(FILE* arq, RegCabecalho* indice);

///
/// \brief escreveDado, pega a variavel do tipo Dado e escreve ela no arquivo
/// \param arq, arquivo a ser escrito o dado
/// \param indice, variavel dos indices do arquivo
/// \param info, dado a ser escrito
/// \return a posicao aonde o dado foi escrito
/// \pre nenhuma
/// \post nenhuma
///
int escreveDado(FILE* arq, RegCabecalho* indice, Dado* info);

///
/// \brief leCabecalhoReg, pega os indices da posicao 0 do arquivo e guarda em uma variavel do tipo RegCabecalho
/// \param arq, arquivo a ser lido a posicao 0
/// \return uma variavel do tipo RegCabecalho que contem os dados do indice do arquivo
/// \pre nenhuma
/// \post nenhuma
///
RegCabecalho* leCabecalhoReg(FILE* arq);

///
/// \brief leDados, le os dados da posição passada e guarda em uma variavel do tipo Dados
/// \param arq, arquivo de onde será lido os dados
/// \param indice, variaveis do indice do arquivo
/// \param pos, posicao de onde o dado será lido
/// \return uma variavel do tipo Dado contendo as informações da posição
/// \pre se a posicao for negativa, retorna NULL
/// \post nenhuma
///
Dado* leDado(FILE* arq, int pos);

///
/// \brief separa, função auxiliar para a função de ordenação QuickSort
/// \param vet, vetor de string a ser ordenada
/// \param inicio, indice do começo do vetor
/// \param fim, indice do final do vetor
/// \return a posição do pivo no vetor
/// \pre nenhuma
/// \post nenhuma
///
int separa(char* vet[], int inicio, int fim);

///
/// \brief quicksSort, função que ordena um vetor de strings
/// \param vet, vetor de strings a ser ordenado
/// \param inicio, inicio do vetor
/// \param fim, final do vetor
/// \pre nenhuma
/// \post nenhuma
///
void quickSort(char* vet[],int inicio, int fim);