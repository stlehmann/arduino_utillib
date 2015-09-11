#include <Arduino.h>

#ifndef UTILITIES_H
#define UTILITIES_H

#define dword unsigned long
#define ulong unsigned long


//==============================
// Bit manipulation
//==============================
//------------------------------
//getbit
//------------------------------
//!Return the nth Bit of the variable x
/*!
    \param x value
    \param n bitnumber
*/
boolean getbit(byte x, int n);
boolean getbit(word x, int n);
boolean getbit(dword x, int n);

//------------------------------
//setbit
//------------------------------
//!Set the nth Bit of the variable x to b
/*!
    \param x value
    \param n bitnumber
    \param b bitvalue
*/
byte setbit(byte x, int n, boolean b);
word setbit(word x, int n, boolean b);
dword setbit(dword x, int n, boolean b);


//==============================
// Signalgeneration
//==============================
//------------------------------
// Blink
//------------------------------
//! Generate an alternating digital signal with a specific low and high time.
/*!
    If Blink::enable is set to true Blink::out is set to true for the
    timespan of Blink::timehigh. After this Blink::out is set to false for
    the timespan Blink::timelow.

    If Blink::out is set to false, Blink::out is set to false immediatly.

    The **smallest timespan** for either Blink::timelow or Blink::timehigh is **1ms**.

    A sample implementation can be found in
   ` examples/signalgeneration/blink/blink.ino`.
*/
class Blink {
private:
    ulong t0;
    boolean last_enable;
public:
    //!Input variable
    boolean enable;
    //!Output variable
    boolean out;
    //!low time in ms
    ulong timelow;
    //!high time in ms
    ulong timehigh;

    //!Constructor
    Blink();
    //!Constructor with low and high time
    Blink(long timelow, long timehigh);
    //!Call cyclic for data processing
    boolean process();
    //!Call cyclic for data processing
    /*!
        \param enable value for input variable
    */
    boolean process(boolean enable);
};

//------------------------------
// PWM_DC
//------------------------------
//! Generate an alternating duty cycle signal.
/*!
    The signal frequency is defined in **0.001Hz** by PWM_DC::fq.
    The duty cycle is defined in **0.1%** by PWM_DC::dc.
    For timing the micros() function is used. While this means very exact
    timing at higher frequency it means cycletimes > 70 minutes can not
    be served. The longest cycletime is 1e9µs meaning 16,7 minutes (0,001Hz).

    A sample implementation can be found in
    `examples/signalgeneration/pwm_dc/pwm_dc.ino`.
*/
class PWM_DC {

private:
    ulong t0;
    unsigned int state;
    boolean last_enable;

public:
    //!PWM frequency in 0.001Hz
    ulong fq;
    //!Duty cycle in 0.1%
    ulong dc;
    //!Output variable
    boolean out;

    //!Constructor
    PWM_DC();
    //!Constructor with frequency
    PWM_DC(ulong fq);
    //!Call cyclic for data processing
    boolean process();
    //!Call cyclic for data processing
    /*!
        \param dc duty cycle value in 0.1%
    */
    boolean process(ulong dc);
};

//------------------------------
// Timer_ms
//------------------------------
//! A simple cyclic Timer with 1ms resolution.
/*!
    This is a simple Timer with milliseconds resolution.
    If the Timer is started with Timer_ms::start() the internal counter is
    increased until it reaches the interval time set by
    Timer_ms::setInterval(ulong ms). Then Timer_ms::out is set to true for one
    cycle and the interval begins again.

    The Timer_ms class uses the millis() function so the interval time
    can be set from 1ms to appox. 50 days.
*/

class Timer_ms {
private:
    ulong t0;
    ulong ms;
    ulong delta;
public:
    //!True if the Timer is active.
    boolean active;
    //!Output. True if an interval has passed.
    boolean out;

    Timer_ms(ulong ms=100, boolean start=false);

    boolean process();
    //!Start the timer
    void start();
    //!Stop the timer and reset output and internal counter
    void stop();

    //!Get the timer interval in ms
    ulong getInterval();
    //!Set the timer interval in ms
    void setInterval(ulong ms);

    //!Get the value of the internal millisecond counter
    ulong getms();
};
//------------------------------
// Timer_us
//------------------------------
//! A simple cyclic Timer with 1µs resolution.
/*!
    This is a simple Timer with microseconds resolution.
    If the Timer is started with Timer_us::start() the internal counter will be
    increased until it reaches the interval time set by
    Timer_us::setInterval(long us). Then Timer_us::out is set to true for one
    cycle and the interval begins again.

    The Timer_us class uses the micros() function so the interval time
    can be set from 1µs to appox. 70 minutes.
*/

class Timer_us {
private:
    ulong t0;
    ulong us;
    ulong delta;
public:
    //!True if the Timer is active.
    boolean active;
    //!Output. True if an interval has passed.
    boolean out;

    Timer_us(ulong us=100, boolean start=false);

    boolean process();
    //!Start the timer
    void start();
    //!Stop the timer and reset output and internal counter
    void stop();

    //!Get the timer interval in ms
    ulong getInterval();
    //!Set the timer interval in ms
    void setInterval(ulong us);

    //!Get the value of the internal millisecond counter
    ulong getus();
};
#endif
