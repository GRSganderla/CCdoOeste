#include "operacoes.h"
#include "tempo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXINT 2147483647

///
/// \brief inicializa, inicializa todos os parametros da struct ArgumentosCMD
/// \return retorna um tipo de struct ArgumentosCMD* inicializada
/// \pre nenhuma
/// \post nenhuma
///
ArgumentosCMD* inicializa()
{
    //aloca uma variavel do tipo ArgumentosCMD
    ArgumentosCMD* novo = (ArgumentosCMD*)malloc(sizeof(ArgumentosCMD));

    //define todos as variaveis do tipo da estrutura para nulo
    novo->arqEntrada = NULL;
    novo->arqSaida = NULL;
    novo->quantN = 0;
    novo->tipoDado = '\0';
    novo->tipoSort = NULL;

    //retorna a variavel inicializada
    return novo;
}

///
/// \brief pegarArg, pega a palavra da linha de argumento passada por linha de comando
/// \param argv, variavel que contem todos os argumentos passados na linha de comando
/// \return returna a palavra da posição 0 a partir da variavel passada
/// \pre nenhuma
/// \post nenhuma
///
char* pegarArg(char const *argv[])
{
    //retorna a primeira posição convertida em string
    return ((char*)argv[0]);
}

///
/// \brief pegaTipo, pega qual é o tipo de dado a ser usado para ordenar
/// \param argv, variavel que tem guardado os argumentos da linha de comando
/// \return retorna um char do tipo de dado
/// \pre nenhuma
/// \post nenhuma
///
char pegaTipo(char const *argv[])
{
    //retorna o primeiro argumento passado, o tipo do Dado
    return argv[0][0];
}

///
/// \brief linhaDeArgumentos, pega e guarda todas os argumentos passados pela linha de comando
/// \param args, struct que vai guardar as informações da linha de comando
/// \param argv, variavel que guarda os argumentos passados por linha de comando
/// \param argc, tamanho da linha de comando
/// \return retorna uma struct tipo ArgumentosCMD* com o conteudo guardado da linha de comando
/// \pre nenhuma
/// \post nenhuma
///
ArgumentosCMD* linhaDeArgumentos(ArgumentosCMD* args, char const *argv[], int argc)
{
    //pega o primeiro dado
    args->tipoDado = pegaTipo(argv+1);

    //se for do tipo inteiro, pega a conversão da string para inteiro da quantidade de valores que o vetor inteiro deve ter
    if(args->tipoDado == 'N')
        args->quantN = atoi(pegarArg(argv+2));
    else
    {
        //se não for do tipo inteiro, então é do tipo strings, pega o nome do arquivo de entrada
        args->arqEntrada = pegarArg(argv+2);
    }

    //se tiver mais argumentos, pega qual o tipo de algoritmo para ser ordenado
    if(argc > 3)
        args->tipoSort = pegarArg(argv+3);

    //se tive mais argumentos, pega qual o arquivo de saida
    if(argc > 4)
        args->arqSaida = pegarArg(argv+4);

    //retorna os argumentos
    return args;
}

///
/// \brief limpaArg, desaloca a variavel do tipo ArgumentosCMD
/// \param arg, variavel do tipo ArgumentosCMD que vai ser desalocada
/// \pre nenhuma
/// \post a variavel da estrutura ArgumentosCMD vai estar desalocada
///
void limpaArg(ArgumentosCMD *arg)
{
    //limpa o tipo de dado
    arg->tipoDado = '\0';

    //se tiver arquivo de entrada, desaloca o espaço
    if(arg->arqEntrada)
        free(arg->arqEntrada);

    //se tiver arquivo de saida, desaloca o espaço
    if(arg->arqSaida)
        free(arg->arqSaida);

    //se tiver metodo de ordenação, desaloca o espaço
    if(arg->tipoSort)
        free(arg->tipoSort);

    //se tiver tamanho do vetor, limpa a variavel
    if(arg->quantN)
        arg->quantN = 0;

    //desaloca a variavel do tipo ArgumentosCMD
    free(arg);
}

