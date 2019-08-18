#ifndef FORMATOI_H
#define FORMATOI_H

class FormatoI
  {
  private:
     unsigned int opcode;
     unsigned int rs;
     unsigned int rt;
     unsigned int offset;
  public:
     unsigned int getOpcode();
     void setOpcode(unsigned int);
     unsigned int getRs();
     void setRs(unsigned int);
     unsigned int getRt();
     void setRt(unsigned int);
     unsigned int getOffset();
     void setOffset(unsigned int);
     FormatoI(unsigned int op,unsigned int rrs,unsigned int rrt,unsigned int Offset);
     void show_Objeto(void);
     void Update(void);
  };

#endif // FORMATOI_H
