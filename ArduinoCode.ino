#include <PWMSoft.h>
#include <SoftwareSerial.h>

int Duwmotor;
int Versnel_Motor;
int Servo;
int Speed_Trigger_1;
int Speed_Trigger_2;

void setup(){
  pinMode(Servo,OUTPUT);
  pinMode(Duwmotor,OUTPUT);
  pinMode(Versnel_Motor,OUTPUT);
  pinMode(Speed_Trigger_1,INPUT);
  pinmode(Speed_Trigger_2,INPUT);

}

void loop(){
  
}

void SnelheidMeting(){
  
  int Lichtniveau1 = digitalRead(Speed_Trigger_1);
  int Lichtniveau2 = digitalRead(Speed_Trigger_2);
    
  //tijd meten: millis();
  if (Lichtniveau1 == 0){   // 0 moet vervangen worden met waarde die verkregen wordt wanneer pingpongbal voor licht staat
    start = millis();
  }
  if (Lichtniveau2 == 0){   
    finish = millis();
    
  }
  verlopen_tijd = finish-start
  snelheid = 0.04/verlopen_tijd*(pow(10,-3)) // met afstand = de afstand tussen de 2 gaten = 4cm
}
