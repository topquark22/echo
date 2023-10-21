#include <SoftwareSerial.h>

// wire to ground for slave mode
const int PIN_SLAVE_ = A1;

int slaveMode;

const int PIN_RESET = 2;
const int PIN_LED = 3;

const int PIN_SW_TX = 10;
const int PIN_SW_RX = 11;

const int BAUD_RATE = 9600;

SoftwareSerial mySerial(PIN_SW_RX, PIN_SW_TX);

void resetSlave() {
  digitalWrite(PIN_RESET, LOW);
  delay(10);
  digitalWrite(PIN_RESET, HIGH);
}

void setup() {
  Serial.begin(BAUD_RATE);
  mySerial.begin(BAUD_RATE);

  pinMode(PIN_LED, OUTPUT);
  
  pinMode(PIN_SLAVE_, INPUT_PULLUP);
  slaveMode = !digitalRead(PIN_SLAVE_);
  
  pinMode(PIN_RESET, OUTPUT);
  digitalWrite(PIN_RESET, HIGH);
}

void loop() {
  if (slaveMode) {
    loop_slave();
  } else {
    loop_master();
  }
}

void loop_slave() {
  while (!mySerial.available()) {
  }
  while (mySerial.available()) {
    char c = mySerial.read();
    Serial.print(c);
  }
  digitalWrite(PIN_LED, HIGH);
  delay(200);
  digitalWrite(PIN_LED, LOW);
}

void loop_master() {
  mySerial.println("Hello world");
  delay(3000);
}
