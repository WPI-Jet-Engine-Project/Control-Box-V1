// PWM out, in microseconds
// 10-bit ADC in
#include <Servo.h>

// Function Prototypes
void setDutyCycle(int throttle);

// pwmPin is pin 9 so that the Servo library can use Timer 1 in the background
int pwmPin = 9;

int armingSwitchPin = 13;
int throttlePin = A1;

Servo mockReceiver;

void setup() {
  pinMode (pwmPin, OUTPUT);

  // Try to use servo's default 50Hz PWM signal to mock the FrSky receiver
  // 1.1ms and 1.71ms are the min and max pulse width, but this didn't seem to change anything
  mockReceiver.attach(pwmPin, 1100, 1725);
  
  Serial.begin(9600);
  // end of setup
}

/* Max throttle increases pulse width by almost 400 us
 * Trim increases pulse width by ~4us/tick
 * Base signal is 1100 us
 */

void loop() {
  if(digitalRead(armingSwitchPin)){
    // Throttle reading from 0-1023 (13.5mV to 5.03 V)
      int throttleRead = analogRead(throttlePin);
      // 87 and 139 are manually tuned bound because setting min/max pulse width didn't seem to work.
      // 87 degrees on the servo corresponds to a 1.35 ms pulse width (zero throttle with trim)
      // 139 degrees on the servo corresponds to a 1.725 ms pulse width (max throttle with trim)
      int mappedVal = map(throttleRead, 0, 1023, 1200, 1725);
      Serial.println(mappedVal);
      mockReceiver.writeMicroseconds(mappedVal);
  } else{
  // No signal should be sent if the arming switch is not on
  mockReceiver.writeMicroseconds(1000);
  }
//  if( Serial.available()){
//    int input = Serial.readStringUntil('\n').toInt();
//    int mappedVal = map(input, 0, 1023, 1350, 1725);
//    Serial.println(mappedVal);
//    mockReceiver.writeMicroseconds(mappedVal);
//    
//  }
}
