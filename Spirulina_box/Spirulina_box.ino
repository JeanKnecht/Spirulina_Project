/*
  SpirulinaBox

  By Jean Knecht
  Sint Barbara college Steam project

  code dat gebruikt wordt om de klimaatbox op de juiste temperatuur te houden(warmte element en temperatuursensor),
  om de beluchting te regelen(12v computer ventilator) en om de stroboscopen mee te bedienen aan de hand van een 4x3 numpad.
*/


#include <Keypad.h> //library om numpad mee te kunnen besturen                                      

const byte ROWS = 4;                    // hier volgen enkele settings die noodzakelijk zijn voor de library van de numpad
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

//nu begint het echte werk
//meeste variabelen worden uitgelegd in de code zelf

String inputString;
long inputInt;

int heatState = LOW;
int heat = LOW;
int pressState = LOW; 
int temp= A0; //analog pin voor de temperatuursensor
int ledState = LOW; 
int warmte = 13; //pin om mosfet van het warmte element mee te besturen
int readl;  
unsigned long previousMillis = 0; 
unsigned long previousMillis2 = 0; 

long interval = 500;          //interval van het alternerend licht
const long heatInterval = 200;
int timeState_2 = LOW;  
int timeState_3 = LOW;
int timeState_4 = LOW;
int timeState_5 = LOW;

int regulateFan = A5;

void aan(int trigger){                        //3 functies voor telkens 1 tijdsregime(aan, uit en alternerend)
  digitalWrite(trigger, HIGH);
}

void uit(int trigger){
   digitalWrite(trigger, LOW);
}

void flikker_500(int trigger){
  
}

void changeTimeH(int x){                    //functies om makkelijk bepaalde statements te veranderen, deze worden verder uitgelegd
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
  pinMode(2, OUTPUT);            //aan de digital pins van de stroboscopen worden geen variabel toegekend omdat het dan makkelijker is om deze pins te besturen
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);

  pinMode(warmte, OUTPUT);      
  pinMode(temp, INPUT);

  pinMode(regulateFan, OUTPUT);
  analogWrite(regulateFan,0);
}

void loop() {
  char key = keypad.getKey(); //kijkt wanneer er op de numpad is geduwd en zet de verkregen waarde in een variabel

  if (key) {                  //wanneer er op een knop is geduwd is de if-statement True
    Serial.println(key);

    if (key >= '0' && key <= '9') {     //is de key een numeriek getal tussen 0 en 9 dan wordt die toegevoegd aan een string 
      inputString += key;               
    } else if (key == '#') {            //wanneer de key gelijk is aan de hashtag zal het de string(dat bestaat uit getallen) omzetten naar een integer
      if (inputString.length() > 0 and inputString.length() < 3) {   //er moet zeker meer dan 1 keer gedrukt zijn anders is er geen input
        inputInt = inputString.toInt();
        inputString = "";               //de inputString wordt weer leeggehaald, nu kan die weer nieuwe informatie opslaan
        readl = inputInt;               //het bekomen integer wordt opgeslaan in een variabel dat later gebruikt wordt om de de mosfets te reguleren
        Serial.println(readl);
        pressState = HIGH;              //wanneer er gedrukt is en er een getal is opgeslagen in een variabel wordt deze statement True, dit manipuleert de code die verder wordt beschreven
        inputInt;

        
      }
     else{
        inputString = "";
      }
    }
    if (key == '*') {  //wanneer er op het * wordt, wordt het interval van het alternerend licht aangepast met het gegeven nummer
         if (inputString.length() > 0) {
            inputInt = inputString.toInt();
            inputString = "";
            interval = inputInt;
            inputInt;
         }
    }
  }

  if(timeState_2 == HIGH){                      //de timestate verwijst naar of de input al dan wel of niet alternerend licht vraagt
      digitalWrite(2, ledState);}               //wanneer de timestate hoog is zal de fucntie telkens opnieuw in de loop gaan en het licht laten flikkeren op het bepaalde interval
  if(timeState_3 == HIGH){                      //wanneer het licht aan of uit gaat hangt af van de ledState, deze wordt bepaald in de volgend blok
     digitalWrite(3, ledState);}
  if(timeState_4 == HIGH){
     digitalWrite(4, ledState);}
  if(timeState_5 == HIGH){
     digitalWrite(5, ledState);}

  if(heatState == HIGH){
     //Serial.println("heat aan/uit");
     digitalWrite(warmte, heat);}
     
  unsigned long currentMillis = millis();
  unsigned long currentMillis2 = millis(); //dit wordt uitgelegd op de Github pagina
        
  if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        if (ledState == LOW){
         ledState = HIGH;}
        else{
          ledState = LOW;
          }

      
  }

  if (currentMillis2 - previousMillis2 >= heatInterval) {
        previousMillis2 = currentMillis2;

        if (heat == LOW){
         heat = HIGH;}
        else{
          heat = LOW;
          }

      
  }

  if(pressState == HIGH){                         //er is gedrukt geweest op de numpad en er moet dus een actie worden ondergaan
      int soort_strobo = readl / 10;              //het verkregen variabel dat bestaat uit 2 cijfers wordt opgeslits in 2 cijfers
      int soort_tijd = readl % 10;                //het eerste cijfer stelt de digital pin voor en het tweede cijfer het tijdsregime                 

      if(soort_tijd == 1){                        //er wordt gekeken welk tijdsregime er gevraagd wordt
       changeTimeL(soort_strobo);                 
       uit(soort_strobo);                         //verwezen naar een functie die de led zal uitzetten, de functie vraagt naar welke digitale pin verwezen moet worden(omdat er geen variabel is toegekend kan "soort_strobo" direct verwijzen naar een digital pin. 
       pressState = LOW;                          //de actie is ondergaan en de pressState mag weer op low gezet worden totdat er een nieuwe variabel op de numpad wordt ingetoetst
        }

      if(soort_tijd == 2){
        changeTimeL(soort_strobo);
        aan(soort_strobo);
        pressState = LOW;
        }

      if(soort_tijd == 3){
        changeTimeH(soort_strobo);                //wanneer er alternerend licht wordt gevraagd zal eerst de timestate op True gezet worden, hierdoor wordt tijdens het lopen de dgitale pin constant verwisseld van HIGH naar LOW volgens een bepaald interval
        pressState = LOW;
}
}


  int reading = analogRead(temp);                    //input van temperatuursensor wordt gelezen en opgeslagen in een variabel
  float voltage = reading * 5.0;                     //omdat de input nog niet direct gelijk is aan de temperatuur in graden celsius moeten er enkele omvormingen gebeuren
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.5) * 100 ;

  Serial.println(temperatureC);                      //printen van de temperatuur in de seriële poort
  if(temperatureC < 32){                             //wanneer de temperatuur kleiner is dan 32 graden zal de gate van de mosfet van het peltier module dicht gaan
    digitalWrite(warmte, HIGH);       
    }else if(temperatureC> 35){
      digitalWrite(warmte, LOW);
    }
} 
