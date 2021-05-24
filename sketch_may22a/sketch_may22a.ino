int readl;

int ledState = LOW;

unsigned long previousMillis = 0;


const long interval = 100;

int timeState_2 = LOW;
int timeState_3 = LOW;
int timeState_4 = LOW;
int timeState_5 = LOW;
int timeState_6 = LOW;
int timeState_7 = LOW;

void aan(int trigger){
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
     case 6: timeState_6 = HIGH; break;
     case 7: timeState_7 = HIGH; break;
     default:break;
   }
}

void changeTimeL(int x){
   switch(x){
     case 2: timeState_2 = LOW; break;
     case 3: timeState_3 = LOW; break;
     case 4: timeState_4 = LOW; break;
     case 5: timeState_5 = LOW; break;
     case 6: timeState_6 = LOW; break;
     case 7: timeState_7 = LOW; break;
     default:break;
   }
}

void setup() {

  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {

  if(timeState_2 == HIGH){
      digitalWrite(2, ledState);}
  if(timeState_3 == HIGH){
     digitalWrite(3, ledState);}
  if(timeState_4 == HIGH){
     digitalWrite(4, ledState);}
  if(timeState_5 == HIGH){
     digitalWrite(5, ledState);}
  if(timeState_6 == HIGH){
     digitalWrite(6, ledState);}
  if(timeState_7 == HIGH){
     digitalWrite(7, ledState);}

  unsigned long currentMillis = millis();
        
  if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        if (ledState == LOW){
         ledState = HIGH;}
        else{
          ledState = LOW;
          }

      
  }

  if(Serial.available()>0){
      readl = Serial.parseInt();
      int soort_strobo = readl / 10;
      int soort_tijd = readl % 10;

      if(soort_tijd == 1){
       changeTimeL(soort_strobo);
       uit(soort_strobo);
        }

      if(soort_tijd == 2){
        changeTimeL(soort_strobo);
        aan(soort_strobo);
        }

      if(soort_tijd == 3){
        changeTimeH(soort_strobo);
}
}
}
