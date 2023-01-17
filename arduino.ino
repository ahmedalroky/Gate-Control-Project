#include <RCSwitch.h>
#include <EEPROM.h>

RCSwitch mySwitch = RCSwitch();

#define RF_TX_PIN 2
#define GREEN_LED_PIN 3
#define RED_LED_PIN 4
#define BUTTON_PIN 5

#define OPEN_CODE_START 0
#define OPEN_CODE_END 4
#define CLOSE_CODE_START 4
#define CLOSE_CODE_END 8

int openCode = 0;
int closeCode = 0;

bool openCodeReceived = false;
bool closeCodeReceived = false;

bool buttonPressed = false;
bool greenLedOn = false;
bool redLedOn = false;

void setup() {
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  mySwitch.enableReceive(0);
  Serial.begin(9600);
  for (int i = OPEN_CODE_START; i < OPEN_CODE_END; i++) {
    openCode += EEPROM.read(i) << (8 * (i - OPEN_CODE_START));
  }
  for (int i = CLOSE_CODE_START; i < CLOSE_CODE_END; i++) {
    closeCode += EEPROM.read(i) << (8 * (i - CLOSE_CODE_START));
  }
  if (openCode != 0 && closeCode != 0) {
    openCodeReceived = true;
    closeCodeReceived = true;
    greenLedOn = true;
    digitalWrite(GREEN_LED_PIN, HIGH);
    // Listen for serial commands
    while (Serial.available() > 0) {
        char command = Serial.read();
        if (command == '1') {
            // Send the first command
            mySwitch.send(openCode, 24);
        } else if (command == '2') {
            // Send the second command
            mySwitch.send(closeCode, 24);
        }
    }
}
