#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "problemaDaMochila.h"

//variaveis para o vetor de valores finais, auxiliares do vetor de solução, o vetor solução final, o valor final e o peso final
static int **s, **aux_x, *x, valor_final, peso_final;

///
/// \brief pesos, função que calcula o peso total do objetos dentro da mochila
/// \param n, quantidade de itens
/// \param temp, vetor de solução binario, diz se o item está totalmente ou não na mochila
/// \param ob, vetor com os itens e seus valores e pesos
/// \return o peso total dos itens na mochila
///
int pesos(int n, int *temp, Objeto* ob, int W){

    int resultado = 0;

    for(int i = 0; i < n; i++){

        if(resultado < W && ((resultado += temp[i] * ob[i].w) < W))
            resultado += temp[i] * ob[i].w;
        else
            return 0;
    }

    return 1;
}

///
/// \brief atualiza, função que o valor final dos itens na mochila, o peso total desses itens e o vetor solução final
/// \param ob, vetor com os itens
/// \param n, quantidade de itens
/// \param temp, vetor de solução com os valores binarios de se o item está ou não na mochila
///
void atualiza(Objeto *ob, int n, int *temp){

    int peso_total = 0;
    int valor_total = 0;

    //para cada item
    for(int i = 0; i < n; i++){

        //se o item está na mochila
        if(temp[i] == 1){

            //coloca o peso e valor no total
            peso_total += ob[i].w;
            valor_total += ob[i].c;
        }
    }

    //se o valor novo calculado for maior do que o valor total que antes era o maior
    if(valor_total > valor_final){

        //o vetor solução final recebe o vetor solução atual
        for(int i = 0; i < n; i++){

            x[i] = temp[i];
        }

        //atualiza os valores e pesos finais da solução
        valor_final = valor_total;
        peso_final = peso_total;
    }
}

///
/// \brief backtracking, função principal do problema da mochila com backtracking
/// \param ob, vetor de itens
/// \param W, capacidade total da mochila
/// \param i, indice do intervalo que está verificando, começa vendo o ultimo, depois o ultimo com o penultimo, após isso verifica o ultimo com o penultimo e o antepenultimo...
/// \param n, quantidade de itens
/// \param tempX, vetor solução temporario atual
///
void backtracking(Objeto *ob, int W, int i, int n, int *tempX){

    tempX[i] = -1;

    while(tempX[i] < 1){
        tempX[i] += 1;

        if((pesos(n, tempX, ob, W)) && i == n-1){

            atualiza(ob, n, tempX);
        }

        else if(i < n-1){

            backtracking(ob, W, i+1, n, tempX);
        }
    }

}

///
/// \brief prog_dinamica, função para o problema da mochila com técnica de programação dinâmica
/// \param ob, vetor de itens
/// \param W, capacidade maxima da mochila
/// \param n, quantidade de itens
/// \return o maior valor possivel conseguido colocando os itens que juntos não tem peso maior que a capacidade maxima da mochila
///
int prog_dinamica(Objeto *ob, int W, int n){

	int i, j;

    //para cada item
	for(i = 1; i < n+1; i++){

        //para cada peso até o maximo da mochila
		for(j = 0; j <= W; j++){

            //se o peso do item atual não é maior que o peso maximo e o valor do elemento da matriz de valores possiveis do item anterior com o peso atual menos o peso daquele item for maior que a atual
			if(ob[i-1].w <= j && ((s[i-1][j - ob[i-1].w] + ob[i-1].c) > s[i-1][j])){
                //o item atual com o peso atual recebe o valor do item anterior de peso menos que o peso do item anterior mais o valor do item anterior
				s[i][j] = s[i-1][j - ob[i-1].w] + ob[i-1].c;
                //vetor solução temporario considera item inserido
				aux_x[i-1][j] = 1;
			}
			else{

                //o elemento do item atual com o peso atual recebe o valor do item anterior com o peso atual
				s[i][j] = s[i-1][j];
                //vetor solução não considera item inserido
				aux_x[i-1][j] = 0;
			}
		}
	}

	j = W;
    //para cada item
	for(i = n-1; i >= 0; i--){

        //se o item ta inserido quando o peso ta no maximo
		if(aux_x[i][j] == 1){

            //vetor solução final recebe 1 para o item atual
			x[i] = 1;
            //peso final é aumentado pelo peso do item
            peso_final += ob[i].w;
            //diminui o peso atual
			j -= ob[i].w;
		}
		else
			x[i] = 0;
	}

    //retorna o valor maximo para essa quantidade de item com essa capacidade de peso maximo
	return s[n][W];
}	

