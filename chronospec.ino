#include "tom-thumb-tall.h"

char * msg = "  Hello World  ";

const int maxDataPin = 4;
const int maxClockPin = 3;
const int maxLoadPin = 2;

void setMaxRegister(byte regCode, byte value) {
    digitalWrite(maxLoadPin, LOW);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, regCode);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, value);
    digitalWrite(maxLoadPin, HIGH);
}

void showPicture(char pic[8]) {
    for (int i = 0; i < 8; i++) {
        setMaxRegister(i + 1, pic[i]);
    }
}

void setup() {
    pinMode(maxDataPin, OUTPUT);
    pinMode(maxClockPin, OUTPUT);
    pinMode(maxLoadPin, OUTPUT);

    setMaxRegister(0xa, 8); // intensity
    setMaxRegister(0xb, 7); // scan limit
    setMaxRegister(0xf, 0); // display test off
    setMaxRegister(0x9, 0x00); // decode mode off
    setMaxRegister(0xc, 1); // activate display

    setMaxRegister(0x1, 0b01111111);
    setMaxRegister(0x2, 0b00001000);
    setMaxRegister(0x3, 0b01111111);
    setMaxRegister(0x4, 0b00000000);
    setMaxRegister(0x5, 0b01111010);
    setMaxRegister(0x6, 0b00000000);
    setMaxRegister(0x7, 0b01011111);
    setMaxRegister(0x8, 0);
}

void loop() {
    int current_char = 0;
    int current_col = 0;

    while (1) {
        int draw_char = current_char;
        int draw_col = current_col;

        for (int scan_col = 0; scan_col < 8; scan_col++) {
            int char_idx = msg[draw_char] - 32;
            int char_data = tom_thumb_tall[char_idx][draw_col];
            setMaxRegister(scan_col + 1, char_data);
            draw_col++;
            if (draw_col > 3) {
                draw_col = 0;
                draw_char++;
            }
        }
        delay(100);
        current_col++;
        if (current_col > 3) {
            current_col = 0;
            current_char++;
        }
        if (msg[current_char] == '\0') {
            break;
        }
    }
}
