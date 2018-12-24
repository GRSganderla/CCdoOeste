#include<stdio.h>
#include<stdlib.h>

char s[10] = "foda-se";
int size = 10;

void escreverString(char* s, int size)
{
	asm(".intel_syntax noprefix\n\t"
		"mov eax, 4\n\t"
		"mov ebx, 1\n\t"
		"mov ecx, [ebp + 8]\n\t"
		"mov edx, [ebp + 12]\n\t"
		"int 0x80\n\t"
		".att_syntax prefix\n\t"
		);
}

int main()
{
	asm(".intel_syntax noprefix\n\t"
		"sub esp, 12\n\t"
		"mov eax, _s\n\t"
		"mov [esp], eax\n\t"
		"mov eax, _size\n\t"
		"mov [esp+4], eax\n\t"
		"push ebp\n\t"
		"mov ebp, esp\n\t"
		"call _escreverString\n\t"
		"add esp, 12\n\t"
		".att_syntax prefix\n\t"
		);

	return 0;
}