#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include "multiplicaMatriz.h"

int LIMITE = 2;

void mult_matriz(int **A, int **B, int **C, int n){

	// C = AxB
	for(int i = 0; i < n; i++){
		
		C[i] = (int*)malloc(sizeof(int)*n);
		for(int j = 0; j < n; j++){
			
			C[i][j] = 0;

			for(int k = 0; k < n; k++){
				
				C[i][j] += A[i][k] * B[k][j];   
			}
		}
	}
}

void printa(int **C, int n){

	for(int i = 0; i < n; i++){
		printf("|");

		for(int j = 0; j < n; j++)
			printf(" %-7d ", C[i][j]);

		printf("|\n");
	}
	printf("\n");
}

int** desaloca(int **mat, int n){

	if(mat == NULL)
		return NULL;

	for(int i = 0; i < n; i++){

		if(mat[i] != NULL){

			free(mat[i]);
			mat[i] = NULL;
		}
	}

	free(mat);
	mat = NULL;

	return (NULL);
}

int ** alocaMat(int n){

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

	if(n == LIMITE){
		
		mult_matriz(A, B, C, n);
	}
	else{

		int novo_n = n/2, i, j;
		
		int **a11 = alocaMat(novo_n), **a12 = alocaMat(novo_n), **a21 = alocaMat(novo_n), **a22 = alocaMat(novo_n);
		int **b11 = alocaMat(novo_n), **b12 = alocaMat(novo_n), **b21 = alocaMat(novo_n), **b22 = alocaMat(novo_n);
		int **c11 = alocaMat(novo_n), **c12 = alocaMat(novo_n), **c21 = alocaMat(novo_n), **c22 = alocaMat(novo_n);
		int **m1 = alocaMat(novo_n), **m2 = alocaMat(novo_n), **m3 = alocaMat(novo_n), **m4 = alocaMat(novo_n), **m5 = alocaMat(novo_n), **m6 = alocaMat(novo_n), **m7 = alocaMat(novo_n);
		int **A_res = alocaMat(novo_n), **B_res = alocaMat(novo_n);

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
		//printf("PASSO 1\n");
		soma(a21, a22, A_res, novo_n);
		mult_strassen(A_res, b11, m2, novo_n);
		//printf("PASSO 2\n");
		sub(b12, b22, B_res, novo_n);
		mult_strassen(a11, B_res, m3, novo_n);
		//printf("PASSO 3\n");
		sub(b21, b11, B_res, novo_n);
		mult_strassen(a22, B_res, m4, novo_n);
		//printf("PASSO 4\n");
		soma(a11, a12, A_res, novo_n);
		mult_strassen(A_res, b22, m5, novo_n);
		//printf("PASSO 5\n");

		sub(a21, a11, A_res, novo_n);
		soma(b11, b12, B_res, novo_n);
		mult_strassen(A_res, B_res, m6, novo_n);
		//printf("PASSO 6\n");

		sub(a12, a22, A_res, novo_n);
		soma(b21, b22, B_res, novo_n);
		mult_strassen(A_res, B_res, m7, novo_n);
		//printf("PASSO 7\n");

		soma(m3, m5, c12, novo_n);
		soma(m2, m4, c21, novo_n);
		//printf("PASSO 8\n");

		soma(m1, m4, A_res, novo_n);
		soma(A_res, m7, B_res, novo_n);;
		sub(B_res, m5, c11, novo_n);
		//printf("PASSO 9\n");

		soma(m1, m3, A_res, novo_n);
		soma(A_res, m6, B_res, novo_n);
		sub(B_res, m2, c22, novo_n);
		//printf("PASSO 10\n");

		for(i = 0; i < novo_n; i++){

			for(j = 0; j < novo_n; j++){

				C[i][j] = c11[i][j];
				C[i][j + novo_n] = c12[i][j];
				C[i + novo_n][j] = c21[i][j];
				C[i + novo_n][j + novo_n] = c22[i][j];
			}
		}
		//printf("PASSO 11\n");

		a11 = desaloca(a11,novo_n);
		a12 = desaloca(a12,novo_n);
		a21 = desaloca(a21,novo_n);
		a22 = desaloca(a22,novo_n);
		b11 = desaloca(b11,novo_n);
		b12 = desaloca(b12,novo_n);
		b21 = desaloca(b21,novo_n);
		b22 = desaloca(b22,novo_n);
		c11 = desaloca(c11,novo_n);
		c12 = desaloca(c12,novo_n);
		c21 = desaloca(c21,novo_n);
		c22 = desaloca(c22,novo_n);
		m1 = desaloca(m1,novo_n);
		m2 = desaloca(m2,novo_n);
		m3 = desaloca(m3,novo_n);
		m4 = desaloca(m4,novo_n);
		m5 = desaloca(m5,novo_n);
		m6 = desaloca(m6,novo_n);
		m7 = desaloca(m7,novo_n);
		A_res = desaloca(A_res,novo_n);
		B_res = desaloca(B_res,novo_n);
	}
}

