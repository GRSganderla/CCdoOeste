#include<stdio.h>
#include<stdlib.h>

#include "problemaDaMochila.h"



int K(Objeto *ob, int W, int n){

	int i, j;

	for(i = 1; i < n+1; i++){

		for(j = 0; j <= W; j++){

			if(ob[i-1].w <= j && ((s[i-1][j - ob[i-1].w] + ob[i-1].c) > s[i-1][j])){

				s[i][j] = s[i-1][j - ob[i-1].w] + ob[i-1].c;
				aux_x[i-1][j] = 1;
			}
			else{

				s[i][j] = s[i-1][j];
				aux_x[i-1][j] = 0;
			}
		}
	}

	j = W;

	for(i = n-1; i >= 0; i--){

		if(aux_x[i][j] == 1){

			x[i] = 1;
			j -= ob[i].w;
		}
		else
			x[i] = 0;
	}

	return s[n][W];
}	

void aloca(int n, int W){

	int i, j;

	aux_x = (int**)malloc(sizeof(int*)*n);
	x = (int*)malloc(sizeof(int)*n);
	s = (int**)malloc(sizeof(int*)*(n+1));

	for(i = 0; i < n+1; i++){

		aux_x[i] = (int*)malloc(sizeof(int)*(W));
		s[i] = (int*)malloc(sizeof(int)*(W+1));

		for(j = 0; j < W+1; j++){
			s[i][j] = 0;
			aux_x[i][j] = 0;
		}
	}
}

void mochila(){

	system("cls");
	FILE* f; 
	int tentativa = 0, n, i, j, solucao, W;
	Objeto *ob;
	char entrada[100];

	printf("1 - Algoritmo com a tecnica de Programacao Dinamica\n");
    printf("2 - Algoritmo com tentativa e erro. (Backtracking)\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
    
    int opcao;
    scanf("%d", &opcao);

    if(opcao != 0){

		for(int k = 0; k < 3; k++){
			
			system("cls");
			tentativa = 0;

		    do{
				if(tentativa > 0){
					
					printf("Arquivo nao existente, tente novamente\n");			
				}

				printf("Entre com o arquivo: ");
				scanf("%s", entrada);
				fflush(stdin);
				f = fopen(entrada, "r+");
				tentativa++;

			} while(f == NULL);
			
			fscanf(f, "W = %d\n", &W);
			fscanf(f, "n = %d", &n);
			aloca(n, W);
			

			ob = (Objeto*)malloc(sizeof(Objeto)*n);

			for(i = 0; i < n; i++)
				fscanf(f, "%d %d", &ob[i].w, &ob[i].c);
		    
		    printf("\n");
		    for(i = 0; i < n; ++i){

		    	printf("Objeto[%d]: ", i);
		    	printf("\tPeso: %d; Valor: %d;\n", ob[i].w, ob[i].c);
		    }
		    printf("\n");
			
			if(opcao == 1){

	    		solucao = K(ob, W, n);
	   		}
	    	else if(opcao == 2){

	    		/*backtracking;*/
	    	}

		    printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
			printf("Vetor solucao = x: {");

			for(i = 0; i < n; i++){

				printf(" %d ", x[i]);
			}
			printf("}\n");

			printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
			printf("Valor maximo atingido = %d\n", solucao);
			printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n");
			
			printf("Matriz dos valores: \n");
			for(int i = 0; i < n+1; i++){
				
				printf("|");

				for(int j = 0; j < W+1; j++)
					printf(" %-7d ", s[i][j]);

				printf("|\n");
			}
			printf("\n");

			getchar();

			fclose(f);
		}
	}
}