#include <utilities.h>

#define LED 13

Timer_us timer;
String buf;

void print_state() {
    Serial.print("Intervaltime=");
    Serial.print(timer.getus());
    Serial.println("us");
}

void print_help() {
    Serial.println("Command list:");
    Serial.println("------------------------------------");
    Serial.println("t1000 - set timer interval to 1000ms");
    Serial.println("help - show this list");
    Serial.println("start - start timer");
    Serial.println("stop - stop timer");
    Serial.println("------------------------------------");
}

void setup() {
    Serial.begin(9600);
    timer.setInterval(1000);
    print_help();
    pinMode(LED, OUTPUT);
}

void loop() {
    // connect pwm to led
    boolean out = timer.process();
    digitalWrite(LED, out);
    if (out) {
        print_state();
    }

    // Wait for Serial data
    char inbyte;
    while (Serial.available()) {
        inbyte = Serial.read();
        buf.concat(inbyte);
    }

    // Wait for newline finishing command
    if (inbyte == '\n')
    {
        if (buf == "help\n") {
            print_help();
        }
        else if (buf[0] == 't') {
            String substring = buf.substring(1);
            timer.setInterval(substring.toInt());
        }
        else if (buf == "start\n") {
            timer.start();
        }
        else if (buf == "stop\n") {
            timer.stop();
        }
        buf = "";
    }
}
