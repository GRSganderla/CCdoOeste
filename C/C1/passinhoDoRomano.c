#include<stdio.h>
#include<stdlib.h>

void fazOPassinho(int dec)
{
	while(dec > 0)
	{
		if(dec >= 1000)
		{
			printf("M");
			dec -= 1000; 
		}
		else if(dec >= 900)
		{
			printf("CM");
			dec -= 900;
		}
		else if(dec >= 500)
		{
			printf("D");
			dec -= 500;
		}
		else if(dec >= 400)
		{
			printf("CD");
			dec -= 400;
		}
		else if(dec >= 100)
		{
			printf("C");
			dec -= 100;
		}
		else if(dec >= 90)
		{
			printf("XC");
			dec -= 90;
		}
		else if(dec >= 50)
		{
			printf("L");
			dec -= 50;
		}
		else if(dec >= 40)
		{
			printf("XL");
			dec -= 40;
		}
		else if(dec >= 10)
		{
			printf("X");
			dec-=10;
		}
		else if(dec >= 9)
		{
			printf("IX");
			dec-=9;
		}
		else if(dec >= 5)
		{
			printf("V");
			dec-=5;
		}
		else if(dec >= 4)
		{
			printf("IV");
			dec-=4;
		}
		else
		{
			printf("I");
			dec -= 1;
		}
	}
}

int main()
{
	int dec = 1;

	while(dec > 0 && dec < 4000)
	{
		printf("\nEntre com o numero decimal: ");
		scanf("%d%*c", &dec);
		printf("Numero Romano: ");
		fazOPassinho(dec);
		printf("\n");
	}
	
	return 0;
}