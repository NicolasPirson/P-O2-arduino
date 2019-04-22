#include <PWMSoft.h>
#include <SoftwareSerial.h>
#include <math.h>


int Duwmotor = ;       //insert default values
int Versnel_Motor = ;
int Servo = ;
int Speed_Trigger_1 = ;
int Speed_Trigger_2 = ;

void setup(){
  pinMode(Servo,OUTPUT);
  pinMode(Duwmotor,OUTPUT);
  pinMode(Versnel_Motor,OUTPUT);
  pinMode(Speed_Trigger_1,INPUT);
  pinmode(Speed_Trigger_2,INPUT);
  
  //interrupts
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  attachInterrupt(0,powerOnOff,RISING);
  attachInterrupt(1,homePosition,RISING);
  
  

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
    }
    else if (command.startsWith
          
          
          
          
          
          
     
    
    

          
        
        
        
        
        
      
        
          
  
        
        
      
      
    
  
  }
  
    
         
         
