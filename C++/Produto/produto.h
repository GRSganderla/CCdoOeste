#ifndef PRODUTO_H
#define PRODUTO_H


class Produto
{
private:
    int codigo;
    float preco;
    char nome[50];
    int quantidade;
    float totaliza();
public:
    Produto();
    Produto(int codigo);
    Produto(int codigo, float preco, char nome[], int quantidade);
    void setCodigo(int codigo);
    void setNome(char nome[]);
    void setQuant(int quantidade);
    void setPreco(float preco);
    int getCodigo();
    char* getNome();
    int getQuant();
    float getPreco();
    void upPreco(int porcentagem);
    void tostring(int* codigo, float* preco, char nome[], int* quantidade, float* total);
    void printProd();
    ~Produto();
};

#endif // PRODUTO_H
