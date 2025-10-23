#include <Arduino.h>

const uint8_t TX_PIN = 4;
const unsigned int PERIOD = 400;
const unsigned int HEADER_LEN = 10;
uint8_t buff[] = { 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
volatile int sent = 0;

void setup() {
  Serial.begin(115200);
  pinMode(TX_PIN, OUTPUT);
  digitalWrite(TX_PIN, LOW);
  Serial.println("Start...");
}

void preamble() {
  for (int i = 0; i < 12; i++) {
    digitalWrite(TX_PIN, HIGH);
    delayMicroseconds(PERIOD);
    digitalWrite(TX_PIN, LOW);
    delayMicroseconds(PERIOD);
  }
}

void header() {
  digitalWrite(TX_PIN, LOW);
  for (int i = 0; i < HEADER_LEN; i++) {
    delayMicroseconds(PERIOD);
  }
}


void sendData(uint8_t* buff, uint8_t len) {
  for (int i = 0; i < len; i++) {
    digitalWrite(TX_PIN, HIGH);
    delayMicroseconds(PERIOD);
    if (buff[i] == 0) {
      digitalWrite(TX_PIN, HIGH);
      delayMicroseconds(PERIOD);
    } else {
      digitalWrite(TX_PIN, LOW);
      delayMicroseconds(PERIOD);
    }
    digitalWrite(TX_PIN, LOW);
    delayMicroseconds(PERIOD);
  }
}



void loop() {
  if (sent == 0) {
    delay(1000);
    preamble();
    header();
    sendData(buff, sizeof(buff));   
    preamble();
    header();
    sendData(buff, sizeof(buff));
    preamble();
    header();
    sendData(buff, sizeof(buff));
    sent = 1;
  }
}
