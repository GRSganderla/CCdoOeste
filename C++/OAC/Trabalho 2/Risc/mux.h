#ifndef MUX_H
#define MUX_H


class MUX
{
private:
    unsigned int in_A;
    unsigned int in_B;
    unsigned int result;
public:
    MUX(unsigned int A,unsigned int B, bool selecao);
    unsigned int get_result();
    ~MUX();
};

#endif // MUX_H
