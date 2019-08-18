#ifndef NOVAPC_H
#define NOVAPC_H
#include "add.h"
#include "mux.h"

class NovaPc
{
private:
    unsigned int pc_4;
    unsigned int end_b;
    unsigned int jmp;
    bool Branch0;
    bool Branch1;
    bool Zero;
    bool Jump;

    unsigned int novo_pc;
public:
    NovaPc();
    void set_pc4(unsigned int pc);
    void set_endb(unsigned int end);
    void set_jmp(unsigned int jmp);
    void set_bools(bool B0, bool B1, bool Z, bool J);
    void det_novo_pc();
    unsigned int get_novo_pc();
    ~NovaPc();
};

#endif // NOVAPC_H
