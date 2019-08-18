#ifndef SIGNEXTEND_H
#define SIGNEXTEND_H


class SignExtend
{
private:
    unsigned int input;
    unsigned int output;
public:
    SignExtend(unsigned int in);
    unsigned int get_output();
    ~SignExtend();
};

#endif // SIGNEXTEND_H
