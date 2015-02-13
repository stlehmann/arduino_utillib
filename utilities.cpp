#include "utilities.h"

//------------------------------
//getbit
//------------------------------
boolean getbit(byte x, int n) {
    return (x >> n) & 1;
}
boolean getbit(word x, int n) {
    return (x >> n) & 1;
}
boolean getbit(dword x, int n) {
    return (x >> n) & 1;
}

//------------------------------
//setbit
//------------------------------
byte setbit(byte x, int n, boolean b) {
    return x ^ (-b ^ n) & (1 << n);
}
word setbit(word x, int n, boolean b) {
    return x ^ (-b ^ n) & (1 << n);
}
dword setbit(dword x, int n, boolean b) {
    return x ^ (-b ^ n) & (1 << n);
}
