#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

//estrutura para a palavra e a localização dela
typedef struct Registro
{
	//a palavra que ela guarda
	char *palavra;
	//o arquivo que contém essa palavra
	char *diretorio[20];
	//a quantidade em que a palavra aparece
	int quantidade;
}Registro;

//estrutura para a logica do programa
typedef struct SemCriat
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
	//variavel para as palavras e a quantidade de palavras
	Registro palavra[100];
	int quantPalavra;
}SemCriat;

int separa(char* vet[], int inicio, int fim)
{
    int j, k;
    char* temp,* pivo;

    pivo = vet[fim];
    j = inicio;

    for(k = inicio; k < fim; k++)
    {
        if(strcmp(vet[k], pivo) <=0)
        {
            temp = vet[j];
            vet[j] = vet[k];
            vet[k] = temp;
            j++;
        }
    }

    vet[fim] = vet[j];
    vet[j] = pivo;

    return j;
}

void quickSort(char* vet[],int inicio, int fim)
{
    int j;

    if(inicio < fim)
    {
        j = separa(vet, inicio, fim);
        quickSort(vet, inicio, j-1);
        quickSort(vet, j+1, fim);
    }
}

///
/// \brief 
/// \param
/// \return 
/// \pre 
/// \post 
///
int pertenceStop(char *v, char** stop, int quantidade)
{
	int i;

	 if(strlen(v) <= 1)
	 	return 1;

	for(i = 0; i < quantidade; i++)
	{
		if(!strcmp(v, stop[i]))
			return 1;
	}

	return 0;
}

void caracteres(char *string)
{
	int i;

	for(i = 0; i < strlen(string); i++)
	{
		if(string[i] == ',' || string[i] == ';' || string[i] == '.' || string[i] == ':' || string[i] == '?' || string[i] == '!')
			string[i] = '\0';
	}
}

int jaExiste(char *nome, Registro palavra[], int quant)
{
	int i;

	for(i = 0; i < quant; i++)
	{
		if(!strcmp(nome, palavra[i].palavra))
			return 1;
	}

	return 0;
}

int pertenceDiretorio(char* arquivoAtual, char* arquivoDoReg[], int quantCaminho)
{
	int i;

	for(i = 0; i < quantCaminho; i++)
	{
		if(!strcmp(arquivoAtual, arquivoDoReg[i]))
			return 1;
	}

	return 0;
}

void printaRegistroP(Registro dados)
{
	printf("[%s]", dados.palavra);
	printf("[%s]", dados.diretorio[0]);
	printf("[%s]\n", dados.quantidade);
}

///
/// \brief 
/// \param
/// \return 
/// \pre 
/// \post 
///
void leituraDeArq(SemCriat *menu)
{	
	int i, j, k, w;

	for(i = 0; i < menu->quantCaminho; i++)
	{
		FILE* f = fopen(menu->caminho[i], "r");
		w = 0;
		while(!feof(f))                                                                                       
		{
			char v[256];
			fscanf(f, "%s ", v);
			caracteres(v);
		
			if(!pertenceStop(v, menu->stopWord, menu->quantStopsWord))
			{
				if(!jaExiste(v, menu->palavra, menu->quantPalavra))
				{
					printf("a\n");
					strcpy(menu->palavra[w].palavra, v);
					strcpy(menu->palavra[w].diretorio[0], menu->caminho[i]);
					menu->palavra[w].quantidade++;
					printf("%d\n", menu->palavra[w].quantidade);
				}
				else
				{
					printf("b\n");
					for(j = 0; j < menu->quantPalavra; j++)
					{
						if(!strcmp(v, menu->palavra[j].palavra))
						{
							if(pertenceDiretorio(menu->caminho[i], menu->palavra[j].diretorio, menu->quantCaminho))
							{
								menu->palavra[j].quantidade++;
								printf("%d\n", menu->palavra[j].quantidade);
							}
							else
							{
								for(k = 0; k < menu->quantCaminho; k++)
								{
									if(menu->palavra[j].diretorio[k] == NULL)
									{
										strcpy(menu->palavra[j].diretorio[k], menu->caminho[i]);
										menu->palavra[j].quantidade++;
										printf("%d\n", menu->palavra[j].quantidade);
									}
								}
							}
						}
					}
				}
				printf("\n");
				printaRegistroP(menu->palavra[w]);
				w++;
			}

		}			
	}
		printf("aloo?\n");

}

