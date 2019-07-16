#include<stdio.h>

int maior(int *A, int n){

	int maior = A[0];

	for(int i = 1; i < n; i++)
		if(A[i] > maior) maior = A[i];

	return maior;
}

void counting_sort(int *A, int *B, int n, int k){

	int C[k], i;

	for(i = 0; i < k+1; i++) C[i] = 0;

	for(i = 0; i < n; i++)
		C[A[i]] = C[A[i]]+1;

	for(i = 1; i < k+1; i++) C[i] += C[i-1];

	for(i = n-1; i >= 0; i++){

		B[C[A[i]]] = A[i];
		C[A[i]] = C[A[i]]-1;
	}
}

int main(){

	int A[] = {10,9,2,3,51,2,4,2,4,2,1,5,3,53,2,3};
	int k = 0, n = 0;

	n = sizeof(A)/sizeof(int);

	k = maior(A, n);

	printf("Desordenado\n");
	for(int i = 0; i < n; i++) printf("[%d] = %d\n",i, A[i]);

	int B[n];

	counting_sort(A, B, n, k);

	printf("Ordenado\n");
	for(int i = 0; i < n; i++) printf("[%d] = %d\n",i, B[i]);	
}