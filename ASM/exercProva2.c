#include<stdio.h>
#include<stdlib.h>

int n = 10, x = 4, b = 0;

int main()
{
	asm(".intel_syntax noprefix\n\t"
		"xor ebx, ebx\n\t"
		"mov eax, _x\n\t"
		"mov ecx, 1\n\t"
		"ini:\n\t"
		"cmp eax, 0\n\t"
		"je fim\n\t"
		"shr eax\n\t"	
		"adc ebx,0\n\t"
		"jmp ini\n\t"
		"fim:\n\t"
		"mov _b, ebx\n\t"
		".att_syntax prefix\n\t"
		);

	printf("%d\n", b);

}