#ifndef FORMATOR_H
#define FORMATOR_H

class FormatoR
{
private:
   unsigned int opcode;
   unsigned int rd;
   unsigned int rs;
   unsigned int rt;
   unsigned int shamt;
   unsigned int funct;
public:
   unsigned int getOpcode();
   void setOpcode(unsigned int);
   void setRd(unsigned int);
   unsigned int getRd();
   void setName(unsigned int);
   unsigned int getRs();
   void setRs(unsigned int);
   unsigned int getRt();
   void setRt(unsigned int);
   unsigned int getShamt();
   void setShamt(unsigned int);
   unsigned int getFunct();
   void setFunct(unsigned int);
   FormatoR(unsigned int op,unsigned int rrd,unsigned int rrs,unsigned int rrt,unsigned int shamtt,unsigned int functt);
   void show_Objeto(void);
   void Update(void);
};

#endif // FORMATOR_H
