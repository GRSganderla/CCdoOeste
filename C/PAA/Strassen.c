#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include "MultiplicaMatriz.c"

int MAX = 32;

void printa(int **C, int n){

	for(int i = 0; i < n; i++){
		printf("|");

		for(int j = 0; j < n; j++)
			printf(" %-7d ", C[i][j]);

		printf("|\n");
	}
	printf("\n");
}

int ** aloca(int n){

	int **matriz = (int**)malloc(sizeof(int*)*n);

	for(int i = 0; i < n; i++){

		matriz[i] = (int*)malloc(sizeof(int)*n);
	}

	return matriz;
}

int potencia(int k){

	int p = 1;

	for(int i = 0; i < k; i++){

		p = 2 * p; 
	}

	return p;
}

int calcula_novo_tam(int n){

	int alvo = 1;

	while(n > potencia(alvo)){

		alvo += 1;
	}

	return potencia(alvo); 
}

void soma(int **A, int **B, int **C, int n){

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			C[i][j] = A[i][j] + B[i][j];
}

void sub(int **A, int **B, int **C, int n){

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			C[i][j] = A[i][j] - B[i][j];
}

void mult_strassen(int **A, int **B, int **C, int n){

	if(n == 2){

		mult_matriz(A, B, C, n);
	}
	else{

		int novo_n = n/2, i, j;
		int **a11 = aloca(novo_n), **a12 = aloca(novo_n), **a21 = aloca(novo_n), **a22 = aloca(novo_n);
		int **b11 = aloca(novo_n), **b12 = aloca(novo_n), **b21 = aloca(novo_n), **b22 = aloca(novo_n);
		int **c11 = aloca(novo_n), **c12 = aloca(novo_n), **c21 = aloca(novo_n), **c22 = aloca(novo_n);
		int **m1 = aloca(novo_n), **m2 = aloca(novo_n), **m3 = aloca(novo_n), **m4 = aloca(novo_n), **m5 = aloca(novo_n), **m6 = aloca(novo_n), **m7 = aloca(novo_n);
		int **A_res = aloca(novo_n), **B_res = aloca(novo_n);

		for(i = 0; i < novo_n; i++){

			for (j = 0; j < novo_n; j++){

				a11[i][j] = A[i][j];
				a12[i][j] = A[i][j + novo_n];
				a21[i][j] = A[i + novo_n][j];
				a22[i][j] = A[i + novo_n][j + novo_n];

				b11[i][j] = B[i][j];
				b12[i][j] = B[i][j + novo_n];
				b21[i][j] = B[i + novo_n][j];
				b22[i][j] = B[i + novo_n][j + novo_n];
			}
		}

		soma(a11, a22, A_res, novo_n);
		soma(b11, b22, B_res, novo_n);
		mult_strassen(A_res, B_res, m1, novo_n);

		soma(a21, a22, A_res, novo_n);
		mult_strassen(A_res, b11, m2, novo_n);

		sub(b12, b22, B_res, novo_n);
		mult_strassen(a11, B_res, m3, novo_n);

		sub(b21, b11, B_res, novo_n);
		mult_strassen(a22, B_res, m4, novo_n);

		soma(a11, a12, A_res, novo_n);
		mult_strassen(A_res, b22, m5, novo_n);

		sub(a21, a11, A_res, novo_n);
		soma(b11, b12, B_res, novo_n);
		mult_strassen(A_res, B_res, m6, novo_n);

		sub(a12, a22, A_res, novo_n);
		soma(b21, b22, B_res, novo_n);
		mult_strassen(A_res, B_res, m7, novo_n);

		soma(m3, m5, c12, novo_n);
		soma(m2, m4, c21, novo_n);

		soma(m1, m4, A_res, novo_n);
		soma(A_res, m7, B_res, novo_n);;
		sub(B_res, m5, c11, novo_n);

		soma(m1, m3, A_res, novo_n);
		soma(A_res, m6, B_res, novo_n);
		sub(B_res, m2, c22, novo_n);

		for(i = 0; i < novo_n; i++){

			for(j = 0; j < novo_n; j++){

				C[i][j] = c11[i][j];
				C[i][j + novo_n] = c12[i][j];
				C[i + novo_n][j] = c21[i][j];
				C[i + novo_n][j + novo_n] = c22[i][j];
			}
		}
	}
}

int** prepara_mat(int **A, int **B, int n){

	int tamanho = n, i, j;

	n = calcula_novo_tam(n);

	int **a = (int**)malloc(sizeof(int*)*n), **b = (int**)malloc(sizeof(int*)*n), **c = (int**)malloc(sizeof(int*)*n);

	for(i = 0; i < n; i++){

		a[i] = (int*)malloc(sizeof(int)*n);
		for(j = 0; j < n; j++){

			if(i >= tamanho || j >= tamanho){

				a[i][j] = 0;
			}
			else
				a[i][j] = A[i][j];
		}
	}

	for(i = 0; i < n; i++){

		b[i] = (int*)malloc(sizeof(int)*n);
		for(j = 0; j < n; j++){

			if(i >= tamanho || j >= tamanho)
				b[i][j] = 0;
			else
				b[i][j] = B[i][j];
		}
	}

	for(i = 0; i < n; i++){

		c[i] = (int*)malloc(sizeof(int)*n);
		
		for(j = 0; j < n; j++){

			c[i][j] = 0;
		}
	}

	mult_strassen(a, b, c, n);

	if(tamanho < n){
		n = tamanho;
	}

	int **C = (int**)malloc(sizeof(int*)*n);

	for(i = 0; i < n; i++){

		C[i] = (int*)malloc(sizeof(int)*n);
		
		for(j = 0; j < n; j++){

			C[i][j] = c[i][j];
		}
	}

	return C;
}

int main(){

	int n = MAX = 3, o = 1;
	int **A = (int**)malloc(sizeof(int*)*n), **B = (int**)malloc(sizeof(int*)*n), **C;

	for(int i = 0; i < n; i++){

		A[i] = (int*)malloc(sizeof(int)*n);
		for(int j = 0; j < n; j++)
			A[i][j] = o++;
	}
	printf("A:\n");
	printa(A, n);
	for(int i = 0; i < n; i++){

		B[i] = (int*)malloc(sizeof(int)*n);
		for(int j = 0; j < n; j++)
			B[i][j] = o++;
	}
	printf("B:\n");
	printa(B, n);
	
    C = prepara_mat(A, B, n);

    printf("C = AxB\n");
	
    printa(C, n);

	return 0;
}