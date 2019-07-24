#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

/*add, sub, and, or, li,lw, sw, beq, bne, j e jr.*/
/* Opcode = 0; {
 * add: funct 100000(32)
 * sub: funct 100010(34)
 * and: funct 100100(36)
 *  or: funct 100101(37)
 *  jr: funct 001000(8)
 * }
 *  lw: opcode 100011(35)
 *  sw: opcode 101011(43)
 * bne: opcode 000101(5)
 * beq: opcode 000100(4)
 *   j: opcode 000010(2)
 *  li: opcode 001111(15)
*/

int bin_to_num(string binario, int n){

    int res = 0, base = 1;
    n -= 1;

    while(n >= 0){

        res += (binario.at(static_cast<unsigned>(n))-'0') * base;
        base *= 2;
        n--;
    }

    return res;
}

char* add_bin(char* a, char* b){

    int n = static_cast<int>(strlen(a)) -1;
    char* c = new char[n];
    char carry = '0';

    while(n >= 0){

        if((a[n] == '1') && (b[n] == '1')){

            if(carry == '1'){
                c[n] = '1';
            }
            else
                c[n] = '0';

            carry = '1';
        }
        else{

            if(a[n] == '1' || b[n] == '1'){

                c[n] = '1';

                if(carry  == '1'){
                    c[n] = '0';
                    carry = '1';
                }
                else
                    carry = '0';
            }
            else{

                if(carry == '1'){
                    c[n] = '1';

                }
                carry = '0';
            }

        }
        cout << "c = " << c[n] << endl;
        cout << "carry = " << carry << endl;
        cout << "n = " << n << endl;
        n--;
    }

    return c;
}

char* or_bin(char* a, char* b){

    int n = static_cast<int>(strlen(a)) -1;
    char* c = new char[n];

    while(n >= 0){

        if((a[n] == '1') || (b[n] == '1'))
            c[n] = '1';
        else
            c[n] = '0';
        n--;
    }

    return c;
}

char* and_bin(char* a, char* b){

    int n = static_cast<int>(strlen(a)) -1;
    char* c = new char[n];

    while(n >= 0){

        if((a[n] == '1') && (b[n] == '1'))
            c[n] = '1';
        else
            c[n] = '0';
        n--;
    }

    return c;
}

void Rformat(string bin){

    int rs, rt, rd, shamt, funct;
    string bin_rs (bin, 6, 5);
    string bin_rt (bin, 12, 5);
    string bin_rd (bin, 17, 5);
    string bin_shamt (bin, 22, 5);
    string bin_funct (bin, 27, 5);

    rs = bin_to_num(bin_rs, 5);
    rt = bin_to_num(bin_rt, 5);
    rd = bin_to_num(bin_rd, 5);
    shamt = bin_to_num(bin_shamt, 5);
    funct = bin_to_num(bin_funct, 5);

    cout << "R: " << endl << "| " << bin_to_num(bin.substr(0, 6), 6) << " | " << rs << " | " << rt << " | " << rd << " | " << shamt << " | " << funct << " |" << endl;
}

void Iformat(string bin){

    int rs, rt, end_cons;
    string bin_rs, bin_rt, bin_end_cons;

    bin_rs = bin.substr(6, 5);
    rs = bin_to_num(bin_rs, 5);
    bin_rt = bin.substr(11, 5);
    rt = bin_to_num(bin_rt, 5);
    bin_end_cons = bin.substr(16, 16);
    end_cons = bin_to_num(bin_end_cons, 16);

    cout << "I: " << endl << "| " << bin_to_num(bin.substr(0, 6), 6) << " | " << rs << " | " << rt << " | " << end_cons << " |" << endl;
}

/*void Jformat(string bin){

}*/

int main()
{
    /*char* a = new char[100], *b = new char[100];

    cout << "teste do and" << endl;
    cin >> a >> b;
    char* c = and_bin(a, b);
    char* d = or_bin(a, b);
    char* e = add_bin(a, b);

    cout << "and bin = " << c << endl;
    cout << "or bin = " << d << endl;
    cout << "add bin = " << e << endl;*/
    int opcao = 1, opcode;

    while(opcao != 0)
    {
        cout << "1 - Entrar com um arquivo;" << endl << "0 - Sair" << endl;
        cin >> opcao;

        if(opcao == 1)
        {
            system("cls");
            string entrada;
            cout << "Entre com o arquivo de entrada: ";
            cin >> entrada;

            ifstream arq_entrada;
            arq_entrada.open(entrada, ifstream::in);

            if(!arq_entrada){
                cerr << "Arquivo de entrada nao existente" << endl;
                continue;
            }

            string binario;

            while(arq_entrada >> binario){

                int i = static_cast<int>(arq_entrada.tellg());
                cout << "linha: "<< i << endl;
                cout << binario << endl;

                string opcode_bin (binario, 0, 6);
                cout << "Opcode: " << opcode_bin << endl;
                opcode = bin_to_num(opcode_bin, 6);
                cout << "Opcode: " << endl;
                cout << opcode << endl;
                GotoLine(arq_entrada, 0);

                switch(opcode){

                    case 0:
                        cout << "entrou R format" << endl;
                        Rformat(binario);
                    break;
                    case 2:
                        cout << "entrou J format" << endl;
                        //Jformat(binario);
                    break;
                    case 4:
                    case 5:
                    case 15:
                    case 35:
                    case 43:
                        cout << "entrou I format" << endl;
                        Iformat(binario);
                    break;

                }
            }
        }
    }

    return 0;
}
