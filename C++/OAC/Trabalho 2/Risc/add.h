#ifndef ADD_H
#define ADD_H


class ADD
{
private:

    unsigned int A;
    unsigned int B;
    unsigned int result;

public:
    ADD(unsigned int a, unsigned int b);
    unsigned int get_result();
    ~ADD();
};

#endif // ADD_H
