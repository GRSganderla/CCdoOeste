#include<stdio.h>
#include<stdlib.h>

void g(int a, int b)
{
	int c = a + b;
}

int main()
{
	int a, b;
	g(a,b);
}