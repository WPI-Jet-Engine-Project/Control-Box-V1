// PWM out, in microseconds
// 10-bit ADC in
#include <Servo.h>

// Function Prototypes
void setDutyCycle(int throttle);

// pwmPin can be either 3 or 11 in order to use timer 2 for proper pwm configuration
int pwmPin = 9;

int armingSwitchPin = 14;
int throttlePin = A1;


Servo mockReceiver;

void setup() {
  pinMode (pwmPin, OUTPUT);


  // Try to use servo's default 50Hz PWM signal to mock the FrSky receiver
  // 1.1ms and 1.71ms are the min and max pulse width, but this didn't seem to change anything
  mockReceiver.attach(pwmPin, 1100, 1725);
  


  sei();        // re-allow interrupts.
  Serial.begin(9600);
  // end of setup
}

/* Max throttle increases duty cycle by 2.25%
 * Trim increases duty cycle by ~0.005%/tick
 * Base duty cycle is 5.75%
 */

void loop() {
  if(digitalRead(armingSwitchPin)){
    // Throttle reading from 0-1023 (13.5mV to 5.03 V)
    int throttleRead = analogRead(throttlePin);
    // 87 and 139 are manually tuned bound because setting min/max pulse width didn't seem to work.
    // 87 degrees on the servo corresponds to a 1.35 ms pulse width (zero throttle with trim)
    // 139 degrees on the servo corresponds to a 1.725 ms pulse width (max throttle with trim)
    int mappedVal = map(throttleRead, 0, 1023, 1350, 1725);
    Serial.println(mappedVal);
    mockReceiver.writeMicroseconds(mappedVal);
  } else{
  // No signal should be sent if the arming switch is not on
  mockReceiver.write(0);
  }
}
