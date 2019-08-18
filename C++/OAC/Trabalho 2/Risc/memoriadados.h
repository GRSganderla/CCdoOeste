#ifndef MEMORIADADOS_H
#define MEMORIADADOS_H


class MemoriaDados
{
private:
    unsigned int memoria[1000];
    unsigned int Address;
    unsigned int WriteData;
    unsigned int ReadData;

    bool MemWrite;
    bool MemRead;
public:
    MemoriaDados();

    void set_input(unsigned int ender, unsigned int dados);
    void set_mem(bool write, bool read);
    unsigned int get_read();
    void escreve();
    void le();
    void showMemo();

    ~MemoriaDados();
};

#endif // MEMORIADADOS_H
