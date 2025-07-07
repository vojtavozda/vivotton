#include <Arduino.h>

int led_pins [] = {7,5,18,16};

void setup() {
    delay(3000); // Wait for the USB CDC to initialize
    Serial.begin(115200);
    Serial.println("Hello, World!");

    for (int i=0; i<4; i++) {
        pinMode(led_pins[i], OUTPUT);
    }
}

int counter = 0;
void loop() {
    Serial.print("Counter: ");
    Serial.println(counter);

    digitalWrite(led_pins[abs((counter - 1) % 4)], LOW);
    digitalWrite(led_pins[counter % 4], HIGH);

    counter++;
    delay(1000);
}
