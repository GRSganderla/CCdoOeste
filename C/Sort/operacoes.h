#ifndef OPERACAO_H
#define OPERACAO_H

#include "ordenacao.h"

//struct que guarda os argumentos da linha de comando
typedef struct argumentos
{
    //guarda se é N ou C
    char tipoDado;
    //arquivo que será aberto e escaneado se o tipo de dado for C
    char* arqEntrada;
    //arquivo de saida se o usuário deseja guardar o vetor ordenado por um algoritmo de ordenação
    char* arqSaida;
    //guarda o tipo de algoritmo a ser usado para ordenar, se for nulo, compara o tempo de ordenação
    char* tipoSort;
    //quantidade de caracteres lidos ou quantidade de numeros para ser gerado aleatoriamente e colocado no vetor de numeros
    int quantN;
}ArgumentosCMD;

///
/// \brief inicializa, inicializa todos os parametros da struct ArgumentosCMD
/// \return retorna um tipo de struct ArgumentosCMD* inicializada
/// \pre nenhuma
/// \post nenhuma
///
ArgumentosCMD* inicializa();

///
/// \brief pegarArg, pega a palavra da linha de argumento passada por linha de comando
/// \param argv, variavel que contem todos os argumentos passados na linha de comando
/// \return returna a palavra da posição 0 a partir da variavel passada
/// \pre nenhuma
/// \post nenhuma
///
char* pegarArg(char const *argv[]);

///
/// \brief linhaDeArgumentos, pega e guarda todas os argumentos passados pela linha de comando
/// \param args, struct que vai guardar as informações da linha de comando
/// \param argv, variavel que guarda os argumentos passados por linha de comando
/// \param argc, tamanho da linha de comando
/// \return retorna uma struct tipo ArgumentosCMD* com o conteudo guardado da linha de comando
/// \pre nenhuma
/// \post nenhuma
///
ArgumentosCMD* linhaDeArgumentos(ArgumentosCMD* args, char const *argv[], int argc);

///
/// \brief pegaTipo, pega qual é o tipo de dado a ser usado para ordenar
/// \param argv, variavel que tem guardado os argumentos da linha de comando
/// \return retorna um char do tipo de dado
/// \pre nenhuma
/// \post nenhuma
///
char pegaTipo(char const *argv[]);

///
/// \brief limpaArg, desaloca a variavel do tipo ArgumentosCMD
/// \param arg, variavel do tipo ArgumentosCMD que vai ser desalocada
/// \pre nenhuma
/// \post a variavel da estrutura ArgumentosCMD vai estar desalocada
///
void limpaArg(ArgumentosCMD *arg);

///
/// \brief criaVetor, cria e aloca um vetor que cada um dos seus indices terá um valor aleatório
/// \param tam, tamanho que o vetor irá conter
/// \return retorna um vetor de tamanho tam com cada um do seus indices contendo um numero gerado aleatóriamente
/// \pre nenhuma
/// \post um vetor é alocado com tamanho tam
///
int* criaVetor(int tam);

///
/// \brief determinaOp, determina o dado(N || C) e cria o vetor para o tipo de dado determinado, sendo os valores do vetor sendo gerado aleatóriamente ou de um arquivo.txt
/// \param arg, variavel que contém o tipo de dado e operação a ser feita
/// \pre nenhuma
/// \post nenhuma
///
void determinaDado(ArgumentosCMD* arg);

///
/// \brief fazOpN, verifica qual o tipo de operação a ser feita por dado inteiro, sendo as operações de comparar os tempos de ordenação ou ordenar e guardar em um arquivo
/// \param v, vetor alocado com seus indices com valores aleatórios
/// \param arg, variavel que guarda o tipo de operação que será feita
/// \pre nenhuma
/// \post nenhuma
///
void fazOpN(int v[], ArgumentosCMD* arg);

///
/// \brief fazOpC, verifica qual o tipo de operação a ser feita por dado de cadeias de caractéres, sendo comparar o tempo de ordenação ou ordenar e guardar em uma arquivo
/// \param v, vetor que tem seus indices as cadeias de caracteres escaneadas do arquivo de entrada
/// \param a, variavel que guarda o tipo de opração que será feita
/// \pre nenhuma
/// \post nenhuma
///
void fazOpC(char* v[], ArgumentosCMD* a);

#endif // OPERACAO_H
