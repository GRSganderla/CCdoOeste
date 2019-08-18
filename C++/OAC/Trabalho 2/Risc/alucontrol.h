#ifndef ALUCONTROL_H
#define ALUCONTROL_H

class ALUcontrol
{
private:
    unsigned int input;
    unsigned int output;
public:
    ALUcontrol(unsigned int input, bool ALUop0, bool ALUop1);
    unsigned int get_output();
    void update();
    ~ALUcontrol();
};

#endif // ALUCONTROL_H
