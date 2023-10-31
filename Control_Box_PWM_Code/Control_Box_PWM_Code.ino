int PWMPin = 3;
int SoftStopPin = 14;
int ThrottlePin = 15;
int ThrottlePercent = 0;
void setup() {
  pinMode(PWMPin, OUTPUT);
  pinMode(SoftStopPin, INPUT);
  pinMode(ThrottlePin, INPUT);
}

void loop() {
  bool stop_check = digitalRead(SoftStopPin);
  if(stop_check){
    ThrottlePercent = (analogRead(ThrottlePin)/1024)*256-1;
    analogWrite(PWMPin, ThrottlePercent);
  }
  else{
    ThrottlePercent = 0;
    }
    
}
