#include <AltSoftSerial.h>
#include <PWMSoft.h>
#include <math.h>

AltSoftSerial bluetoothSerial;

String command;

int Duwmotor = 6;       //insert default values
int Versnel_Motor = 10;
int Servo_Motor = 7;
int Speed_Trigger_1 = 2;
int Speed_Trigger_2 = 3;
int ledRED = 11;

int Servo_Angle;
int Duwmotor_Speed;
int Versnel_Motor_Speed;

int PWM[] = {Duwmotor,Versnel_Motor,Servo_Motor,ledRED};

volatile int Time_begin;
volatile int Time_end;
volatile bool State = false;
float Speed;

bool Error_occured = false;
String Error_type[2]= {};

/*----------------------------------------------------*/

void setup(){
  
  SoftPWMBegin();
  delay(100);
  bluetoothSerial.begin(9600);
  delay(100);
  Serial.begin(9600);
  delay(100);
  
  for(int i=0; i < sizeof(PWM) - 1; i++){
    pinMode(PWM[i],OUTPUT);
    SoftPWMSet(PWM[i],0);
  }
  
  //interrupts
  attachInterrupt(digitalPinToInterrupt(Speed_Trigger_1),slot_1,FALLING);
  attachInterrupt(digitalPinToInterrupt(Speed_Trigger_2),slot_2,FALLING);
  

}

/*----------------------------------------------------*/

void loop(){
  checkBluetooth();

  if(!Error_occured){
    Speed = velocity();
    Serial.println(Speed);
    bluetoothSerial.println(Speed);
  }
  else{
    Display_error();
  }
  

}
          
          
          
