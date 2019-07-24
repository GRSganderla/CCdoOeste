#ifndef REGISTRADORES_H
#define REGISTRADORES_H


class Registradores
{                              // Endereços
    int zero = 0, at;          // 0, 1
    int v[2], a[4];            // 2, 3, 4, 5, 6, 7
    int t[10];                 // 8, 9, 10, 11, 12, 13, 14, 15, 24, 25
    int s[8];                  // 16, 17, 18, 19, 20, 21, 22, 23
    int k[2], gp, sp, fp, ra;  // 26, 27, 28, 29, 30, 31

public:
    Registradores();
};

#endif // REGISTRADORES_H
