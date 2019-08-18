#ifndef PC_H
#define PC_H


class PC
{
private:
    unsigned int input;
    unsigned int output;
public:
    PC();
    unsigned int get_output();
    void update(unsigned int endereco);
    ~PC();
};

#endif // PC_H
