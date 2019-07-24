#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include "multiplicaMatriz.h"

///
/// \brief mult_matriz, função O(n^3) de multiplicação de matrizes
/// \param A, matriz A
/// \param B, matriz B
/// \param C, matriz C que tera o resultado da multiplicação A*B
/// \param n, ordem das matrizes A, B e C
///
void mult_matriz(int **A, int **B, int **C, int n){

    //percorre a ordem nxn das matrizes
	for(int i = 0; i < n; i++){

        //aloca a memoria para as colunas da linha i
        C[i] = (int*)malloc(sizeof(int)*(unsigned long long)n);
		for(int j = 0; j < n; j++){
			
            //inicializa o elemento cij
			C[i][j] = 0;

            //multiplica o elemento da linha da matriz A pelo elemento da coluna da matriz B
			for(int k = 0; k < n; k++){
				
				C[i][j] += A[i][k] * B[k][j];   
			}
		}
	}
}

///
/// \brief printa, função que imprime na tela a matriz passada por paramêtro
/// \param C, matriz a ser imprimida na tela
/// \param n, tamanho da matriz, sendo a ordem dela nxn
///
void printa(int **C, int n){

    //para cada linha
	for(int i = 0; i < n; i++){
		printf("|");
        //para cada coluna
		for(int j = 0; j < n; j++)
			printf(" %-7d ", C[i][j]);

		printf("|\n");
	}
	printf("\n");
}

///
/// \brief desaloca, função que remove a alocação da memoria na matriz passada por paramêtro
/// \param mat, matriz a ser desaloca da memória
/// \param n, tamanho da matriz
/// \return NULL para desalocar totalmente a variavel
///
int** desalocaMat(int **mat, int n){

    //se não esta alocada, retorna nulo
	if(mat == NULL)
		return NULL;

    //para cada linha da matriz
	for(int i = 0; i < n; i++){

        //se esta alocada
		if(mat[i] != NULL){

            //desaloca e atribui nulo a linha da matriz
			free(mat[i]);
			mat[i] = NULL;
		}
	}

    //desaloca a variavel completamente e atribui nulo
	free(mat);
	mat = NULL;

	return (NULL);
}

///
/// \brief alocaMat, aloca uma faixa de memória para a matriz de ordem n
/// \param n, tamanho ou ordem da matriz
/// \return matriz alocada de ordem nxn
///
int ** alocaMat(int n){

    //aloca as linha para a matriz
    int **matriz = (int**)malloc(sizeof(int*)*(unsigned long long)n);

    //para cada linha
	for(int i = 0; i < n; i++){

        //aloca as colunas da matriz
        matriz[i] = (int*)malloc(sizeof(int)*(unsigned long long)n);
	}

    //retorna a matriz alocada
	return matriz;
}

///
/// \brief potencia, função que calcula o valor de 2 elevado a k
/// \param k, número da potência desejada
/// \return o valor resultante de 2 elevado a k
///
int potencia(int k){

    //inicializa a potência em 1 para o caso base 2^0 = 1
	int p = 1;

    //de 0 até k-1
	for(int i = 0; i < k; i++){

        //duplica o valor de p
		p = 2 * p; 
	}

    //retorna a potência
	return p;
}

///
/// \brief calcula_novo_tam, função para a regra do algoritmo de strassen, onde a ordem da matriz tem que potência de 2, ex: 1, 2, 4, 8, 16, 32, 64, 128
/// \param n, ordem da matriz atual, valor para determinar qual a potência de 2 vai ser usada como nova ordem da matriz
/// \return nova ordem para as matrizes usadas no algoritmo de strassen
///
int calcula_novo_tam(int n){

    //variavel que contera o novo tamanho
	int alvo = 1;

    //enquanto não achou a potência de 2 que seja maior que n
	while(n > potencia(alvo)){

        //aumenta o valor da potência de 2
		alvo += 1;
	}

    //retorna a potência de 2 maior que n
	return potencia(alvo); 
}

///
/// \brief soma, função de soma de matriz que é utilizada no algoritmo de strassen
/// \param A, primeira matriz da soma de matrizes
/// \param B, segunda matriz da soma
/// \param C, matriz que recebe a soma da matriz A com a B
/// \param n, ordem das matrizes A, B e C
///
void soma(int **A, int **B, int **C, int n){

    //para cada linha e coluna, soma o elemento aij com o elemento bij
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			C[i][j] = A[i][j] + B[i][j];
}

