#include<stdio.h>
#include<stdlib.h>

int main(){

	double x1 = 11.25, x2 = 30.5;
	int m1 = 1, m2 = 1;
	int aa = 0;
	double r1, r2;

	while(!aa){

		r1 = x1 * m1;
		r2 = x2 * m2;

		m1++;

		if(r1 == r2) break;

		m1++;
		if(r1 > r2)
			m2++;
	}

	printf("M1: %d, M2: %d\n", m1, m2);
	return 0;
}