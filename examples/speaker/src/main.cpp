#include <Arduino.h>
#include <SPI.h>

#define AUDIO_EN 3
#define SPEAKER_PIN 9
#define CHANNEL 0          // LEDC channel (0–15)
#define RESOLUTION 8       // Bits of resolution (1–16)
#define DEFAULT_FREQ 1000  // Hz

const int tones[] = { 262, 294, 330, 349, 392, 440, 494, 523 };
const int tones_count = sizeof(tones) / sizeof(tones[0]);
int volume = 10;
int song_index = 0;
int loop_count = 0;

void setVolume(int vol) {
    vol = vol<=100 ? vol : 100;
    digitalWrite(SS, LOW);
    SPI.transfer(0x11);
    SPI.transfer(vol);
    digitalWrite(SS, HIGH);
}

void playTone(int frequency, int duration) {
    ledcWriteTone(CHANNEL, frequency);
    delay(duration);
    ledcWriteTone(CHANNEL, 0);
}

void setup() {
    delay(3000); // Wait for the USB CDC to initialize
    Serial.begin(115200);
    Serial.println("Speaker Example Started!");

    ledcSetup(CHANNEL, DEFAULT_FREQ, RESOLUTION);
    ledcAttachPin(SPEAKER_PIN, CHANNEL);

    pinMode(AUDIO_EN,OUTPUT);
    digitalWrite(AUDIO_EN,1); // Enable PAM8304

    pinMode(SS,OUTPUT);
    SPI.begin();
    setVolume(volume);
}

void loop() {

    playTone(tones[song_index], 200);
    song_index++;

    if (song_index >= tones_count) {
        song_index = 0; // Reset to the beginning of the song
        volume += 10;
        if (volume > 100) {
            volume = 0; // Reset volume after reaching max
        }
        setVolume(volume);
    }

    Serial.printf("Playing tone %d at volume %d\n", tones[song_index], volume);
    loop_count++;
    delay(200);

}