///
/// \brief desaloca, função que desaloca cada uma das variaveis globais dinamicas
/// \param n, quantidade de itens
///
void desaloca(int n){

    int i;
    if(s == NULL && aux_x == NULL)
        return;

    //para cada item mais 1, desaloca as linhas das matrizes
    for(i = 0; i < n+1; i++){

        if(i < n && aux_x[i] != NULL){

            //free(aux_x[i]);
            aux_x[i] = NULL;
        }

        if(s[i] != NULL){
            free(s[i]);
            s[i] = NULL;
        }
    }

    free(s);
    free(aux_x);

    s = NULL;
    aux_x = NULL;
}

///
/// \brief aloca, função que aloca cada uma das variaveis globais
/// \param n, quantidade de itens
/// \param W, capacidade da mochila
///
void aloca(int n, int W){

	int i, j;

    //aloca as matrizes e vetores pela quantidade de itens
    aux_x = (int**)malloc(sizeof(int*)*n);
    s = (int**)malloc(sizeof(int*)*(n+1));

    //para cada item mais 1, aloca as colunas das matrizes
	for(i = 0; i < n+1; i++){

        if(i < n)
            aux_x[i] = (int*)malloc(sizeof(int)*(W));
        s[i] = (int*)malloc(sizeof(int)*(W+1));

        //coloca tudo em 0 nas matrizes
		for(j = 0; j < W+1; j++){

            if(i < n && j < W)
                aux_x[i][j] = 0;

            s[i][j] = 0;
		}
	}
}

///
/// \brief mochila, função principal do problema da mochila, prepara os dados e chama o metódo selecionado
///
void mochila(){

	system("cls");
	FILE* f; 
    int tentativa = 0, n[3], i, W, *temp;
	Objeto *ob;
	char entrada[100];
    double tempoGasto[3];

    //menu
	printf("1 - Algoritmo com a tecnica de Programacao Dinamica\n");
    printf("2 - Algoritmo com tentativa e erro. (Backtracking)\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
    
    int opcao;
    scanf("%d", &opcao);
    fflush(stdin);

    if(opcao > 0 && opcao < 3){

        //para cada instância
		for(int k = 0; k < 3; k++){
			
			system("cls");
            printf("%s\n",(opcao==1)? "Programacao Dinamica": "Backtracking");
			tentativa = 0;
            //lê os nomes de arquivo até ser escrito um valido
		    do{
				if(tentativa > 0){
					
					printf("Arquivo nao existente, tente novamente\n");			
				}

				printf("Entre com o arquivo: ");
                scanf("%[^\n]", entrada);
				fflush(stdin);
				f = fopen(entrada, "r+");
				tentativa++;

			} while(f == NULL);
			
            //pega a capacidade maxima da mochila e a quantidade de itens
			fscanf(f, "W = %d\n", &W);
            fscanf(f, "n = %d", &n[k]);

            if(opcao == 1)
                aloca(n[k], W);

            valor_final = 0;
            peso_final = 0;

            x = (int*)malloc(sizeof(int)*(n[k]));
            temp = (int*)malloc(sizeof(int)*(unsigned long long)n[k]);
            ob = (Objeto*)malloc(sizeof(Objeto)*n[k]);

            //para cada item dessa instancia
            for(i = 0; i < n[k]; i++)
                fscanf(f, "%d %d", &ob[i].w, &ob[i].c);
		    
		    printf("\n");
            //mostra cada um dos itens
            for(i = 0; i < n[k]; ++i){

		    	printf("Objeto[%d]: ", i);
                printf("\tPeso: %-7d; Valor: %d;\n", ob[i].w, ob[i].c);
		    }
            printf("\n");

            //pega o tempo antes do algoritmo
            clock_t tempo;
            tempo = clock();

            //chama o metodo desejado
			if(opcao == 1){

                valor_final = prog_dinamica(ob, W, n[k]);
	   		}
	    	else if(opcao == 2){

                backtracking(ob, W, 0, n[k], temp);
	    	}

            //pega o tempo depois do algoritmo
            tempo = clock() - tempo;
            tempoGasto[k] = ((double)tempo)/CLOCKS_PER_SEC;

            printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");

            printf("Vetor solucao = x: {");
            //imprime o vetor solução
            for(i = 0; i < n[k]; i++){

				printf(" %d ", x[i]);
			}
            printf("}\n");
            printf("Capacidade da Mochila = %d\n", W);
			printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
            printf("Valor maximo atingido = %d\n", valor_final);
            printf("Peso total atingido = %d\n", peso_final);
			printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n");


            if(opcao == 1){

                printf("Matriz dos valores: \n");
                for(int i = 0; i < n[k]+1; i++){

                    printf("|");

                    for(int j = 0; j < W+1; j++)
                        printf(" %-d ", s[i][j]);

                    printf("|\n");
                }
                printf("\n");
            }

            printf("Tempo de execucao foi de %lf s\n", tempoGasto[k]);
            getchar();
			fclose(f);
            desaloca(n[k]);
            free(temp);
            temp = NULL;
            free(x);
            x = NULL;
            free(ob);
            ob = NULL;
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