///
/// \brief sub, função auxiliar para o algoritmo de strassen que faz a subtração de duas matrizes
/// \param A, primeira matriz, matriz que sera retirado o valor
/// \param B, segunda matriz, matriz que retirará o valor da primeira matriz
/// \param C, matriz que recebe a subtração de A por B
/// \param n
///
void sub(int **A, int **B, int **C, int n){

    //para cada linha e coluna, diminui o elemento aij pelo elemento bij
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			C[i][j] = A[i][j] - B[i][j];
}

///
/// \brief mult_strassen, função principal do algoritmo de strassen, é o que desenvolve as divisões das partes da matriz A e B, e calcula as sub-matrizes
/// \param A, matriz A da função C = AxB
/// \param B, matriz B da função C = AxB
/// \param C, matriz que recebe o produto de A por B
/// \param n, ordem das matrizes passadas por paramêtro, A, B e C
///
void mult_strassen(int **A, int **B, int **C, int n){

    //se o tamanho da matriz atingiu o limite de recursão
    if(n == 1){
		
        //multiplica A11 por B11 colocando o resultado em C11 -> alternativa 1
        C[0][0] = A[0][0] * B[0][0];

        //chama o metódo normal de multiplicação -> alternativa 2
        //mult_matriz(A, B, C, n);
	}
	else{
		
        int novo_n = n/2, i, j;
        //aloca as subdivisões das matriz A, B e C com um novo tamanho, sendo a metade das matrizes
		int **a11 = alocaMat(novo_n), **a12 = alocaMat(novo_n), **a21 = alocaMat(novo_n), **a22 = alocaMat(novo_n);
		int **b11 = alocaMat(novo_n), **b12 = alocaMat(novo_n), **b21 = alocaMat(novo_n), **b22 = alocaMat(novo_n);
		int **c11 = alocaMat(novo_n), **c12 = alocaMat(novo_n), **c21 = alocaMat(novo_n), **c22 = alocaMat(novo_n);
		int **m1 = alocaMat(novo_n), **m2 = alocaMat(novo_n), **m3 = alocaMat(novo_n), **m4 = alocaMat(novo_n), **m5 = alocaMat(novo_n), **m6 = alocaMat(novo_n), **m7 = alocaMat(novo_n);
		int **A_res = alocaMat(novo_n), **B_res = alocaMat(novo_n);

        //para cada linha da nova ordem das matrizes
		for(i = 0; i < novo_n; i++){

            //para cada coluna da nova ordem das matrizes
			for (j = 0; j < novo_n; j++){

                //as subdivisões da matriz A recebe os valores da matriz A de cada divisão
				a11[i][j] = A[i][j];
				a12[i][j] = A[i][j + novo_n];
				a21[i][j] = A[i + novo_n][j];
				a22[i][j] = A[i + novo_n][j + novo_n];
                //as subdivisões da matriz B recebem a parte da matriz B
				b11[i][j] = B[i][j];
				b12[i][j] = B[i][j + novo_n];
				b21[i][j] = B[i + novo_n][j];
				b22[i][j] = B[i + novo_n][j + novo_n];
			}
		}

        //m1 = (a11 + a22)*(b11 + b22)
		soma(a11, a22, A_res, novo_n);
		soma(b11, b22, B_res, novo_n);
        mult_strassen(A_res, B_res, m1, novo_n);

        //m2 = (a21 + a22)*b11
		soma(a21, a22, A_res, novo_n);
        mult_strassen(A_res, b11, m2, novo_n);

        //m3 = a11*(b12 - b22)
		sub(b12, b22, B_res, novo_n);
        mult_strassen(a11, B_res, m3, novo_n);

        //m4 = a22*(b21 - b11)
		sub(b21, b11, B_res, novo_n);
        mult_strassen(a22, B_res, m4, novo_n);

        //m5 = (a11 + a12)*b22
		soma(a11, a12, A_res, novo_n);
        mult_strassen(A_res, b22, m5, novo_n);

        //m6 = (a21 - a11)*(b11 - b12)
		sub(a21, a11, A_res, novo_n);
		soma(b11, b12, B_res, novo_n);
        mult_strassen(A_res, B_res, m6, novo_n);

        //m7 = (a12 - a22)*(b21 + b22)
		sub(a12, a22, A_res, novo_n);
		soma(b21, b22, B_res, novo_n);
        mult_strassen(A_res, B_res, m7, novo_n);

        //c12 = m3 + m5
		soma(m3, m5, c12, novo_n);
        //c21 = m2 + m4
        soma(m2, m4, c21, novo_n);

        //c11 = m1 + m4 - m5 + m7
		soma(m1, m4, A_res, novo_n);
		soma(A_res, m7, B_res, novo_n);;
        sub(B_res, m5, c11, novo_n);

        //c22 = m1 - m2 + m3 + m6
		soma(m1, m3, A_res, novo_n);
		soma(A_res, m6, B_res, novo_n);
        sub(B_res, m2, c22, novo_n);

        //para cada linha da nova ordem
		for(i = 0; i < novo_n; i++){

            //para cada coluna da nova ordem
			for(j = 0; j < novo_n; j++){

                //matriz C recebe a suas respectivas subdivisões
				C[i][j] = c11[i][j];
				C[i][j + novo_n] = c12[i][j];
				C[i + novo_n][j] = c21[i][j];
				C[i + novo_n][j + novo_n] = c22[i][j];
			}
        }

        //desaloca todas as outras matriz usadas
        a11 = desalocaMat(a11,novo_n);
        a12 = desalocaMat(a12,novo_n);
        a21 = desalocaMat(a21,novo_n);
        a22 = desalocaMat(a22,novo_n);
        b11 = desalocaMat(b11,novo_n);
        b12 = desalocaMat(b12,novo_n);
        b21 = desalocaMat(b21,novo_n);
        b22 = desalocaMat(b22,novo_n);
        c11 = desalocaMat(c11,novo_n);
        c12 = desalocaMat(c12,novo_n);
        c21 = desalocaMat(c21,novo_n);
        c22 = desalocaMat(c22,novo_n);
        m1 = desalocaMat(m1,novo_n);
        m2 = desalocaMat(m2,novo_n);
        m3 = desalocaMat(m3,novo_n);
        m4 = desalocaMat(m4,novo_n);
        m5 = desalocaMat(m5,novo_n);
        m6 = desalocaMat(m6,novo_n);
        m7 = desalocaMat(m7,novo_n);
        A_res = desalocaMat(A_res,novo_n);
        B_res = desalocaMat(B_res,novo_n);
	}
}

