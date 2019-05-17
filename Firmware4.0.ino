#include <AltSoftSerial.h>
#include <PWMSoft.h>
#include <SoftPWM_timer.h>

AltSoftSerial btSerial;

int Duwmotor = 10;
int motor = 6;
int servo = 7;
int RedLED = 11;

volatile int starttime;
volatile int stoptime;
volatile bool state = false;
volatile int shootCount = 0;
volatile int passed = false;

String command;
String number;

int Redpin = A1;
int Greenpin = A3;
int Bluepin = A2;
int R;
int G;
int B;

float deltaspeed;
int consecs = 1;
int timeout = 2000;

int Speed;
int Angle;
int DuwmotorInterval = 800;

void setup() {
  Serial.begin(9600);
  delay(200);
  btSerial.begin(9600);
  delay(200);
  pinMode(servo,OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(Duwmotor,OUTPUT);
  
  pinMode(Redpin,OUTPUT);
  pinMode(Greenpin,OUTPUT);
  pinMode(Bluepin,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(3), port2, FALLING);
  attachInterrupt(digitalPinToInterrupt(2), port1, FALLING);

  digitalWrite(RedLED,HIGH);

  SoftPWMBegin();
  delay(10);
  SoftPWMSet(servo,23);
  SoftPWMSetPercent(Duwmotor,0);
  SoftPWMSet(Redpin,0);
  SoftPWMSet(Greenpin,0);
  SoftPWMSet(Bluepin,0);
  
  
  Serial.println("Start ok");

}

void loop() {
  //Manual overwrite
  
  if(Serial.available()){
    Speed = Serial.parseInt();
    Angle = Serial.parseInt();
    
    if(Speed == 1234){
      ShowData();
    }
    else{
      Move_Machine();
    }   
  }
  else{
    //Bluetooth commandos ontvangen
    checkSerial();
  }

  
//  // Bereken de beginsnelheid en verzend en stop accelerator
//  if(state == true){
//    
//    deltaspeed = (0.04)/((stoptime-starttime)*pow(10,-6));
//    state = false;
//    
//    Serial.println(deltaspeed);
//    btSerial.println(deltaspeed);
//    SoftPWMSetPercent(motor,0);
//  }
   
}

/*----------------------------------------------------------------*/
/*----------------------------------------------------------------*/

// interrupt code voor de sensor

void port1(){
  starttime = micros();
  shootCount += 1;
  passed = true;
  Serial.println(passed);
}

void port2(){
  stoptime = micros();
  state = true;
  Serial.println(state);
}

/*----------------------------------------------------------------*/

//verwerking ingezonden commando's

/* voor links --> pos1
 * achter links --> pos2
 * voor rechts --> pos 3
 * achter rechts --> pos 4
 */

void checkSerial(){
  if (btSerial.available()){
    Serial.println("IF");
    delay(10);
    for (int i = 1; i <= 10; i++){
    char c = btSerial.read();
    command += c;
    }
    if (command.length() > 0){
      Serial.println(command);
      if (command.startsWith("COORD/")){
        Serial.println("COORD");
        number = command.substring(command.indexOf("/") + 1);
        Serial.println(number.substring(0,4));
        
        if (number.substring(0,4) == ("pos1")){
          //voor links
          Serial.println("pos1");
          
          Angle = 140;
          Speed = 60;
          Move_Machine();
        }
        else if (number.substring(0,4) == ("pos2")){
          //achter links
          Serial.println("pos2");
          
          Angle = 140;
          Speed = 100;
          Move_Machine();
        }
        else if (number.substring(0,4) == ("pos3")){
          //voor rechts
          Serial.println("pos3");
          
          Angle = 110;
          Speed = 60;
          Move_Machine();
        }
        else if (number.substring(0,4) == ("pos4")){
          //achter rechts
          Serial.println("pos4");
          
          Angle = 110;
          Speed = 100;
          Move_Machine();
        }
      }
      /* Difficulty
       *  DIFF/
       *  -EASY
       *  -NORM
       *  -HARD
       */
       
      else if (command.startsWith("DIFF/")){
        Serial.println("COORD");
        number = command.substring(command.indexOf("/") + 1);
        Serial.println(number.substring(0,4));

        if (number.substring(0,4) == ("EASY")){
          DuwmotorInterval = 1000;
          R = 255;
          G = 0;
          B = 255;
          SetRGB();
        }
        else if (number.substring(0,4) == ("NORM")){
          DuwmotorInterval = 500;
          R = 255;
          G = 255;
          B = 0;
          SetRGB();
        }
        else if (number.substring(0,4) == ("HARD")){
          DuwmotorInterval = 200;
          R = 0;
          G = 255;
          B = 255;
          SetRGB();
        }
      }
      /* Stel hethaling in */ 
      else if(command.startsWith("REPEAT/")){
        Serial.println("REPEAT/");
        number = command.substring(command.indexOf("/") + 1);
        Serial.println(number.substring(0,2));
        
        consecs = constructDigit();
      }
      command = "";
    }
  }
}

void checkForQuit(){
  if (btSerial.available()){
    Serial.println("IF");
    delay(10);
    for (int i = 1; i <= 10; i++){
    char c = btSerial.read();
    command += c;
    }
    
    Serial.print(command);
    
    if(command.length() > 0){
      if (command.startsWith("QUIT")){
        Serial.print("entered state");
        shootCount = consecs;
        passed = true;
      }
    }
    command = "";
  } 
}

/*-------------------------------------------------*/

// Data operatoren

bool contrDigit(){
  for(int i=0;i<2;i++){
    if(!isDigit(number[i])){
      return false;
    }
  }
  Serial.println("TRUE");
  return true;
}

int constructDigit(){
  //number = number.substring(0,2);
  Serial.println(number);
  int num = number.toInt();
  Serial.println(num);
  //Serial.println(num);
  return num;
}

/*----------------------------------------------------------------*/

// Beweeg de machine

void Move_Machine(){  
  Serial.print("Countinit: ");
  Serial.println(shootCount);

  int servoVal = map(Angle,0,240,8,37);
  SoftPWMSet(servo,servoVal);
  
  SoftPWMSetPercent(motor, Speed);
  delay(1800);
  SoftPWMSetPercent(Duwmotor,100);


  while(shootCount < consecs){
    Serial.print("Count: ");
    Serial.println(shootCount);
   
    while(!passed){
       checkForQuit();
       checkSerial();
       Serial.print(".");
  
    }
    passed = false;
    
    SoftPWMSetPercent(Duwmotor,0);
    pause();
    // Bereken de beginsnelheid en verzend en stop accelerator
    if(state == true){
        Serial.println("*");
        deltaspeed = (0.04)/((stoptime-starttime)*pow(10,-6));
        state = false;
        
        Serial.println(deltaspeed);
        btSerial.println(deltaspeed);
    }

    SoftPWMSetPercent(Duwmotor,100);
    
  }
  SoftPWMSetPercent(Duwmotor,0);
  SoftPWMSetPercent(motor,0);
  shootCount = 0;
}

void pause(){
  int initialTime = millis();
  int passedTime = 0;

  while(passedTime < DuwmotorInterval){
    passedTime = millis() - initialTime;
    // just wait and let interrupts do their job
  }
}

void SetRGB(){
  SoftPWMSet(Redpin,R);
  SoftPWMSet(Greenpin,G);
  SoftPWMSet(Bluepin,B);
}

void ShowData(){
  Serial.println("______________________");
  Serial.print("herhalingen: ");
  Serial.println(consecs);
  Serial.print("Versnelmotor speed: ");
  Serial.println(Speed);
  Serial.print("Angle: ");
  Serial.println(Angle);
  Serial.print("DuwmotorInterval: ");
  Serial.println(DuwmotorInterval);
  Serial.print("State: ");
  Serial.println(state);
  Serial.println("______________________");
}

