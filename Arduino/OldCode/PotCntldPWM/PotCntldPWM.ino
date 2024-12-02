

// include the library code:
#include <Servo.h>

//Servo myservo;

//#define servoPin 9

// int pwm_out_pin = 6;
//int pot_in_pin = A0;
int pwm_out_pin = 9;
//int pot_value = 0;
int pwm_out_value = 40;

void setup() {
  //pinMode(pwm_out_pin, OUTPUT);
  //pinMode(pot_in_pin, INPUT);
  Serial.begin(9600);
}

void loop() {

  // pot_value = analogRead(pot_in_pin);
 pwm_out_value = 200;
    analogWrite(pwm_out_pin, pwm_out_value);
    delay(1000);
    
  if (Serial.available() > 0) {
    // get incoming byte:
    //pot_value = Serial.read();

    Serial.print("pot_value is: ");
   // Serial.println(pot_value);

    //analogRead(pot_in_pin);
   
  }
}
