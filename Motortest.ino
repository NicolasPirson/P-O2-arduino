#include <PWMSoft.h>
#include <SoftPWM_timer.h>

int Duwmotor = 10;
int motor = 6;

int Speed;

void setup() {
  Serial.begin(9600);
  pinMode(motor,OUTPUT);
  pinMode(Duwmotor,OUTPUT);

  SoftPWMBegin();
  delay(10);
  SoftPWMSet(Duwmotor,0);
  
  
  Serial.print("Start ok");

}

void loop() {
  if(Serial.available()){
    
    Speed = Serial.parseInt();

    SoftPWMSet(motor, Speed);
    delay(20000);

    
    

  }

}
