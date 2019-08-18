#include "simulador.h"
#include <iostream>
#include <fstream>
#include <string.h>

#include "pc.h"
#include "memoriainstrucao.h"
#include "memoriadados.h"
#include "add.h"

using namespace std;

Simulador::Simulador()
{   
    clock = 0;
}

void Simulador::set_outfile(){

    string saida;

    cout << "Entre com o nome do Arquivo de Saida: ";
    cin >> saida;

    this->arq.open(saida);
}

bool Simulador::inst_ja_feita(string pc){

    for(string a: this->inst_feitas){

        if(a.compare(pc) == 0){

            return 1;
        }
    }
    return 0;
}

void Simulador::insereArq(int quant){

    for(int i = 0; i < quant; i++)
        this->arq << i*4 << " " << this->inst_feitas[i] << endl;
}

unsigned int Simulador::process(Registradores* regs, MemoriaInstrucao* ins, unsigned int end_pc, MemoriaDados* data){

    string nova;

    unsigned int pc = ins->le_instr(regs, end_pc + 0b100, data, &nova);
    cout << "\nNo Endereco " << end_pc << " achou a Instrucao: " << nova << endl;

    if(!this->inst_ja_feita(nova)){

        inst_feitas[this->clock++] = nova;
    }

    cout << "Instrucao feita, indo para a instrucao de endereco: " << pc << "\n" << endl;

    return pc;
}

void Simulador::start(){

    unsigned int novo_end, pc;
    PC *counter = new PC();
    MemoriaInstrucao* MI = new MemoriaInstrucao();
    MemoriaDados* data = new MemoriaDados();
    Registradores* regs = new Registradores();
    this->set_outfile();

    while(counter->get_output() <= (MI->get_quant()-1)*4){

        pc = counter->get_output();

        MI->setInput(pc);
        novo_end = this->process(regs, MI, pc, data);

        counter->update(novo_end);
        regs->update();
    }

    insereArq(MI->get_quant());

    cout << "Simulacao Finalizada" << endl;
    cout << "Todas as Instrucoes foram processadas em " << this->clock << " ciclos de clock" << endl;

    cout << "\nRegistradores Usados: " << endl;
    regs->show();

    cout << "\nMemoria Usada: " << endl;
    data->showMemo();

    cout << "\nFinalizando Simulacao" << endl;

    delete counter;
    delete MI;
    delete data;
    delete regs;
}

Simulador::~Simulador(){

}
