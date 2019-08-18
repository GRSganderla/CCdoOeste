#ifndef FORMATOJ_H
#define FORMATOJ_H

class FormatoJ
  {
  private:
     unsigned int opcode;
     unsigned int endereco;
  public:
     unsigned int getOpcode();
     void setOpcode(unsigned int);
     unsigned int getEndereco();
     void setEndereco(unsigned int);

     FormatoJ(unsigned int op,unsigned int end);
     void show_Objeto();
     void Update();
  };

#endif // FORMATOJ_H
