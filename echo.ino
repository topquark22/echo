#include <SoftwareSerial.h>

// wire to ground for slave mode
const int PIN_SLAVE_ = A1;

int slaveMode;

const int PIN_RESET = 2;
const int PIN_LED = 3;

const int PIN_SW_TX = 5;
const int PIN_SW_RX = 6;

// Multiplexer control
const int PIN_ID2 = A4; // to bin B of CD4052BE
const int PIN_ID1 = A5; // to pin A of CD4052BE

// Which device for master to communicate with (0-3). Hardcoded for now
int deviceId = 0;

const int BAUD_RATE = 9600;

// Lib sets RX pinMode(INPUT_PULLUP), so no need for external resistor.
// https://github.com/PaulStoffregen/SoftwareSerial/blob/master/SoftwareSerial.cpp
SoftwareSerial mySerial(PIN_SW_RX, PIN_SW_TX);

// Wire pin D2 on master to RST on all slaves.
void resetSlaves() {
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

  pinMode(PIN_ID1, OUTPUT);
  pinMode(PIN_ID2, OUTPUT);

  digitalWrite(PIN_ID2, (deviceId > 1) & 0x1);
  digitalWrite(PIN_ID1, deviceId & 0x1);
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
  // visual acknowledgment that data was received
  digitalWrite(PIN_LED, HIGH);
  delay(20);
  digitalWrite(PIN_LED, LOW);
}

void loop_master() {
  mySerial.println("Hello world");
  delay(3000);
}
