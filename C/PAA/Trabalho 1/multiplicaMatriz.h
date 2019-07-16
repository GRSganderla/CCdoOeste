#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void mult_matriz(int **A, int **B, int **C, int n);

void printa(int **C, int n);

int ** alocaMat(int n);

int potencia(int k);

int calcula_novo_tam(int n);

void soma(int **A, int **B, int **C, int n);

void sub(int **A, int **B, int **C, int n);

void mult_strassen(int **A, int **B, int **C, int n);

int** strassen(int **A, int **B, int n);

void matrizes();