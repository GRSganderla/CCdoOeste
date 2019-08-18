#ifndef ALU_H
#define ALU_H
#include <string>

using namespace std;

#define ADD 2
#define SUB 6
#define AND 0
#define OR 1
#define SLT 7

class ALU
{
private:
    unsigned int A;
    unsigned int B;

    bool zero;
    unsigned int ALUres;
    unsigned int funcao;

public:
    ALU(unsigned int A, unsigned int B);

    void set_funcao(unsigned int fun);
    static string get_nome(unsigned int opcode, unsigned int funct);
    bool get_zero();
    void executa();
    unsigned int get_res();

    ~ALU();
};

#endif // ALU_H
