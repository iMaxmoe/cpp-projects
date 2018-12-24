#include "rsa.h"

RSA::RSA()
{
    p = "263986629565113564591367147857897817709";
    q = "289623896914026186660567345097696183669";
    n = "76456836387847668610175938462440441250789793744156026408265977716132744794321";
    e = "65537";
    d = "55363163215003722501251344060203756350934713379893408810218020892001386514945";
}

InfInt RSA::power(InfInt a, InfInt b){
    InfInt c = 1;
    while(b > 0){
        if(b % 2 == 1) c = (c * a) % n;
        a = (a * a) % n;
        b = b / 2;
    }
    return c;
}

InfInt RSA::encrypt(const InfInt &m){
    return power(m, e);
}

InfInt RSA::decrypt(const InfInt &c){
    return power(c, d);
}
