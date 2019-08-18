#ifndef CONTROL_H
#define CONTROL_H

#define R   0b0
//#define J   0b10
#define BEQ 0b100
#define BNE 0b101
#define LI  0b1111
#define LW  0b100011
#define SW  0b101011

class Control
{
private:
    bool RegDst;
    bool Jump;
    bool Branch0;
    bool Branch1;
    bool MemRead;
    bool MemtoReg;
    bool ALUop0;
    bool ALUop1;
    bool MemWrite;
    bool AluSrc;
    bool RegWrite;
public:
    Control();
    void set_control(unsigned int opcode);
    void reset();
    void show_contr();
    bool get_RegDst();
    bool get_Jump();
    bool get_Branch0();
    bool get_Branch1();
    bool get_MemRead();
    bool get_MemtoReg();
    bool get_ALUop0();
    bool get_ALUop1();
    bool get_MemWrite();
    bool get_AluSrc();
    bool get_RegWrite();
    ~Control();
};

#endif // CONTROL_H
