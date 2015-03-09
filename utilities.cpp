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

//==============================
// Signalgeneration
//==============================
//------------------------------
// Blink
//------------------------------
Blink::Blink() {
    t0 = 0;
    enable = false;
    last_enable = false;
    out = false;
    timelow = 0;
    timehigh = 0;
}
Blink::Blink(long timelow, long timehigh) {
    t0 = 0;
    enable = false;
    last_enable = false;
    out = false;
    this->timelow = timelow;
    this->timehigh = timehigh;
}
boolean Blink::process() {
    if (enable) {
        //current time and starttime
        ulong t = millis();
        if (enable &! last_enable) t0 = t;

        if (t <= (t0 + timehigh)) {
            out = true;
        }
        else if (t <= (t0 + timehigh + timelow)) {
            out = false;
        }
        else
            t0 = t;

        //if timehigh or timelow == 0 set out to false or true
        if (timehigh == 0)
            out = false;
        else if (timelow == 0)
            out = true;
    }
    else
        out = false;

    last_enable = enable;
    return out;
}
boolean Blink::process(boolean enable) {
    this->enable = enable;
    return this->process();
}
