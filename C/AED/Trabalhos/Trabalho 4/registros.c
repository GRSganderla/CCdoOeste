#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "registros.h"

///
/// \brief criaArqReg, cria e inicializa o campo que ficará como cabecalho do arquivo de registros
/// \param arq, arquivo que será posto o cabeçalho
/// \pre nenhuma
/// \post o arquivo terá espaço guardado com o cabeçalho do arquivo
///
void criaArqReg(FILE* arq)
{
	RegCabecalho indice;

	indice.topo = 0;
	//escreve o cabecalho do arquivo de registro
	escreveRegCabecalho(arq, &indice);
}

///
/// \brief criaDados, aloca e inicializa cada um dos campos do tipo da estrutura Dado
/// \return uma variável do tipo Dado com os campos inicializado
/// \pre nenhuma
/// \post nenhuma
///
void escreveRegCabecalho(FILE* arq, RegCabecalho* indice)
{
	//se não tem cabecalho
	if(!indice)
		return;

	//busca o topo e escreve o cabecalho
	fseek(arq, 0, SEEK_SET);
	fwrite(indice, sizeof(RegCabecalho), 1, arq);
}

///
/// \brief escreveRegCabecalho, pega os dados da estrutura RegCabecalho e escreve no topo do arquivo
/// \param arq, arquivo que terá os dados do cabecalho escritos
/// \param indice, estrutura que contem o campo que será escrito no arquivo
/// \pre se não está alocado o indice, não insere
/// \post o arquivo terá topo atualizado
///
Dado* criaDados()
{
	//cria, aloca e inicializa os campos
	Dado* novo = (Dado*)malloc(sizeof(Dado));

	novo->arquivo = -1;
	novo->quantidade = 0;
	novo->proxPos = -1;
	novo->posicao = -1;

	return novo;
}

///
/// \brief escreveDado, pega a variavel do tipo Dado e escreve ela no arquivo
/// \param arq, arquivo a ser escrito o dado
/// \param indice, variavel dos indices do arquivo
/// \param info, dado a ser escrito
/// \return a posicao aonde o dado foi escrito
/// \pre nenhuma
/// \post nenhuma
///
int escreveDado(FILE* arq, RegCabecalho* indice, Dado* info)
{
	int posicao;

	posicao = info->posicao;

	//se a posição dele não foi atribuida
	if(posicao == -1)
	{
		//vira o topo do arquivo
		posicao = indice->topo++;

		//reescreve o cabecalho
		escreveRegCabecalho(arq, indice);
	}

	//atualiza a posicão dele
	info->posicao = posicao;

	//busca essa posição e escreve 
	fseek(arq, sizeof(RegCabecalho) + sizeof(Dado)*posicao, SEEK_SET);
	fwrite(info, sizeof(Dado), 1, arq);

	//retorna a posição no arquivo
	return posicao;
}

///
/// \brief leCabecalhoReg, pega os indices da posicao 0 do arquivo e guarda em uma variavel do tipo RegCabecalho
/// \param arq, arquivo a ser lido a posicao 0
/// \return uma variavel do tipo RegCabecalho que contem os dados do indice do arquivo
/// \pre nenhuma
/// \post nenhuma
///
RegCabecalho* leCabecalhoReg(FILE* arq)
{
	//cria e aloca
	RegCabecalho* indice = (RegCabecalho*)malloc(sizeof(RegCabecalho));
	//busca o topo e le o cabecalho 
	fseek(arq, 0, SEEK_SET);
	fread(indice, sizeof(RegCabecalho), 1, arq);

	//retorna o cabecalho lido
	return indice;
}

///
/// \brief leDados, le os dados da posição passada e guarda em uma variavel do tipo Dados
/// \param arq, arquivo de onde será lido os dados
/// \param indice, variaveis do indice do arquivo
/// \param pos, posicao de onde o dado será lido
/// \return uma variavel do tipo Dado contendo as informações da posição
/// \pre se a posicao for negativa, retorna NULL
/// \post nenhuma
///
Dado* leDado(FILE* arq, int pos)
{
	//cria e aloca
	Dado* novo = (Dado*)malloc(sizeof(Dado));
	//se a posição buscada não é possivel, retorna nulo
	if(pos == -1) return NULL;
	//busca a posição no arquivo e lê o dado lá
	fseek(arq, sizeof(RegCabecalho) + sizeof(Dado)*pos, SEEK_SET);
	fread(novo, sizeof(Dado), 1, arq);
	//retorna esse dado
	return novo;
}

///
/// \brief separa, função auxiliar para a função de ordenação QuickSort
/// \param vet, vetor de string a ser ordenada
/// \param inicio, indice do começo do vetor
/// \param fim, indice do final do vetor
/// \return a posição do pivo no vetor
/// \pre nenhuma
/// \post nenhuma
///
int separa(char* vet[], int inicio, int fim)
{
    int j, k;
    char* temp,* pivo;
    //pivo vira o fim do vetor 
    pivo = vet[fim];
    j = inicio;
    //enquanto não for o meio entre inicio e fim
    for(k = inicio; k < fim; k++)
    {
    	//compara as strings
        if(strcmp(vet[k], pivo) <=0)
        {
        	//troca as posições 
            temp = vet[j];
            vet[j] = vet[k];
            vet[k] = temp;
            j++;
        }
    }

    //final atualizado
    vet[fim] = vet[j];
    vet[j] = pivo;

    //retorna a posição do pivo
    return j;
}

///
/// \brief quicksSort, função que ordena um vetor de strings
/// \param vet, vetor de strings a ser ordenado
/// \param inicio, inicio do vetor
/// \param fim, final do vetor
/// \pre nenhuma
/// \post nenhuma
///
void quickSort(char* vet[],int inicio, int fim)
{
    int j;
    //enquanto não for o fim
    if(inicio < fim)
    {
    	//chama a função que separa a string e recursivamente quebra o vetor em dois
        j = separa(vet, inicio, fim);
        quickSort(vet, inicio, j-1);
        quickSort(vet, j+1, fim);
    }
}
