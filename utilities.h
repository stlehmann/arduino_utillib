#include <Arduino.h>

#ifndef UTILITIES_H
#define UTILITIES_H

#define dword unsigned long

//!Return the nth Bit of the variable x
/*!
    \param x value
    \param n bitnumber
*/
boolean getbit(byte x, int n);
boolean getbit(word x, int n);
boolean getbit(dword x, int n);

//!Set the nth Bit of the variable x to b
/*!
    \param x value
    \param n bitnumber
    \param b bitvalue
*/
byte setbit(byte x, int n, boolean b);
word setbit(word x, int n, boolean b);
dword setbit(dword x, int n, boolean b);

#endif
