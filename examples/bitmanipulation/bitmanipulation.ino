#include <utilities.h>

byte val = 0;
int direction = 1;
int i = 0;

void print_bits(byte val) {
    for (int i=0; i<8; i++) {
        boolean b = getbit(val, i);
        Serial.print(b);
        Serial.print(" ");
    }
}

void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.print(val);
    Serial.print(": ");
    print_bits(val);
    Serial.print("\n");

    val = setbit(val, i, true);
    if (i>7) direction = -1;
    if (i<0) direction = 1;
    i += direction;
    delay(1000);
}
