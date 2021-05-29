/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/faq/how-to-input-a-multiple-digits-number-using-the-keypad
 */

#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte pin_rows[ROW_NUM] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {9, 8, 7}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

String inputString;
long inputInt;

void setup() {
  Serial.begin(9600);
  inputString.reserve(10); // maximum number of digit for a number is 10, change if needed
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    if (key >= '0' && key <= '9') {     // only act on numeric keys
      inputString += key;               // append new character to input string
    } else if (key == '#') {
      if (inputString.length() > 0) {
        inputInt = inputString.toInt(); // YOU GOT AN INTEGER NUMBER
        inputString = "";
        Serial.println(inputInt);// clear input
        // DO YOUR WORK HERE

      }
    } else if (key == '*') {
      inputString = "";                 // clear input
    }
  }
}
