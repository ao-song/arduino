#include <SoftwareSerial.h>

#define RELAY 2
#define POWER 13

#define SW_RX 7
#define SW_TX 8

SoftwareSerial espSerial(SW_RX, SW_TX);

void setup() {
  // put your setup code here, to run once:
  espSerial.begin(115200);
  espSerial.flush();

  pinMode(POWER, OUTPUT);
  pinMode(RELAY, OUTPUT);

  digitalWrite(POWER, HIGH);
  digitalWrite(RELAY, HIGH); // low level trigger
}

void loop() {
  // put your main code here, to run repeatedly:    
  if (espSerial.available()) {
    espSerial.println("receive data");
    String str = espSerial.readString();
    str.trim();
    if (str == "on") {
      digitalWrite(RELAY, LOW);
    } else if (str == "off") {
      digitalWrite(RELAY, HIGH);
    }
  }
}
