#include <SPI.h>
#include <RF24.h>

RF24 radio(4, 5); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);

  if (!radio.begin()) {
    Serial.println("NRF24L01 not detected!");
    while (1) {}
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW); // start low to avoid power issues; bump up once confirmed working
  radio.stopListening(); // set as transmitter

  Serial.println("Transmitter ready");
}

void loop() {
  const char text[] = "What is up bro!sss";
  bool success = radio.write(&text, sizeof(text));

  if (success) {
    Serial.println("Sent: Hello");
  } else {
    Serial.println("Send failed");
  }

  delay(1000);
}