int** strassen(int **A, int **B, int n){

	int tamanho = n, i, j;

	n = calcula_novo_tam(n);
	printf("%d\n", n);

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
	printf("ALO\n");

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

void matrizes(){

	system("cls");
	float tempoGasto[3];
	FILE* f; 
	int tentativa = 0, n, i, j, lim, **A, **B, **C;
	char entrada[100];

	printf("1 - Algoritmo comum de multiplicacao de matrizes.(O(n^3))\n");
    printf("2 - Algoritmo Strassen de multiplicacao de matrizes.(O(n^2.807))\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
    int opcao;
    
    scanf("%d", &opcao);
    system("cls");

    if(opcao != 0){

    	for(int k = 0; k < 3; k++){
    		
    		system("cls");
    		tentativa = 0;
	    	do {

				if(tentativa > 0){
					
					printf("Arquivo nao existente, tente novamente\n");			
				}

				printf("Entre com o arquivo: ");
				scanf("%s", entrada);
				fflush(stdin);
				f = fopen(entrada, "r+");
				tentativa++;

			} while(f == NULL);
		
			fscanf(f, "n = %d\n", &n);
			fscanf(f, "l = %d\n", &LIMITE);
			printf("%d\n", LIMITE);

			A = (int**)malloc(sizeof(int*)*n);
			B = (int**)malloc(sizeof(int*)*n);
			C = (int**)malloc(sizeof(int*)*n);

			for(i = 0; i < n; i++){

				A[i] = (int*)malloc(sizeof(int)*n);
				
				for(j = 0; j < n; j++){
					fscanf(f, "%d ", &A[i][j]);
				}
			}

			for(i = 0; i < n; i++){

				B[i] = (int*)malloc(sizeof(int)*n);
				
				for(j = 0; j < n; j++){
					fscanf(f, "%d ", &B[i][j]);
				}
			}

			//printa(A, n);
			//printa(B, n);

			clock_t tempo;
			tempo = clock();

		    if(opcao == 1){

		    	mult_matriz(A, B, C, n);
		    }
		    else if(opcao == 2){

		    	C = strassen(A, B, n);
		    }

			tempo = clock() - tempo;
			tempoGasto[k] = ((float)tempo)/CLOCKS_PER_SEC;

		    //printa(C, n);

		    printf("Tempo de execucao foi de %f ms\n", tempoGasto[k]);
		    fclose(f);

		   	getchar();
    	}

    	system("cls");
    	printf("Tempo das 3 instancias:\n");
    	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
    	printf("Tempo da instancia 1: %lf\n", tempoGasto[0]);
    	printf("Tempo da instancia 2: %lf\n", tempoGasto[1]);
    	printf("Tempo da instancia 3: %lf\n", tempoGasto[2]);
    	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
    	getchar();
    }
}