///
/// \brief criaVetor, cria e aloca um vetor que cada um dos seus indices terá um valor aleatório
/// \param tam, tamanho que o vetor irá conter
/// \return retorna um vetor de tamanho tam com cada um do seus indices contendo um numero gerado aleatóriamente
/// \pre nenhuma
/// \post um vetor é alocado com tamanho tam
///
int* criaVetor(int tam)
{
    int i;
    int *vet = (int*)malloc(sizeof(int)*tam);

    //ate o tamanho maximo definido
    for(i = 0; i < tam; i++)
    {
        //atribui um valor aleatorio, como o valor aleatorio ia até um numero baixo, eu adicionei o vezes para aumentar o valor
        vet[i] = (rand() * rand())%MAXINT;
    }

    //retorna o vetor alocado e com valores aleatório atribuidos a ele
    return vet;
}

///
/// \brief determinaOp, determina o dado(N || C) e cria o vetor para o tipo de dado determinado, sendo os valores do vetor sendo gerado aleatóriamente ou de um arquivo.txt
/// \param arg, variavel que contém o tipo de dado e operação a ser feita
/// \pre nenhuma
/// \post nenhuma
///
void determinaDado(ArgumentosCMD* arg)
{
    //se a quantidade for maior que 0, ou seja, tem um tamanho ja definido, e é um inteiro
    if(arg->quantN > 0 && (arg->tipoDado == 'N' || arg->tipoDado == 'n'))
    {
        //cria o vetor e faz chama a função de verificar qual operação a ser feita
        int* vetN;
        vetN = criaVetor(arg->quantN);
        fazOpN(vetN, arg);
    }
    //se não for inteiro
    else if(arg->tipoDado == 'C' || arg->tipoDado == 'c')
    {
        //cria o vetor e chama a função de abertura do arquivo
        char** vet;
        vet = lerArq(arg->arqEntrada, &arg->quantN);
        //verifica qual operação a ser feita
        fazOpC(vet, arg);
    }
}

///
/// \brief fazOpN, verifica qual o tipo de operação a ser feita por dado inteiro, sendo as operações de comparar os tempos de ordenação ou ordenar e guardar em um arquivo
/// \param v, vetor alocado com seus indices com valores aleatórios
/// \param arg, variavel que guarda o tipo de operação que será feita
/// \pre nenhuma
/// \post nenhuma
///
void fazOpN(int v[], ArgumentosCMD* arg)
{
    //se não tiver tipo de ordenação, compara os tempos
    if(arg->tipoSort == NULL)
        comparaTempoN(v, arg->quantN);
    //se tiver tipo de ordenação
    else
    {
        //se não tiver arquivo de saida, avisa e não faz nada
        if(arg->arqSaida == NULL)
            printf("Arquivo de Saida nao selecionado\n");
        else{
            //se tiver, ordena e imprime no arquivo
            imprimeNoArqN(v, arg);
        }
    }
}

///
/// \brief fazOpC, verifica qual o tipo de operação a ser feita por dado de cadeias de caractéres, sendo comparar o tempo de ordenação ou ordenar e guardar em uma arquivo
/// \param v, vetor que tem seus indices as cadeias de caracteres escaneadas do arquivo de entrada
/// \param a, variavel que guarda o tipo de opração que será feita
/// \pre nenhuma
/// \post nenhuma
///
void fazOpC(char* v[], ArgumentosCMD* a)
{
    //se não tiver tipo de ordenação, compara os tempos
    if(a->tipoSort == NULL)
    {
        comparaTempoC(v, a->quantN);
    }

    //se tiver tipo de ordenação
    else
    {
        //se não tiver arquivo de saida, avisa e não faz nada
        if(a->arqSaida == NULL)
        {
            printf("Arquivo de saida nao escolhido!\n");
            return;
        }
        else
            //se tiver, ordena e imprime no arquivo
            imprimeNoArqC(v, a);
    }
}
