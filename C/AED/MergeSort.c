#include<stdlib.h>
#include<stdio.h>

int main(){

	int vet[12] = {7, 2, 9, 15, 8, 6, 3, 4, 10, 12, 5, 3};
	int aux[12];
	int res[12];
	int e1 = 1, d1 = 3, e2 = 6, d2 = 12;
	int temp;
	int a = 0;

	int j = e1, m = e2;

	while(j < d1 && m < d2){

		if(vet[j] <= vet[m]) aux[a++] = vet[j++];
		else aux[a++] = vet[m++];
	}

	for(int i = 0 ; i < 12; i++)
		printf("[%d] ", aux[i]);

	while(j < d1) aux[a++] = vet[j++];
	while(m < d2) aux[a++] = vet[m++];

	for(int i = e1; i < d2; i++) vet[i] = aux[i-e1];

	printf("\n");

	for(int j = 0; j < 12; j++)
		printf("[%d] ", vet[j]);

	return 0;
}