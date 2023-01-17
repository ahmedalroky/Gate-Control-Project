#include <RCSwitch.h>
#include <EEPROM.h>


RCSwitch mySwitch = RCSwitch();
int greenLed = 13;
int redLed = 12;
int transmitPin = 10; // Specify the pin for transmitting
int receivePin = 0; // Specify the pin for receiving
bool codesStored = false;
unsigned long receivedCode1, receivedCode2;
int eepromAddress1 = 0, eepromAddress2 = 4;


void writeLongToEEPROM(int address, unsigned long value) {
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);


  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}


unsigned long readLongFromEEPROM(int address) {
  unsigned long four = EEPROM.read(address);
  unsigned long three = EEPROM.read(address + 1);
  unsigned long two = EEPROM.read(address + 2);
  unsigned long one = EEPROM.read(address + 3);


  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}



void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  mySwitch.enableTransmit(transmitPin);
  mySwitch.enableReceive(receivePin);
  Serial.begin(9600);
  mySwitch.enableTransmit(10);



  // Check if codes are already stored in EEPROM
  if (EEPROM.read(eepromAddress1) != 0xFF && EEPROM.read(eepromAddress2) != 0xFF) {
    codesStored = true;
    digitalWrite(greenLed, HIGH);
    receivedCode1 = readLongFromEEPROM(eepromAddress1);
    receivedCode2 = readLongFromEEPROM(eepromAddress2);
  }
}


void loop() {

  if (codesStored) {
if (Serial.available()) {
      int command = Serial.read();
      if (command == '1') {
        mySwitch.send(receivedCode1, 24); // Send "on" command
      } else if (command == '2') {
        mySwitch.send(receivedCode2, 24); // Send "off" command
      } else if (command == '3') {
        EEPROM.write(eepromAddress1,0xFF);
        EEPROM.write(eepromAddress2,0xFF);
      }
    }
  } else {
    digitalWrite(redLed, HIGH);
    if (mySwitch.available()) {
      unsigned long value = mySwitch.getReceivedValue();
      if (value != 0) {
        Serial.print("Received RF code (On): ");
        Serial.println(value);
        receivedCode1 = value;
        writeLongToEEPROM(eepromAddress1, receivedCode1);
        digitalWrite(redLed, HIGH);
        delay(100);
        digitalWrite(redLed, LOW);
        delay(100);
        digitalWrite(greenLed, HIGH);
        delay(100);
        digitalWrite(greenLed, LOW);
        digitalWrite(redLed, HIGH);
        delay(100);
        digitalWrite(redLed, LOW);
        delay(100);
        digitalWrite(greenLed, HIGH);
        delay(100);
        digitalWrite(greenLed, LOW);
        delay(10000);
        if (mySwitch.available()) {
          unsigned long value2 = mySwitch.getReceivedValue();
          if (value2 != 0) {
            Serial.print("Received RF code (Off): ");
            Serial.println(value2);
            receivedCode2 = value2;
            writeLongToEEPROM(eepromAddress2, receivedCode2);
            digitalWrite(redLed, LOW);
            codesStored = true;
            digitalWrite(greenLed, HIGH);
        }
      }
    }
    }}  }

