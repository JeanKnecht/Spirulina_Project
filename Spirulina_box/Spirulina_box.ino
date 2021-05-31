/*
  SpirulinaBox

  By Jean Knecht
  Sint Barbara college Steam project

  code dat gebruikt wordt om de klimaatbox op de juiste temperatuur te houden(warmte element en temperatuursensor),
  om de beluchting te regelen(12v computer ventilator) en om de stroboscopen mee te bedienen aan de hand van een 3x3 numpad.
*/


#include <Keypad.h> //library om numpad mee te kunnen besturen                                      

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'#', '0', '*'},
  {'9', '8', '7'},
  {'6', '5', '4'},
  {'3', '2', '1'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {12,11,10}; 

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);   //functie van de library om keypad te maken

//nu begint het echt werk
//meeste variabelen worden uitgelegd in de code zelf

String inputString;
long inputInt;

int pressState = LOW; 
int temp= A0; //analog pin voor de temperatuursensor
int ledState = LOW; 
int warmte = 6; //pin om mosfet van het warmte element mee te besturen
int readl;  
unsigned long previousMillis = 0; 


const long interval = 100; //interval van het alternerend licht

int timeState_2 = LOW;  
int timeState_3 = LOW;
int timeState_4 = LOW;
int timeState_5 = LOW;

void aan(int trigger){                        //3 functies voor telkens 1 tijdsregime(aan, uit en alternerend)
  digitalWrite(trigger, HIGH);
}

void uit(int trigger){
   digitalWrite(trigger, LOW);
}

void flikker_500(int trigger){
  
}

void changeTimeH(int x){
   switch(x){
     case 2: timeState_2 = HIGH; break;
     case 3: timeState_3 = HIGH; break;
     case 4: timeState_4 = HIGH; break;
     case 5: timeState_5 = HIGH; break;
     default:break;
   }
}

void changeTimeL(int x){
   switch(x){
     case 2: timeState_2 = LOW; break;
     case 3: timeState_3 = LOW; break;
     case 4: timeState_4 = LOW; break;
     case 5: timeState_5 = LOW; break;
     default:break;
   }
}

void setup() {

  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(warmte, OUTPUT);
  pinMode(temp, INPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    if (key >= '0' && key <= '9') {     
      inputString += key;               
    } else if (key == '#') {
      if (inputString.length() > 0) {
        inputInt = inputString.toInt();
        inputString = "";
        readl = inputInt;
        Serial.println(readl);
        pressState = HIGH;
        inputInt;

        
      }
    } else if (key == '*') {
      inputString = "";                 
    }
  }

  if(timeState_2 == HIGH){
      digitalWrite(2, ledState);}
  if(timeState_3 == HIGH){
     digitalWrite(3, ledState);}
  if(timeState_4 == HIGH){
     digitalWrite(4, ledState);}
  if(timeState_5 == HIGH){
     digitalWrite(5, ledState);}

  unsigned long currentMillis = millis();
        
  if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        if (ledState == LOW){
         ledState = HIGH;}
        else{
          ledState = LOW;
          }

      
  }

  if(pressState == HIGH){
      int soort_strobo = readl / 10;
      int soort_tijd = readl % 10;

      if(soort_tijd == 1){
       changeTimeL(soort_strobo);
       uit(soort_strobo);
       pressState = LOW;
        }

      if(soort_tijd == 2){
        changeTimeL(soort_strobo);
        aan(soort_strobo);
        pressState = LOW;
        }

      if(soort_tijd == 3){
        changeTimeH(soort_strobo);
        pressState = LOW;
}
}


  int reading = analogRead(temp);
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.5) * 100 ;

  Serial.println(temperatureC);
  if(temperatureC < 32){
    digitalWrite(warmte, HIGH);
    }
  else{
    digitalWrite(warmte, LOW);
    }
}