/// 
/// \brief abreArqCMD, pega o nome do arquivo passado por paramêtro e copia os dados dentro dele
/// \param nomeArq, nome do arquivo a ser lido
/// \return um vetor de Strings, contendo os dados o arquivo
/// \pre se o arquivo não é vazio, lê até o final do arquivo
/// \post
///
char** abreArqCMD(char *nomeArq, int *tamanho)
{
	FILE *arquivo = fopen(nomeArq, "r+");
	
	if(arquivo == NULL)
	{
		printf("Arquivo Stop nulo\n");
		return 0;
	}

	int i;
	char v[256], **conteudo;

	*tamanho = 2;

    conteudo = (char**)malloc(sizeof(char*) * *tamanho);

	for(i = 0; !feof(arquivo); i++)
    {
        if(i+1 > *tamanho)
        {
            *tamanho *= 2;
            conteudo = (char**)realloc(conteudo, sizeof(char*) * *tamanho);
        }

        fscanf(arquivo, "%[^\n]%*c", v);

        conteudo[i] = strcpy(malloc(sizeof(char) * strlen(v) + 1), v);
    }

    *tamanho = i;
    conteudo = (char**)realloc(conteudo, sizeof(char*) * *tamanho);

	fclose(arquivo);
	return conteudo;
}

/// 
/// \brief pegaArq, pega a primeira palavra da string da linha de comando
/// \param argv, variavel que guarda os dados da linha de comando
/// \return uma string que é a primeira palavra da string da linha de comando
/// \pre a linha de comando tem que ter 3 palavras para ser executado essa função
/// \post nenhuma
///
char* pegaArg(const char* argv[])
{
	return (char*)argv[0];
}

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
int leLinhaCMD(const char* argv[], char *nomeStop, char *nomeDir, int argc)
{
	if(argc > 2)
	{
		strcpy(nomeDir, pegaArg(argv+1));
		strcpy(nomeStop, pegaArg(argv+2));
		return 1;
	}

	return 0;
}

///
/// \brief criaRegistro, cria uma variavel do tipo RegistroPalavra e aloca seus campos
/// \return um variavel do tipo RegistroPalavra inicializada
/// \pre nenhuma
/// \post nenhuma
///
Registro criaRegistro()
{
	Registro novo;

	novo.palavra = malloc(sizeof(char)*100);
	novo.quantidade = 0;

	int i;
	for(i = 0; i < 20; i++)
		novo.diretorio[i] = (char*)malloc(sizeof(char)*100);

	return novo;
}

///
/// \brief cria??, cria uma variavel do tipo ?? e aloca seus campos
/// \return uma variavel do tipo ?? inicializada
/// \pre nenhuma
/// \post nenhuma
///
SemCriat* criaSemCriat()
{
	SemCriat* novo = (SemCriat*)malloc(sizeof(SemCriat));

	novo->arquivoStop = malloc(sizeof(char)*100);
	novo->arquivoCaminho = malloc(sizeof(char)*100);
	novo->quantCaminho = 0;
	novo->quantStopsWord = 0;
	novo->quantPalavra = 0;

	int i;
	for(i = 0; i < 100; i++)
		novo->palavra[i] = criaRegistro();

	return novo;
}

///
/// \brief imprimeStopWords, pega o vetor de Strings e imprime suas strings 
/// \param stopWords, 
/// \pre nenhuma
/// \post nenhuma
///
void imprimeStopWords(char **stopWords, int quant)
{
	if(stopWords[0] == NULL)
		printf("Arquivo nao contem Stops Words!\n");
	else
	{
		int i;
		printf("Stop Words:\n");
		for(i = 0; i < quant; i++)
			printf("-> %s\n", stopWords[i]);
	}
}

///
/// \brief operacoes, menu das opções que o programa faz 
/// \param menu, estrutura que contém as informações principais
/// \param palavras, estrutura que guarda as palavras lidas dos arquivos
/// \pre é posto ao usuário qual operação deve ser feita, enquanto tiver uma opção do usuário, o programa continua a executar
/// \post nenhuma
///
void operacoes(SemCriat* menu)
{
	int opcao;

	do
	{
		system("CLS");

		printf("\t[1] - Imprimir lista de Stop Words\n");
		printf("\t[2] - Imprimir indice\n");
		printf("\t[3] - Consultar\n");
		printf("\t[0] - Fechar\n");
		printf("\tOpcao: ");

		scanf("%d%*c", &opcao);

		switch(opcao)
		{
			case 1:
				quickSort(menu->stopWord, 0, menu->quantStopsWord-1);
				imprimeStopWords(menu->stopWord, menu->quantStopsWord);
			case 2:
				//blu;
			case 3:
				//ble;
			case 0:
			default:
				break;
		}

		getch();

	}while(opcao != 0);
}

int main(int argc, char const *argv[])
{
	int opcao;
	SemCriat* menu = criaSemCriat();

	if(leLinhaCMD(argv, menu->arquivoStop, menu->arquivoCaminho, argc))
	{
		menu->stopWord = abreArqCMD(menu->arquivoStop, &menu->quantStopsWord);
		menu->caminho = abreArqCMD(menu->arquivoCaminho, &menu->quantCaminho);
		//leituraDeArq(menu);

		//operacoes(menu);
	}else
		printf("Arquivos inexistentes!\n");

	return 0;
}