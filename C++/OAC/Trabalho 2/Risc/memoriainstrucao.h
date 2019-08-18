#ifndef MEMORIAINSTRUCAO_H
#define MEMORIAINSTRUCAO_H
#include <iostream>
#include <fstream>
#include <string.h>
#include "registradores.h"
#include "memoriadados.h"

using namespace std;

class MemoriaInstrucao
{
private:
    string instrucao[1000];
    int quant_instr = 0;
    unsigned int input;
    string instrucao_out;
public:
    MemoriaInstrucao();

    void setInput(unsigned int pc);
    unsigned int le_instr(Registradores* regs, unsigned int pc, MemoriaDados* memoData, string* funcao);
    void add_instrucao(string instrucao);
    string faz_instr(unsigned int opcode, unsigned int rs, unsigned int rt, unsigned int rd, unsigned int adress, unsigned int jp);
    int get_quant();
    string get_instrucao();

    ~MemoriaInstrucao();
};

#endif // MEMORIAINSTRUCAO_H
