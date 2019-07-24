#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

///
/// \brief mult_matriz, função O(n^3) de multiplicação de matrizes
/// \param A, matriz A
/// \param B, matriz B
/// \param C, matriz C que tera o resultado da multiplicação A*B
/// \param n, ordem das matrizes A, B e C
///
void mult_matriz(int **A, int **B, int **C, int n);
///
/// \brief printa, função que imprime na tela a matriz passada por paramêtro
/// \param C, matriz a ser imprimida na tela
/// \param n, tamanho da matriz, sendo a ordem dela nxn
///
void printa(int **C, int n);
///
/// \brief desaloca, função que remove a alocação da memoria na matriz passada por paramêtro
/// \param mat, matriz a ser desaloca da memória
/// \param n, tamanho da matriz
/// \return NULL para desalocar totalmente a variavel
///
int** desalocaMat(int **mat, int n);
///
/// \brief alocaMat, aloca uma faixa de memória para a matriz de ordem n
/// \param n, tamanho ou ordem da matriz
/// \return matriz alocada de ordem nxn
///
int ** alocaMat(int n);
///
/// \brief potencia, função que calcula o valor de 2 elevado a k
/// \param k, número da potência desejada
/// \return o valor resultante de 2 elevado a k
///
int potencia(int k);
///
/// \brief calcula_novo_tam, função para a regra do algoritmo de strassen, onde a ordem da matriz tem que potência de 2, ex: 1, 2, 4, 8, 16, 32, 64, 128
/// \param n, ordem da matriz atual, valor para determinar qual a potência de 2 vai ser usada como nova ordem da matriz
/// \return nova ordem para as matrizes usadas no algoritmo de strassen
///
int calcula_novo_tam(int n);
///
/// \brief soma, função de soma de matriz que é utilizada no algoritmo de strassen
/// \param A, primeira matriz da soma de matrizes
/// \param B, segunda matriz da soma
/// \param C, matriz que recebe a soma da matriz A com a B
/// \param n, ordem das matrizes A, B e C
///
void soma(int **A, int **B, int **C, int n);
///
/// \brief sub, função auxiliar para o algoritmo de strassen que faz a subtração de duas matrizes
/// \param A, primeira matriz, matriz que sera retirado o valor
/// \param B, segunda matriz, matriz que retirará o valor da primeira matriz
/// \param C, matriz que recebe a subtração de A por B
/// \param n
///
void sub(int **A, int **B, int **C, int n);
///
/// \brief mult_strassen, função principal do algoritmo de strassen, é o que desenvolve as divisões das partes da matriz A e B, e calcula as sub-matrizes
/// \param A, matriz A da função C = AxB
/// \param B, matriz B da função C = AxB
/// \param C, matriz que recebe o produto de A por B
/// \param n, ordem das matrizes passadas por paramêtro, A, B e C
///
void mult_strassen(int **A, int **B, int **C, int n);
///
/// \brief strassen, função inicial do algoritmo de strassen, nele aloca a matriz com o novo tamanho na potência de 2 e chama o metodo de strassen
/// \param A, matriz original A do produto de C = AxB
/// \param B, matriz original B de C = AxB
/// \param n, ordem das matrizes A e B
/// \return matriz C contendo o produto de A por B no tamanho original das matrizes
///
int** strassen(int **A, int **B, int n);
///
/// \brief matrizes, função principal para o problema da multiplicação de matrizes
///
void matrizes(void);
