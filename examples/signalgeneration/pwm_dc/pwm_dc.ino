#include <utilities.h>

#define LED 13

PWM_DC pwm;
String buf;

void print_pwmstate() {
    Serial.print("PWM ");
    Serial.print(" (frequency=");
    Serial.print(pwm.fq);
    Serial.print(", dutycycle=");
    Serial.print(pwm.dc);
    Serial.println(")");
}

void print_help() {
    Serial.println("Command list:");
    Serial.println("----------------------------");
    Serial.println("f1000 - set frequency to 1Hz");
    Serial.println("d500 - set dutycycle to 50%");
    Serial.println("help - call help");
    Serial.println("----------------------------");
}

void setup() {
    Serial.begin(9600);
    pwm.fq = 1000;
    pwm.dc = 500;
    pinMode(LED, OUTPUT);
    print_help();
    print_pwmstate();
}

void loop() {
    // connect pwm to led
    pwm.process();
    digitalWrite(LED, pwm.out);

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
        else if (buf[0] == 'f') {
            String substring = buf.substring(1);
            ulong fq = substring.toInt();
            pwm.fq = fq;
        }
        else if (buf[0] == 'd') {
            String substring = buf.substring(1);
            ulong dc = substring.toInt();
            pwm.dc = dc;
        }
        print_pwmstate();
        buf = "";
    }
}
