#include<stdio.h>
#include "Arquivos.h"

Cadastro lerArqEntrada()
{
	FILE *texto = fopen("cadastros.txt", "r");

	Cadastro arquivo[100];

	int i, n, temp;

	char s[256];

	fgets(texto, s);

	for(i = 0; !EOF(texto); i++)
	{
		sscanf(s, "%[^:]:%n", &arquivo[i].codigo, &n);
		temp = n;
		sscanf(s+temp, "%[^:]:%n", arquivo[i].nome, &n);
		temp += n;
		sscanf(s+temp, "%[^:]:%n", arquivo[i].sexo, &n);
		temp += n;
		sscanf(s+temp, "%[^:]:%n", arquivo[i].cpf, &n);
		temp += n;
		sscanf(s+temp, "%[^:]:%n", &arquivo[i].crm, &n);
		temp += n;
		sscanf(s+temp, "%[^:]:%n", arquivo[i].especialidade, &n);
		temp += n;
		sscanf(s+temp, "%[^:]:%n", arquivo[i].rg, &n);
		temp += n;
		sscanf(s+temp, "%[^:]:%n", arquivo[i].telefone, &n);
		temp += n;
		sscanf(s+temp, "%[^:]:%n", arquivo[i].celular, &n);
		temp += n;
		sscanf(s+temp, "%[^:]:%n", arquivo[i].email, &n);
		temp += n;
		sscanf(s+temp, "%[^:]:%n", arquivo[i].endereco, &n);
	}
}


NodeArq* criaNohArq(int info)
{
	NodeArq* novo = (NodeArq*)malloc(sizeof(NodeArq));

	novo->numChaves = 0;

	for(int i = 0; i < ORDEM; i++)
		novo->chave[i] = 0;

	for(i = 0; i < ORDEM - 1; i++)
		novo->filho[i] = -1;	

	return novo;
}

NodeArq* leituraDeNoh(FILE* binario, int posicao)
{
    //cria e inicializa uma estrutura de nó
    NodeArq* nois = (NodeArq*)malloc(sizeof(NodeArq));

    //determina o lugat aonde o nó será buscado

    //posiciona na posição do nó
    fseek(binario, sizeof(ArqBinario) + sizeof(NodeArq)*posicao , SEEK_SET);

    //lê o nó
    fread(nois, sizeof(NodeArq), 1, binario);

    //retorna o novo nó lido
    return nois;
}