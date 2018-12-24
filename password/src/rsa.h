#ifndef RSA_H
#define RSA_H

#include "infint.h"

class RSA
{
public:
    RSA();
    InfInt power(InfInt a, InfInt b);
    InfInt encrypt(const InfInt& m);
    InfInt decrypt(const InfInt& c);

private:
    InfInt n;
    InfInt p, q;
    InfInt e, d;
};

#endif // RSA_H
