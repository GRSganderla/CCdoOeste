#include "memoriainstrucao.h"
#include "control.h"
#include "simulador.h"
#include "registradores.h"
#include "shiftleft.h"
#include "novapc.h"
#include "mux.h"
#include "signextend.h"
#include "alucontrol.h"
#include "formatoi.h"
#include "formatoj.h"
#include "formator.h"
#include "alu.h"
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

unsigned int getInst(string binario, int tam){

    unsigned int res = 0, base = 1u;

    for(int i = tam-1; i >= 0; i--, base <<= 1u){

        res |= (binario.at(i)-'0') ? base : 0;
    }

    return res;
}

ifstream get_arquivo(){

    ifstream arquivo;

    string entrada;
    cout << "Entre com o arquivo de entrada: ";
    cin >> entrada;
    arquivo.open(entrada, ifstream::in);

    while(!arquivo){

        cerr << "Arquivo de entrada nao existente" << endl;
        cout << "Entre com o arquivo de entrada novamente: ";
        cin >> entrada;
        arquivo.open(entrada, ifstream::in);
    }

    return arquivo;
}

int MemoriaInstrucao::get_quant(){

    return this->quant_instr;
}

MemoriaInstrucao::MemoriaInstrucao()
{
    ifstream arq_entrada = get_arquivo();
    string binario;

    while(arq_entrada >> binario){

        this->add_instrucao(binario);
    }
}

int qual_formato(unsigned int opcode){

    if(opcode == 0){

        return 1;
    }
    else {

        switch (opcode) {

            case 2:
                return 2;
            case 4:
            case 5:
                return 3;
            case 15:
                return 4;
            case 35:
            case 43:
                return 5;
        }
    }
}

string MemoriaInstrucao::faz_instr(unsigned int opcode, unsigned int rs, unsigned int rt, unsigned int rd, unsigned int adress, unsigned int jp){

    string fun, espaco = ", ";

    char ins[100];

    switch(qual_formato(opcode)){

        case 1:
            fun.append(Registradores::get_nome(rd));
            fun.append(espaco);
            fun.append(Registradores::get_nome(rs));
            fun.append(espaco);
            fun.append(Registradores::get_nome(rt));
        break;
        case 2:
            fun.append(to_string(jp));
        break;
        case 3:
            fun.append(Registradores::get_nome(rs));
            fun.append(espaco);
            fun.append(Registradores::get_nome(rt));
            fun.append(espaco);
            sprintf(ins, "%d", adress);
            fun.append(ins);
        break;
        case 4:
            fun.append(Registradores::get_nome(rt));
            fun.append(espaco);
            sprintf(ins, "%d", adress);
            fun.append(ins);
        break;
        case 5:
            fun.append(Registradores::get_nome(rt));
            fun.append(espaco);
            sprintf(ins, "%d", adress);
            fun.append(ins);
            fun.append("(");
            fun.append(Registradores::get_nome(rs));
            fun.append(")");
        break;

    }

    return fun;
}

unsigned int MemoriaInstrucao::le_instr(Registradores* regs, unsigned int end_pc, MemoriaDados* memoData, string *funcao){

    NovaPc* pc = new NovaPc();
    pc->set_pc4(end_pc);
    unsigned int quatro_pc = (end_pc & 0b11110000000000000000000000000000);
    Control* con = new Control();

    string instrucao = this->get_instrucao();

    unsigned int opcode = getInst(instrucao.substr(0, 6), 6);
    unsigned int rs = getInst(instrucao.substr(6, 5), 5);
    unsigned int rt = getInst(instrucao.substr(11, 5), 5);
    unsigned int rd = getInst(instrucao.substr(16, 5), 5);
    unsigned int funct = getInst(instrucao.substr(26, 6), 6);
    unsigned int adress = getInst(instrucao.substr(16, 16), 16);
    unsigned int jp = getInst(instrucao.substr(6, 26), 26);

    con->set_control(opcode);
    regs->set_RegWrite(con->get_RegWrite());

    funcao->append(ALU::get_nome(opcode, funct));

    MUX* regDestino = new MUX(rd, rt, con->get_RegDst());
    regs->set_regs(rs, rt, regDestino->get_result());

    SignExtend* SiEx = new SignExtend(adress);
    funcao->append(this->faz_instr(opcode, rs, rt, rd, SiEx->get_output(), jp));

    ShiftLeft* b = new ShiftLeft(SiEx->get_output());
    pc->set_endb(b->get_result());

    ALUcontrol* op = new ALUcontrol(funct, con->get_ALUop0(), con->get_ALUop1());

    ShiftLeft* jmp = new ShiftLeft(jp);
    pc->set_jmp(jmp->get_result() + quatro_pc);

    MUX* read_ou_end = new MUX(SiEx->get_output(), regs->get_Reg(rt),  con->get_AluSrc());

    ALU* ula = new ALU(regs->get_Reg(rs), read_ou_end->get_result());
    ula->set_funcao(op->get_output());
    ula->executa();

    memoData->set_input(ula->get_res(), regs->get_ReadData2());
    memoData->set_mem(con->get_MemWrite(), con->get_MemRead());
    memoData->le();
    memoData->escreve();

    MUX* aluout = new MUX(memoData->get_read(), ula->get_res(), con->get_MemtoReg());

    regs->set_WriteData(aluout->get_result());
    regs->write_Reg();

    pc->set_bools(con->get_Branch0(), con->get_Branch1(), ula->get_zero(), con->get_Jump());
    pc->det_novo_pc();

    return pc->get_novo_pc();
}

void MemoriaInstrucao::setInput(unsigned int pc){

    this->input = pc;
}

void MemoriaInstrucao::add_instrucao(string instrucao){

    this->instrucao[4 * this->quant_instr] = instrucao;
    quant_instr++;
}

string MemoriaInstrucao::get_instrucao(){

    return this->instrucao[this->input];
}

MemoriaInstrucao::~MemoriaInstrucao(){

}
