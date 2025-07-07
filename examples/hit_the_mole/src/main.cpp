#include <Arduino.h>

const int led_pins[] = {7, 5, 18, 16};
const int btn_pins[] = {6, 4, 17, 15};

// Index of a button where the mole is currently located
int mole = random(0, 4);

void setup() {
    delay(3000); // Wait for the USB to initialize
    Serial.begin(115200);
    Serial.println("Hit the Mole Game Started!");

    for (int i = 0; i < 4; i++) {
        pinMode(led_pins[i], OUTPUT);
        pinMode(btn_pins[i], INPUT_PULLUP);
    }
    digitalWrite(led_pins[mole], HIGH);
}

int loop_count = 0;
int score = 0;

void loop() {
    
    for (int i=0; i<4; i++) {
        if (digitalRead(btn_pins[i]) == LOW) {
            if (i == mole) {
                score++;
                float speed = 10.0 * score / (loop_count + 1);
                Serial.printf("Hit mole no. %d! Score: %d Speed: %.2f moles/s\n", mole, score,speed);
                digitalWrite(led_pins[mole], LOW);
                mole = random(0, 4);
                digitalWrite(led_pins[mole], HIGH);
            } else {
                Serial.println("Missed!");
            }
        }
    }
    loop_count++;
    delay(100);
}