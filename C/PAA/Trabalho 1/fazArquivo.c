#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){

	char entrada[100];
	scanf("%s", entrada);
	FILE* f= fopen(entrada, "w+");

	srand(time(NULL));

	int n, limite;
	scanf("%d", &n);

	scanf("%d", &limite);

	fprintf(f, "n = %d\n", n);
	fprintf(f, "l = %d\n", limite);

	for(int i = 0; i < n; i++){

		for(int j = 0; j < n; j++){

			fprintf(f, "%d ", (rand()*rand())%100);
		}
		fprintf(f, "\n");
	}

	for(int i = 0; i < n; i++){

		for(int j = 0; j < n; j++){

			fprintf(f, "%d ", (rand()*rand())%100);
		}
		fprintf(f, "\n");
	}

	fclose(f);
	return 0;
}