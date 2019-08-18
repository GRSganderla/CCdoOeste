#ifndef REGISTRADORES_H
#define REGISTRADORES_H
#include <string>
#include "control.h"
#include "novapc.h"

using namespace std;

class Registradores
{
    unsigned int Reg[32];

    unsigned int ReadReg1;
    unsigned int ReadReg2;
    unsigned int WriteReg;
    unsigned int WriteData;

    unsigned int ReadData1;
    unsigned int ReadData2;

    bool RegWrite;

public:
    Registradores();

    void show();
    void set_regs(unsigned int r1, unsigned int r2, unsigned int w);
    unsigned int get_Reg(int endereco);
    static string get_nome(unsigned int endereco);
    void set_WriteData(unsigned int data);
    void set_RegWrite(bool reg);
    unsigned int executa_inst(Control *con, string inst, NovaPc* pc);
    void write_Reg();
    void update();
    unsigned int get_ReadData2();

    ~Registradores();
};

#endif // REGISTRADORES_H
