#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

/*add, sub, and, or, li,lw, sw, beq, bne, jejr.*/

int bin_to_num(char *str, int fim){

    int base = 1, num = 0;

    while(fim-1 >= 0){
        num += (str[fim-1]-'0') * base;
        base *= 2;
        fim--;
    }
    cout << num << endl;
    return num;
}

int main()
{
    int opcao = 1;

    while(opcao != 0)
    {
        cout << "1 - Entrar com um arquivo;" << endl << "0 - Sair" << endl;
        cin >> opcao;

        if(opcao == 1)
        {
            system("cls");
            char entrada[100];
            cout << "Entre com o arquivo de entrada: ";
            cin >> entrada;

            ifstream arq_entrada;
            arq_entrada.open(entrada, ifstream::in);

            if(!arq_entrada){
                cerr << "Arquivo de entrada nao existente" << endl;
                continue;
            }

            char binario[100], opcode_bin[7];

            while(arq_entrada >> binario){

                cout << binario << endl;
                strncpy(opcode_bin, binario, 6);
                opcode_bin[6] = '\0';
                cout << opcode_bin << endl;
                bin_to_num(opcode_bin, 6);
            }
        }
    }

    return 0;
}
