#include <iostream>
#include <fstream>
#include <string.h>

#include "simulador.h"

using namespace std;

/*add, sub, and, or, li,lw, sw, beq, bne, j e jr.*/
/* Opcode = 0; {
 * add: funct 100000(32)
 * sub: funct 100010(34)
 * and: funct 100100(36)
 *  or: funct 100101(37)
 *  jr: funct 001000(8)
 * }
 *  lw: opcode 100011(35)
 *  sw: opcode 101011(43)
 * bne: opcode 000101(5)
 * beq: opcode 000100(4)
 *   j: opcode 000010(2)
 *  li: opcode 001111(15)
*/

int main(){

    cout << "SIMULADOR RISC MONOCICLO" << endl;

    Simulador* risc = new Simulador();

    risc->start();

    return 0;
}
