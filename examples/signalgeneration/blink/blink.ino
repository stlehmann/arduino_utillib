#include <utillib.h>

#define LED 13

Blink blink;
String buf;

void print_blinkstate() {
    Serial.print("Blinker ");
    Serial.print(blink.enable ? "enabled" : "disabled");
    Serial.print(" (timelow=");
    Serial.print(blink.timelow);
    Serial.print(", timehigh=");
    Serial.print(blink.timehigh);
    Serial.println(")");
}

void print_help() {
    Serial.println("Command list:");
    Serial.println("----------------------------");
    Serial.println("e - enable blinker");
    Serial.println("d - disable blinker");
    Serial.println("l100 - set timelow to 100ms");
    Serial.println("h100 - set timehigh to 100ms");
    Serial.println("help - call help");
    Serial.println("----------------------------");
}

void setup() {
    Serial.begin(9600);
    blink.timelow = 1000;
    blink.timehigh = 1000;
    pinMode(LED, OUTPUT);
    print_help();
}

void loop() {
    // connect blinker to led
    blink.process();
    digitalWrite(LED, blink.out);

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
        else if (buf[0] == 'e') {
            blink.enable = true;
        }
        else if (buf[0] == 'd') {
            blink.enable = false;
        }
        else if (buf[0] == 'l') {
            String substring = buf.substring(1);
            int i = substring.toInt();
            blink.timelow = i;
        }
        else if (buf[0] == 'h') {
            String substring = buf.substring(1);
            int i = substring.toInt();
            blink.timehigh = i;
        }
        print_blinkstate();
        buf = "";
    }
}