///
/// \brief strassen, função inicial do algoritmo de strassen, nele aloca a matriz com o novo tamanho na potência de 2 e chama o metodo de strassen
/// \param A, matriz original A do produto de C = AxB
/// \param B, matriz original B de C = AxB
/// \param n, ordem das matrizes A e B
/// \return matriz C contendo o produto de A por B no tamanho original das matrizes
///
int** strassen(int **A, int **B, int n){

    //guardar a ordem original das matrizes
	int tamanho = n, i, j;

    //calcula a potência que é maior que a ordem atual
    n = calcula_novo_tam(n);
    printf("Novo tamanho para as matrizes = %d\n", n);

    //aloca as novas matrizes com a nova ordem
    int **a = (int**)malloc(sizeof(int*)*(unsigned long long)n), **b = (int**)malloc(sizeof(int*)*(unsigned long long)n), **c = (int**)malloc(sizeof(int*)*(unsigned long long)n);

    //para cada linha
	for(i = 0; i < n; i++){

        //aloca as colunas
        a[i] = (int*)malloc(sizeof(int)*(unsigned long long)n);
		for(j = 0; j < n; j++){
            //se o indice da matriz não pertence a ordem original da matriz A, recebe 0
			if(i >= tamanho || j >= tamanho){

				a[i][j] = 0;
			}
			else
				a[i][j] = A[i][j];
		}
	}

    //para cada linha
	for(i = 0; i < n; i++){
        //aloca as colunas
        b[i] = (int*)malloc(sizeof(int)*(unsigned long long)n);
		for(j = 0; j < n; j++){
            //se o indice da matriz não pertence a ordem original da matriz A, recebe 0
			if(i >= tamanho || j >= tamanho)
				b[i][j] = 0;
			else
				b[i][j] = B[i][j];
		}
	}
    //para cada linha
	for(i = 0; i < n; i++){
        //aloca as colunas
        c[i] = (int*)malloc(sizeof(int)*(unsigned long long)n);
        //coloca 0 em todos os elementos da matriz c
		for(j = 0; j < n; j++){

			c[i][j] = 0;
		}
	}
    //chama o metodo do produto AxB
    mult_strassen(a, b, c, n);

    //se o tamanho original das matriz não é o mesmo da nova ordem, a nova ordem volta a ser o tamanho original
	if(tamanho < n){
		n = tamanho;
	}

    //aloca a matriz C com a ordem original
    int **C = (int**)malloc(sizeof(int*)*(unsigned long long)n);

    //para cada linha
	for(i = 0; i < n; i++){

        //aloca as colunas
        C[i] = (int*)malloc(sizeof(int)*(unsigned long long)n);
        //coloca cada elemento em seu respectivo indice
		for(j = 0; j < n; j++){

			C[i][j] = c[i][j];
		}
	}

	return C;
}

