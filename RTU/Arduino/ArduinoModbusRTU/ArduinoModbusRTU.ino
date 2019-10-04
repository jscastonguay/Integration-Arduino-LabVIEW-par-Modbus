#include <SimpleModbusSlave.h>

enum {
  TEMPERATURE,  // Vaut 0
  RELAIS,       // Vaut 1  

  NB_REGISTRES  // Vaut 2, correspond au nombre d'item (temperature et relais)
};

unsigned int holdingRegs[NB_REGISTRES];

void setup() {

  unsigned char ID = 1;
  unsigned char TxEnablePin = 2;

  modbus_configure(&Serial, 9600, SERIAL_8N1, ID, TxEnablePin, NB_REGISTRES, holdingRegs);

  // modbus_update_comms(baud, byteFormat, id) non essentielle: à utiliser pour modifier
  // la configuration de façon dynamique
  //modbus_update_comms(9600, SERIAL_8N2, 1);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  modbus_update();

  holdingRegs[TEMPERATURE] = analogRead(A0);
  if (holdingRegs[RELAIS] == 1) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
