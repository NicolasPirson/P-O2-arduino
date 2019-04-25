void checkBluetooth() {
  
  while (bluetoothSerial.available())
  {
    char c = bluetoothSerial.read();
    command += c;
  }
  if (command.length() > 0){
    
    if (command.startsWith("COORD/")){// coördinaten voor pingpongtafel
      String vervolg = command.substring(command.indexOf("/") + 1);
      if (vervolg == "RANDOM" ){
        int x = (rand()%100 + 1); // willekeurige waarde tussen 1 en 100
        int y = (rand()%100 + 1); // zelfde
        
        Versnel_Motor_Speed = sqrt((pow(x,2))+(pow(y,2))); // aanpassen om juiste snelheid te krijgen, waarschijnlijk vermenigvuldigen
        //met waarde om in verhouding te brengen met bord
        Servo_Angle = atan(y/x);
        Duwmotor_Speed = 0;
      }
      else if (vervolg == "pos1"){//
        Versnel_Motor_Speed = 0;//waarde invoegen
        Servo_Angle = 0;
        Duwmotor_Speed = 0;
        End_command();
      }
      else if (vervolg == "pos2"){
        Versnel_Motor_Speed = 0;//waarde invoegen
        Servo_Angle = 0;
        Duwmotor_Speed = 0;
        End_command();
      }
      else if (vervolg == "pos3"){
        Versnel_Motor_Speed = 0;//waarde invoegen
        Servo_Angle = 0;
        Duwmotor_Speed = 0;
        End_command();
      }
      else if (vervolg == "pos4"){
        Versnel_Motor_Speed = 0;//waarde invoegen
        Servo_Angle = 0;
        Duwmotor_Speed = 0;
        End_command();
      }
      else if (vervolg == "pos5"){
        Versnel_Motor_Speed = 0;//waarde invoegen
        Servo_Angle = 0;
        Duwmotor_Speed = 0;
        End_command();
      }
      else if (vervolg == "pos6"){
        Versnel_Motor_Speed = 0;//waarde invoegen
        Servo_Angle = 0;
        Duwmotor_Speed = 0;
        End_command();
      }     

    }
    /*else if (command.startsWith){
      pass
    }*/
    Serial.println("Ontvangen commando: " + command);
    command = ""; // klaar om een nieuw commando te ontvangen

  }

}