///
/// \brief matrizes, função principal para o problema da multiplicação de matrizes
///
void matrizes(){

	system("cls");
    double tempoGasto[3];
	FILE* f; 
    int tentativa = 0, n[3], i, j, **A, **B, **C;
	char entrada[100];

    //menu de escolha de algoritmo
	printf("1 - Algoritmo comum de multiplicacao de matrizes.(O(n^3))\n");
    printf("2 - Algoritmo Strassen de multiplicacao de matrizes.(O(n^2.807))\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
    int opcao;
    
    scanf("%d", &opcao);
    system("cls");

    if(opcao > 0 && opcao < 3){

        //para cada instância das 3
    	for(int k = 0; k < 3; k++){
    		
    		system("cls");
    		tentativa = 0;
            //continua lendo o nome do arquivo até que o arquivo certo seja aberto
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
		
            //pega a ordem e limite de recursão
            fscanf(f, "n = %d\n", &n[k]);
            printf("Tamanho da matriz = %d\n", n[k]);

            //aloca as matrizes A, B e C
            A = (int**)malloc(sizeof(int*)*(unsigned long long)n[k]);
            B = (int**)malloc(sizeof(int*)*(unsigned long long)n[k]);
            C = (int**)malloc(sizeof(int*)*(unsigned long long)n[k]);

            for(i = 0; i < n[k]; i++){

                A[i] = (int*)malloc(sizeof(int)*(unsigned long long)n[k]);
				
                for(j = 0; j < n[k]; j++){
					fscanf(f, "%d ", &A[i][j]);
				}
			}

            for(i = 0; i < n[k]; i++){

                B[i] = (int*)malloc(sizeof(int)*(unsigned long long)n[k]);
				
                for(j = 0; j < n[k]; j++){
					fscanf(f, "%d ", &B[i][j]);
				}
			}

            //imprime as matrizes na tela
            //printa(A, n[k]);
            //printa(B, n[k]);

            //para calcular o tempo
			clock_t tempo;
			tempo = clock();

            //chama o algoritmo de produto de matriz com a opção desejada
		    if(opcao == 1){

                mult_matriz(A, B, C, n[k]);
		    }
		    else if(opcao == 2){

                C = strassen(A, B, n[k]);
            }

            //calcula o tempo de execução
			tempo = clock() - tempo;
            tempoGasto[k] = ((double)tempo)/CLOCKS_PER_SEC;

            //imprime a matriz resultado
            //printa(C, n[k);

            //imprime o resultado do tempo de execução e fecha o arquivo
            printf("Tempo de execucao foi de %lf s\n", tempoGasto[k]);
		    fclose(f);

		   	getchar();
    	}

        //mostra o tamanho da instância e o tempo de execução do algoritmo com essa intância
        system("cls");
        printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
        printf("| Instancia  | Tamanho da instancia | Tempo(s)      |\n");
        printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
        printf("|     1      |        %-13d |  %-13.4lf|\n", n[0], tempoGasto[0]);
        printf("|     2      |        %-13d |  %-13.4lf|\n", n[1], tempoGasto[1]);
        printf("|     3      |        %-13d |  %-13.4lf|\n", n[2], tempoGasto[2]);
        printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
    }
}
