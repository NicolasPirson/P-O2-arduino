int pin = 2;
float Speed = 0.0;
volatile bool state = LOW;
volatile float Time;
volatile float prevTime;

void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pin), sensor, FALLING);
  
}

void loop() {
  Speed = 0.251/((Time-prevTime)/1000000);
  Serial.print(Time);
  Serial.print(" ");
  Serial.print(Speed);
  Serial.print(" ");
  Serial.println(state);
}


void sensor (){
  state = !state;
  prevTime = Time;
  Time = micros();
}


/*
void sensor(){
  
  if (state == LOW){
    Time = micros();
    state = HIGH;
  }
  if (state == HIGH){
    float diff = micros() - Time;
    state = LOW;
  }
}
*/
