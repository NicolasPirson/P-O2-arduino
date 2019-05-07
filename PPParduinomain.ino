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
//input/************************************************************************************************
void slot_1(){
  Time_begin = micros();
  
}

void slot_2(){
  Time_end = micros();
  State = true;
}

float velocity(){
  int initial_time = millis();
  int delta_time = 0;
  while(!State){
    if(delta_time > 1000){
      Error_occured = true;
      Error_type[0] = "velocity timeout";
      return 0;
    }
    delta_time = millis() - initial_time;
  }

  return 0.04/((Time_end - Time_begin)/1000000);
//output/*********************************************************************************************************
void Move_Machine(){
  SoftPWMSetDegree(Servo_Motor, Servo_Angle);
  delay(100);
  SoftPWMSetPercent(Versnel_Motor, Versnel_Motor_Speed);
  SoftPWMSetPercent(Duwmotor, Duwmotor_Speed);
}

void End_command(){
  int initial_time = millis();
  int delta_time = 0;
  while(!State){
    // Do nothing (wait for the ball to pass the second slot)
    // Check if it is taking to long
    if(delta_time > 1000){
      State = true;
      Error_occured = true;
      Error_type[1] = "End_command timeout";
    }
    delta_time = millis() - initial_time;
  }
  Versnel_Motor_Speed = 0;//waarde invoegen
  Servo_Angle = 0;
  Duwmotor_Speed = 0;

  Move_Machine();
  
}

void Display_error(){
  Serial.print("Error Occured");
  for(int i=0; i < sizeof(Error_type) - 1; i++){
    Serial.print(i);
    Serial.print("  ");
    Serial.println(Error_type[i]);
  }
  bluetoothSerial.print("ERROR");
}
//bluetooth/******************************************************************************************************
void checkBluetooth() {
  
  if (bluetoothSerial.available()){
    delay(10);
    for (int i = 1; i <= 10; i++){
      char c = bluetoothSerial.read();
      command += c;
    }
    
  }
    if (command.length() > 0){
    
      if (command.startsWith("COORD/")){// coördinaten voor pingpongtafel
        String vervolg = command.substring(command.indexOf("/") + 1);
        if (vervolg.substring(0,4) == "RAND" ){
          int x = (rand()%100 + 1); // willekeurige waarde tussen 1 en 100
          int y = (rand()%100 + 1); // zelfde
        
          Versnel_Motor_Speed = sqrt((pow(x,2))+(pow(y,2))); // aanpassen om juiste snelheid te krijgen, waarschijnlijk vermenigvuldigen
          //met waarde om in verhouding te brengen met bord
          Servo_Angle = atan(y/x);
          Versnel_Motor_Speed = 0;
        }
        else if (vervolg.substring(0,4) == "pos1"){
          Versnel_Motor_Speed = 0;//waarde invoegen
          Servo_Angle = 0;
          End_command();
        }
        else if (vervolg.substring(0,4) == "pos2"){
          Versnel_Motor_Speed = 0;//waarde invoegen
          Servo_Angle = 0;
          End_command();
        }
        else if (vervolg.substring(0,4) == "pos3"){
          Versnel_Motor_Speed = 0;//waarde invoegen
          Servo_Angle = 0;
          End_command();
        }
        else if (vervolg.substring(0,4) == "pos4"){
          Versnel_Motor_Speed = 0;//waarde invoegen
          Servo_Angle = 0;
          End_command();
        }
        else if (vervolg.substring(0,4) == "pos5"){
          Versnel_Motor_Speed = 0;//waarde invoegen
          Servo_Angle = 0;
          End_command();
        }
        else if (vervolg.substring(0,4) == "pos6"){
          Versnel_Motor_Speed = 0;//waarde invoegen
          Servo_Angle = 0;
          End_command();
        }     

      }
      else if (command.startsWith("DIFF/"){
        String vervolg = command.substring(command.indexOf("/") + 1);
        if (vervolg.substring(0,4) == "EASY"){
          Duwmotor_Speed = 0;//waarde invoegen
          End_command();
        }
        else if (vervolg.substring(0,4) == "NORMAL"){
          Duwmotor_Speed = 0;//waarde invoegen
          End_command();
        }
        else if (vervolg.substring(0,4) == "HARD"){
          Duwmotor_Speed = 0;//waarde invoegen
          End_command();
        }
      }
      else if (command.startsWith("QUIT"){
        int Versnel_Motor_Speed = 0;
        int Duwmotor_Speed = 0;
        int val = 0;//value
        Servo_Angle = map(val,-120,120,8,37);//hoek waardoor recht vooruit mikt
        //interrupt invoegen om alles te stoppen
      }
             
    Serial.println("Ontvangen commando: " + command);
    command = ""; // klaar om een nieuw commando te ontvangen

  }

}
