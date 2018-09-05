#ifndef CALCULO_H
#define CALCULO_H
#include<stdio.h>
#include<stdlib.h>
#define MAXL 100
#define MAXC 100

float divisao(float a, float b);

void printaMatriz(float a[][MAXC], float b[MAXL], int n);

void gauss(float a[][MAXC], float b[MAXL], float lu[MAXL], int n);

int leAeB(float a[][MAXL], float b[MAXL]);

float* descobreX(float a[][MAXC], float b[], int n);

#endif