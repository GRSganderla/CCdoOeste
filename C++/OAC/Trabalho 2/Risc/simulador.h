#ifndef SIMULADOR_H
#define SIMULADOR_H
#include "memoriainstrucao.h"
#include "registradores.h"
#include "memoriadados.h"
#include <string>
using namespace std;

class Simulador
{
private:
    int clock;
    string inst_feitas[100];
    ofstream arq;
public:
    Simulador();

    void set_outfile();
    unsigned int process(Registradores* regs, MemoriaInstrucao* ins, unsigned int end_pc, MemoriaDados* data);
    void start();
    bool inst_ja_feita(string pc);
    void insereArq(int quant);

    ~Simulador();
};

#endif // SIMULADOR_H
