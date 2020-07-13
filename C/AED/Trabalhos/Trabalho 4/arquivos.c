#include<stdio.h>
#include<stdlib.h>
#include "arquivos.h"
#include<string.h>
#include<conio.h>
#include<ctype.h>

///
/// \brief ehStopWord, verifica se o nome passada é Stop Word ou não
/// \param nome, palavra a ser verificada
/// \param stopWords, matriz de strings de stop words
/// \param quant, quantidade de stopWords
/// \return 1 se é stopWord, 0 se não
/// \pre nenhuma
/// \post nenhuma
///
int ehStopWord(char *nome, char** stopWords, int quant)
{
	int i;

	if(!nome[0]) return 1;

	if(strlen(nome) == 1) return 1;

	for(i = 0; i < quant; i++)
	{
		if(!strcmp(nome, stopWords[i]))
			return 1;
	}

	return 0;
}

/// 
/// \brief abreArqCMD, pega o nome do arquivo passado por paramêtro e copia os dados dentro dele
/// \param nomeArq, nome do arquivo a ser lido
/// \return um vetor de Strings, contendo os dados o arquivo
/// \pre se o arquivo não é vazio, lê até o final do arquivo
/// \post
///
char** abreArqCMD(char *nomeArq, int *quantidade)
{
	FILE *arquivo = fopen(nomeArq, "r+");
	
	if(arquivo == NULL)
	{
		printf("Arquivo Stop nulo\n");
		return 0;
	}

	int i;
	char v[256], **conteudo;

	*quantidade = 2;

    conteudo = (char**)malloc(sizeof(char*) * *quantidade);

	for(i = 0; !feof(arquivo); i++)
    {
        if(i+1 == *quantidade)
        {
            (*quantidade) *= 2;
            conteudo = (char**)realloc(conteudo, sizeof(char*) * (*quantidade));
        }

        fscanf(arquivo, "%[^\n]%*c", v);

        conteudo[i] = strcpy(malloc(sizeof(char) * strlen(v) + 1), v);
    }

    *quantidade = i;
    conteudo = (char**)realloc(conteudo, sizeof(char*) * *quantidade);

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
/// \brief cria??, cria uma variavel do tipo ?? e aloca seus campos
/// \return uma variavel do tipo ?? inicializada
/// \pre nenhuma
/// \post nenhuma
///
Menu* criaMenu()
{
	Menu* novo = (Menu*)malloc(sizeof(Menu));

	novo->arquivoStop = malloc(sizeof(char)*100);
	novo->arquivoCaminho = malloc(sizeof(char)*100);
	novo->quantCaminho = 0;
	novo->quantStopsWord = 0;

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
	system("CLS");
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
/// \brief charValido, verifica se o char é valido 
/// \param c, char a ser verificado
/// \return 1 se for valido e 0 se não for valido
/// \pre nenhuma
/// \post nenhuma
///
int charValido(char c)
{
	return(isalnum(c) || c == '-' || c == '\'');
}

///
/// \brief temPalavra, verica se tem palavra ainda no arquivo atual
/// \param palavra, palavra que receberá a palavra que está no arquivo
/// \param atual, arquivo a ser retirada a palavra
/// \return 1 se tem palavra no arquivo e 0 se não
/// \pre nenhuma
/// \post nenhum
///
int temPalavra(char *palavra, FILE* atual)
{	
	int i = 0, valido;
	char letra = 'a';
	palavra[0] = '\0';

	do{
		
		if(fscanf(atual, "%c", &letra) == EOF && !i) return 0;
		
		valido = charValido(letra);

		if(valido)
			palavra[i++] = letra;

		if(feof(atual)) return 0;

	}while(valido);

	palavra[i] = '\0';

	return 1;
}

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
void leArquivo(FILE *atual, FILE *invertido, char **stopWords, int quantStop, FILE* registros, int numeroArq)
{
	char palavra[256];
	Dado* dadoArq = NULL;
	RegCabecalho* indiceReg = leCabecalhoReg(registros);

	while(temPalavra(palavra, atual))
	{
		if(!ehStopWord(palavra, stopWords, quantStop))
		{	
			dadoArq = procuraDado(invertido, registros, palavra);
			if(!dadoArq)
			{
				Dado* novo = criaDados();

				novo->arquivo = numeroArq;

				insere(invertido, palavra, escreveDado(registros, indiceReg, novo));
				dadoArq = procuraDado(invertido, registros, palavra);
			}
			else
			{			
				Dado* dadoIgual = dadoArq, *repetido = NULL;

				while(dadoIgual->arquivo != numeroArq)
				{
					repetido = leDado(registros, dadoIgual->proxPos);

					if(!repetido)
					{
						Dado* novo = criaDados();

						novo->arquivo = numeroArq;

						dadoIgual->proxPos = escreveDado(registros, indiceReg, novo);

						escreveDado(registros, indiceReg, dadoIgual);

						repetido = novo;
					}

					free(dadoIgual);

					dadoIgual = repetido;
				}

				dadoArq = dadoIgual;
			}

			if(dadoArq)
			{
				dadoArq->quantidade++;

				escreveDado(registros, indiceReg, dadoArq);
				free(dadoArq);
			}
		}	
	}
}

/// 
/// \brief arquivoInvertido, abre os arquivos de registros e o arquivo para a Arvore-B e abre os arquivos de cada uma dos diretorios
/// \param menu, variavel da estrutura Menu* que contém todo os dados que foi passado por cmd
/// \pre nenhuma
/// \post nenhuma
///
void arquivoInvertido(Menu* menu)
{
	int i = 1;
	FILE* registros, *invertido, *atual;

	registros = fopen("registros.bin", "wb+");
	if(registros == NULL) return;
	invertido = fopen("invertido.bin", "wb+");
	if(invertido == NULL) return;

	criaIndicesArq(invertido);
	criaArqReg(registros);

	for(int j = 0; j < menu->quantCaminho; j++)
	{
		atual = fopen(menu->caminho[j], "r");

		if(atual == NULL) continue;

		leArquivo(atual, invertido, menu->stopWord, menu->quantStopsWord, registros, i++);

		fclose(atual);
	}

	fclose(invertido);
	fclose(registros);
}

///
/// \brief printaArqQuant, pega o dado do arquivo de registro e imprime a quantidade que apareceu e o arquivo que apareceu
/// \param registros, arquivo com os dados
/// \param pos, posição do dado no arquivo de registro
/// \pre nenhuma
/// \post nenhuma
///
void printaArqQuant(FILE* registros, int pos)
{
	Dado* arqQuant = leDado(registros, pos), *proxArqQuant;

	while(arqQuant)
	{
		printf(" %d, %d ", arqQuant->arquivo, arqQuant->quantidade);

		proxArqQuant = leDado(registros, arqQuant->proxPos);
		arqQuant = proxArqQuant;
	}

	printf("\n");
}

///
/// \brief imprimeTabela, função que pega os nós da Arvore-B e imprime a sua chave
/// \param invertido, arquivo que contém a Arvore-B
/// \param registros, arquivo que contém todos os dados
/// \param raiz, nó do começo da Arvore-B
/// \pre nenhuma
/// \post nenhuma
///
void imprimeTabela(FILE* invertido, FILE* registros, ArvoreB* raiz)
{
	if(!raiz) return;

	ArvoreB* filho = leituraDoNoh(invertido, raiz->filho[0]);

	imprimeTabela(invertido, registros, filho);
	int i;
	for(i = 0; i < raiz->numChaves; i++)
	{
		printf("| %-27s|", raiz->chave[i].palavra);

		printaArqQuant(registros, raiz->chave[i].registroPos);

		filho = leituraDoNoh(invertido, raiz->filho[i+1]);
		imprimeTabela(invertido, registros, filho);

		free(filho);
	}
}

///
/// \brief imprimeIndices, função que abre os arquivos da Arvore-B e o arquivo de registros, chamando a função para imprimir a tabela
/// \pre nenhuma
/// \post nenhuma
///
void imprimeIndices()
{
	FILE* invertido = fopen("invertido.bin", "rb+");
	if(invertido == NULL) return;

	FILE* registros = fopen("registros.bin", "rb+");
	if(registros == NULL) return;

	Cabecalho* indiceB = leituraDoCabecalho(invertido);
	ArvoreB* raiz = leituraDoNoh(invertido, indiceB->raiz);

	if(raiz)
	{ 
		system("CLS");
		printf("---------------------------------------------------------------\n");
		printf("|          Palavra           |        Arquivo/Quantidade      |\n");
		printf("---------------------------------------------------------------\n");
	
		imprimeTabela(invertido, registros, raiz);

		printf("---------------------------------------------------------------\n");
	}

	fclose(registros);
	fclose(invertido);
}

///
/// \brief separaPesquisa, separa a string de pesquisa pela as palavras dentro dela, voltando essas palavras
/// \param pesquisa, string a ser pego as palavras dentro dela
/// \param quantPalavra, ponteiro para a quantidade de palavras dentro da string
/// \return um vetor de strings, essas que são as palavras dentro da string pesquisa
/// \pre nenhuma
/// \post nenhuma
///
char** separaPesquisa(char *pesquisa, int *quantPalavra)
{
	char **palavraPesq, palavra[256];
	int percorre, n = 0, i = 0, tamanhoPesquisa = (int) strlen(pesquisa);
	
	(*quantPalavra) = 2;
	palavraPesq = (char **)malloc(sizeof(char*)*(*quantPalavra));
	
	for(percorre = 0; percorre < tamanhoPesquisa; percorre += n)
	{
		sscanf((const char*)(pesquisa+percorre), "%s%n", palavra, &n);

		if(palavra[0])
		{
			if(i+1 == *quantPalavra)
			{
				(*quantPalavra) *= 2;

				palavraPesq = (char**)realloc(palavraPesq, sizeof(char*) * (*quantPalavra));
			}

			palavraPesq[i++] = strcpy(malloc(strlen(palavra)+1), palavra);
		}
	}

	*quantPalavra = i;

	palavraPesq = (char**)realloc(palavraPesq, sizeof(char*)*(*quantPalavra));

	return palavraPesq;
}

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
Dado** atualizaDados(FILE* registros, Dado* busca, Dado** dados, int *tamanho)
{
	Dado* atual = NULL, *proximoDado = NULL;

	int novoTam = 2, j = 0, quantDado, i; 

	Dado** novosDados = (Dado**)malloc(sizeof(Dado*)*(novoTam));

	atual = busca;

	while(atual)
	{
		proximoDado = leDado(registros, atual->proxPos);

		quantDado = 0; 

		for(i = 0 ; i < *tamanho; i++)
		{
			if(dados[i])
			{
				if(dados[i]->arquivo == atual->arquivo)
				{
					quantDado = 1;

					if(j+1 >= novoTam)
					{
						novoTam *= 2;
						novosDados = realloc(novosDados, sizeof(Dado*)*(novoTam));
					}

					novosDados[j++] = dados[i];
					dados[i] = NULL; 
				}
			}
		}

		if(quantDado)
		{
			if(j+1 >= novoTam)
			{
				novoTam *= 2;
				novosDados = realloc(novosDados, sizeof(Dado*)*(novoTam));
			}
			novosDados[j++] = atual;
		}else
			free(atual);

		atual = proximoDado;
	}

	for(i = 0; i < *tamanho; i++)
		if(dados[i]) 
			free(dados[i]);

	*tamanho = j;
	novosDados = realloc(novosDados, sizeof(Dado*)*(*tamanho));

	return novosDados;
}

///
/// \brief todosOsDados, procura todos os dados proximos do Dado atual
/// \param registros, arquivo aonde estão os dados
/// \param atual, dado atual da palavra
/// \param tamanho, ponteiro para a quantidade de palavras procuradas
/// \return os dados das palavras 
/// \pre nenhuma
/// \post nenhuma
///
Dado** todosOsDados(FILE* registros, Dado* atual, int *tamanho)
{
	int i = 0;
	Dado* palavra = NULL;

	*tamanho = 2;
	Dado **pesquisa = malloc(sizeof(Dado*)*(*tamanho));

	palavra = atual;

	while(palavra)
	{
		if(i+1 >= (*tamanho))
		{
			(*tamanho) *= 2;
			pesquisa = realloc(pesquisa, sizeof(Dado*) * (*tamanho));
		}

		pesquisa[i++] = palavra;
		palavra = leDado(registros, palavra->proxPos);
	}

	(*tamanho) = i;
	pesquisa = realloc(pesquisa, sizeof(Dado*) * (*tamanho));

	return pesquisa;
}

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
void pesquisaEmArq(char**caminhos, int quant, FILE* invertido, FILE* registros, char* palavraDeConsulta[], int quantPalavra)
{
	Dado* busca, **dados = NULL;
	int i, tamanhoDeDados, total;

	if(quantPalavra)
	{
		dados = todosOsDados(registros, procuraDado(invertido, registros, palavraDeConsulta[0]), &tamanhoDeDados);
	}

	for(i = 1; i < quantPalavra; i++)
	{
		busca = procuraDado(invertido, registros, palavraDeConsulta[i]);

		dados = atualizaDados(registros, busca, dados, &tamanhoDeDados);
	}

	if(tamanhoDeDados)
	{
		int duplicados[quant];
		memset(duplicados, 0, sizeof(int)*quant);

		for(total = i = 0; i < tamanhoDeDados; i++)
		{
			if(!duplicados[dados[i]->arquivo - 1])
			{
				total++;
				duplicados[dados[i]->arquivo-1] = 1;
			}
		}

		printf("\nquantidade: %d\n", total);
		printf("documentos: \n");

		for(i = 0; i < tamanhoDeDados; i++)
		{
			if(duplicados[dados[i]->arquivo-1])
			{
				printf("%s\n", caminhos[dados[i]->arquivo-1]);
				duplicados[dados[i]->arquivo-1] = 0;
			}

			free(dados[i]);
		}
	}
	else
	{
		printf("Nao foram encontradas nenhuma entrada\n");
	}

	free(dados);
}

///
/// \brief consultar, função que inicializa a pesquisa nos arquivos de registros, abre os arquivos de registro e de Arvore-B
/// \param caminhos, vetor de strings que contém os diretorios dos arquivos
/// \param quant, quantidade de strings dentro do vetor
/// \pre nenhuma
/// \post nenhuma
///
void consultar(char* caminhos[], int quant)
{
	system("CLS");
	FILE* invertido = fopen("invertido.bin", "rb+");
	if(invertido == NULL) return;

	FILE* registros = fopen("registros.bin", "rb+");
	if(registros == NULL) return;

	Cabecalho *indice = leituraDoCabecalho(invertido);
	ArvoreB* raiz = leituraDoNoh(invertido, indice->raiz);
	int quantPalavra;
	char pesquisa[256], **palavraDeConsulta;

	if(raiz)
	{
		printf("Entre com a(s) palavra(s) a ser(em) consultada(s): ");
		fflush(stdin);
		scanf("%[^\n]%*c", pesquisa);
		palavraDeConsulta = separaPesquisa(pesquisa, &quantPalavra);
		pesquisaEmArq(caminhos, quant, invertido, registros, palavraDeConsulta, quantPalavra);
	}

	fclose(registros);
	fclose(invertido);
}

///
/// \brief operacoes, menu das opções que o programa faz 
/// \param menu, estrutura que contém as informações principais
/// \param palavras, estrutura que guarda as palavras lidas dos arquivos
/// \pre é posto ao usuário qual operação deve ser feita, enquanto tiver uma opção do usuário, o programa continua a executar
/// \post nenhuma
///
void operacoes(Menu* menu)
{
	int opcao;

	do
	{
		system("CLS");
		printf("-------------------------------------------\n");
		printf("| [1] - Imprimir lista de Stop Words      |\n");
		printf("| [2] - Imprimir indice                   |\n");
		printf("| [3] - Consultar                         |\n");
		printf("| [0] - Fechar                            |\n");
		printf("-------------------------------------------\n");
		printf("     Opcao: ");
		scanf("%d%*c", &opcao);

		switch(opcao)
		{
			case 1:
				//chama a função de ordenação e imprime as stopsWords
				quickSort(menu->stopWord, 0, menu->quantStopsWord-1);
				imprimeStopWords(menu->stopWord, menu->quantStopsWord);
				break;
			case 2:
				//imprime a tabela de indices
				imprimeIndices();
				break;
			case 3:
				//chama a função para consultar palavras
				consultar(menu->caminho, menu->quantCaminho);
				break;
			case 0:
			default:
				break;
		}

		getch();

	}while(opcao != 0);
}
