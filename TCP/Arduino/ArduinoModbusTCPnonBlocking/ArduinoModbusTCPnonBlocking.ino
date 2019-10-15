#include <SPI.h>
#include <WiFiNINA.h> // for MKR WiFi 1010
// #include <WiFi101.h> // for MKR1000

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include "arduino_secrets.h"
#include "connection.h"

const int ledPin = LED_BUILTIN;
ModbusTCPServer modbusTCPServer;


void setup() {

  Serial.begin(9600);
  Serial.println("Exemple Arduino Modbus TCP - Non Blocking WiFi");

  Connection_setup();

  if (!modbusTCPServer.begin()) {
    Serial.println("Failed to start Modbus TCP Server!");
    while (1);
  }

  // configure 2 x holding registers at address 0
  if (modbusTCPServer.configureHoldingRegisters(0, 2) == 0) {
    Serial.println("Error no.1");
  }

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}


void loop() {
  
  Connection_loop();
  if (Connection_getState() == NEW_CLIENT_CONNECTED) {
    WiFiClient client = Connection_getWiFiClient();
    modbusTCPServer.accept(client);
  }
  modbusTCPServer.poll();

  int temperature = analogRead(A0);
  if (modbusTCPServer.holdingRegisterWrite(0, temperature) == 0) {
    Serial.println("Error no.2");
  }

  unsigned int etatRelais = modbusTCPServer.holdingRegisterRead(1);
  if (etatRelais) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
