#include <PWMSoft.h>
#include <SoftwareSerial.h>
#include <math.h>


int Duwmotor = ;       //insert default values
int Versnel_Motor = ;
int Servo = ;
int Speed_Trigger_1 = ;
int Speed_Trigger_2 = ;
int ledGreen = ;
String command;

void setup(){
  //pins invoeren
  pinMode(7,OUTPUT);//Servo
  pinMode(Duwmotor,OUTPUT);//Duwmotor
  pinMode(Versnel_Motor,OUTPUT);//Versnel_Motor
  pinMode(2,INPUT);//Speed_Trigger_1
  pinmode(3,INPUT);//Speed_Trigger_1
  
  //interrupts
  attachInterrupt(0,powerOnOff,RISING);
  attachInterrupt(1,homePosition,RISING);
  //power aan/ arduino start => groene led aan?
  digitalWrite(ledGreen,HIGH);
  
  

}

void loop(){
  checkBluetooth();
  
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
void checkBluetooth() {
  
  while (bluetoothSerial.available())
  {
    char c = blutoothSerial.read();
    command += c;
  }
  if (command.length() > 0){
    
    if (command.startsWith("COORD/")){// coördinaten voor pingpongtafel
      vervolg = command.substring(command.indefOf("/") + 1);
      if (vervolg == "RANDOM" ){
        x = (rand()%100 + 1); // willekeurige waarde tussen 1 en 100
        y = (rand()%100 + 1); // zelfde
        
        int Versnel_Motor = sqrt((pow(x,2))+(pow(y,2))); // aanpassen om juiste snelheid te krijgen, waarschijnlijk vermenigvuldigen
        //met waarde om in verhouding te brengen met bord
        int Servo = atan(y/x);
      }
      else if (vervolg == "pos1"){//
        int Versnel_Motor = ;//waarde invoegen
        int Servo = ;
      }
      else if (vervolg == "pos2"){
        int Versnel_Motor = ;//waarde invoegen
        int Servo = ;
      }
      else if (vervolg == "pos3"){
        int Versnel_Motor = ;//waarde invoegen
        int Servo = ;
      }
      else if (vervolg == "pos4"){
        int Versnel_Motor = ;//waarde invoegen
        int Servo = ;
      }
      else if (vervolg == "pos5"){
        int Versnel_Motor = ;//waarde invoegen
        int Servo = ;
      }
      else if (vervolg == "pos6"){
        int Versnel_Motor = ;//waarde invoegen
        int Servo = ;
      }
      
       
          

    }
    else if (command.startsWith("QUIT"){
      int Versnel_Motor = 0;
      int Servo = ;//hoek waardoor recht vooruit mikt
    }
            
    else if (command.startsWith("DIFF")){
      vervolg = command.substring(command.indefOf("/") + 1);
      if (vervolg == "EASY"){
        int Duwmotor = ;//snelheid of frequentie invoeren
      }
      else if (vervolg == "NORMAL"){
        int Duwmotor = ;//snelheid of frequentie invoeren
      }
      else if (vervolg == "HARD"){
        int duwmotor = ;//snelheid of frequentie invoeren
     
    
      
          
          
          
          
          
     
    
    

          
        
        
        
        
        
      
        
          
  
        
        
      
      
    
  
  }
  
    
         
         
