
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
