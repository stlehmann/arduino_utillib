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

        if ((t - t0) <= timehigh) {
            out = true;
        }
        else if ((t - t0) <= (timehigh + timelow)) {
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
//------------------------------
// PWM_DC
//------------------------------
PWM_DC::PWM_DC() {
    t0 = 0;
    out = false;
    fq = 0;
    dc = 0;
    state = 0;
}
PWM_DC::PWM_DC(ulong fq) {
    t0 = 0;
    out = false;
    this->fq = fq;
    dc = 0;
    state = 0;
}
boolean PWM_DC::process() {
    // current time and starttime
    ulong t_cycle = 1E9 / fq;  // cycle time
    ulong t_duty = (dc * t_cycle / 1E3);  // duty time

    ulong t = micros();
    switch (state) {
    case 0:
        t0 = t;
        state = 1;
        break;
    case 1:
        if ((t - t0) > t_duty)
            state = 2;
        break;
    case 2:
        if ((t - t0) > t_cycle)
            state = 0;
        break;
    }
    out = (state == 1);
    return out;
}
boolean PWM_DC::process(ulong dc) {
    this->dc = dc;
    return this->process();
}

//------------------------------
// Timer_ms
//------------------------------
Timer_ms::Timer_ms(ulong ms, boolean start) {
    t0 = 0;
    this->ms = ms;
    delta = 0;
    active = start;
    out = false;
}
boolean Timer_ms::process() {
    long t = millis();
    if (active) {
        if (t0 == 0) t0 = t;
        if ((t - t0) > ms) {
            out = true;
            delta = t - t0;
            t0 = 0;
        }
        else {
            out = false;
        }
    }
    return out;
}
void Timer_ms::start() {
    active = true;
}
void Timer_ms::stop() {
    active = false;
    t0 = 0;
    out = false;
}

ulong Timer_ms::getInterval() {
    return ms;
}
void Timer_ms::setInterval(ulong ms) {
    this->ms = ms;
}

ulong Timer_ms::getms() {
    if (t0 == 0)  return delta;
    else return (millis() - t0);
}

//------------------------------
// Timer_us
//------------------------------
Timer_us::Timer_us(ulong us, boolean start) {
    t0 = 0;
    this->us = us;
    delta = 0;
    active = start;
    out = false;
}
boolean Timer_us::process() {
    long t = micros();
    if (active) {
        if (t0 == 0) t0 = t;
        if ((t - t0) > us) {
            out = true;
            delta = t - t0;
            t0 = 0;
        }
        else {
            out = false;
        }
    }
    return out;
}
void Timer_us::start() {
    active = true;
}
void Timer_us::stop() {
    active = false;
    t0 = 0;
    out = false;
}

ulong Timer_us::getInterval() {
    return us;
}
void Timer_us::setInterval(ulong us) {
    this->us = us;
}

ulong Timer_us::getus() {
    if (t0 == 0)  return delta;
    else return (micros() - t0);
}