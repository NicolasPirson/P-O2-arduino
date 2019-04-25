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
