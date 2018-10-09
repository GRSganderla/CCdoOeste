#include<stdio.h>
#include<stdlib.h>

int v[10] = {1,2,3,4,5,6,7,8,9,10};
int n = 10, t = 0;

int main()
{
	asm(".intel_syntax noprefix\n\t"
		"mov eax, 0\n\t"
		"xor ecx, ecx\n\t"
		"L0:\n\t" 
		"cmp ecx, _n\n\t"
		"je L1\n\t"
		"mov ebx, 0\n\t"
		"add ebx, [_v + ecx*4]\n\t"
		"imul ebx, ebx\n\t"
		"add eax, ebx\n\t"
		"inc ecx\n\t"
		"jmp L0\n\t"
		"L1:\n\t"
		"mov _t, eax\n\t"
		".att_syntax prefix\n\t"
		);

	printf("%d\n",t);
	return 0;
}