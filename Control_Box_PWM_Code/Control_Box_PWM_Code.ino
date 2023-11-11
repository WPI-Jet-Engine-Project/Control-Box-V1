// 8-bit PWM out
// 10-bit ADC in

// TODO: Minimize use of float operations without losing precision by doing some funky math shenanigans

// Function Prototypes
void setDutyCycle(float percentage);

// pwmPin can be either 3 or 11 in order to use timer 2 for proper pwm configuration
int pwmPin = 3;

int armingSwitchPin = 14;
int throttlePin = A1;

int trimValue = 64;

void setup() {
  pinMode (pwmPin, OUTPUT);

  // Reset prescalers
  GTCCR = bit (PSRASY);        // reset prescaler now

  // mode 15
  TCCR2A = bit (WGM20) | bit (WGM21) | bit (COM2B1); // fast PWM, clear OC2B on compare
  
  // start Timer 2
  TCCR2B = bit (WGM22) | bit (CS20) | bit (CS22); // prescaler of 128
  // 16,000,000 Hz / 128 (prescaler) = 125,000 / 50Hz = 2500 timer ticks per PWM pulse
  OCR2A = 2500 - 1;
  // The clock counts up to 2500 and then jumps down to zero (sawtooth wave)
  // When that counter is above the set value for OCR2B, the pulse width is set high.
  // Therefore, to set the duty cycle in %, you need to do a little math (see function below)
  OCR2B = 2500; // 0% duty cycle to start
  }  // end of setup
  Serial.begin(9600);
}

/* Max throttle increases duty cycle by 2.25%
 * Trim increases duty cycle by ~0.005%/tick
 * Base duty cycle is 5.75%
 */

void loop() {
  if(digitalRead(armingSwitchPin)){
    int throttleRead = analogRead(throttlePin);
    // TODO: With default trim of 64 (trimValue variable), calculate what the % duty cycle is and set it
    setDutyCycle(0.0575);
  } else{
    setDutyCycle(0);
  }
}

void setDutyCycle(float percentage){
  // The clock counts up to 2500 (for 50Hz) and then jumps down to zero (sawtooth wave)
  // When that counter is above the set value for OCR2B, the pulse width is set high.
  // Therefore, to set the duty cycle in %, you need to multiply the max (2500) by (1-%)
  OCR2B = (int) (2500*(1-percentage));
}
