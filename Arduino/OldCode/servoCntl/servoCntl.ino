

// include the library code:
#include <Servo.h>

Servo myservo;

#define servoPin 6


int pot_value = 0;
// Create a variable to store the servo position:
int angle = 0;


void setup() {

  myservo.attach(servoPin);

  Serial.begin(9600);
}

void loop() {

  myservo.write(90);
  delay(1000);
  myservo.write(100);
  delay(1000);
  myservo.write(180);
  delay(1000);
  // Sweep from 0 to 180 degrees:
  for (angle = 0; angle <= 180; angle += 1) {
    myservo.write(angle);
    delay(15);
  }
  // And back from 180 to 0 degrees:
  for (angle = 180; angle >= 0; angle -= 1) {
    myservo.write(angle);
    delay(30);
  }
  delay(1000);

}
