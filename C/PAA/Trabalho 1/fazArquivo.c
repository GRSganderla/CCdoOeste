#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){

	char entrada[100];
	scanf("%s", entrada);
	FILE* f= fopen(entrada, "w+");

	srand(time(NULL));

	int n = 34, limite = 1, peso = (rand()*rand())%20000;
	//scanf("%d", &n);

	//scanf("%d", &limite);

	fprintf(f, "W = %d\n", peso);
	fprintf(f, "n = %d\n", n);

	for(int i = 0; i < n; i++){

		for(int j = 0; j < 2; j++){

			fprintf(f, "%d ", (rand()*rand())%peso);
		}
		fprintf(f, "\n");
	}

	/*for(int i = 0; i < n; i++){

		for(int j = 0; j < n; j++){

			fprintf(f, "%d ", (rand()*rand())%100000);
		}
		fprintf(f, "\n");
	}
*/
	fclose(f);
	return 0;
}