int PWMPin = 3;
int SoftStopPin = 14;
int ThrottlePin = 15;
int ThrottlePercent = 0;
float DutyOn = 0;
void setup() {
  pinMode(PWMPin, OUTPUT);
  pinMode(SoftStopPin, INPUT);
  pinMode(ThrottlePin, INPUT);
}

void loop() {
  bool stop_check = digitalRead(SoftStopPin);
  if(stop_check){
    ThrottlePercent = (analogRead(ThrottlePin)/1023);
    DutyOn = (0.05+ (ThrottlePercent * 0.05));
    digitalWrite(PWMPin, HIGH);
    delayMicroseconds(int((DutyOn)*18181));
    digitalWrite(PWMPin, LOW);
    delayMicroseconds(int((1-DutyOn)*18181));

  }
  else{
    ThrottlePercent = 0;
    }
    
}
