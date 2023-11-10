int PWMPin = 3;
// int SoftStopPin = 14;
int ThrottlePin = 15;
int Throttle;
float ThrottlePercent;
float DutyOn = 0;
int DutyTime = 0;
void setup() {
  pinMode(11, OUTPUT);
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);
  TCCR2B = TCCR2B & 0b11111000 | 0x07;
  OCR2A = 180;
  OCR2B = 50;
  Serial.begin(9600);
}
// fucking breaks below 100ish Hz kill me
void loop() {
  int throttleRead = analogRead(A1);
  int throttle = 256*throttleRead/1024;
  analogWrite(11,throttle);
}
