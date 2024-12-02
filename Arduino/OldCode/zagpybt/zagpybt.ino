int r_motor_pwm = 10;  //PWM control Right Motor -
int l_motor_pwm = 11;  //PWM control Right Motor +

int r_dir = 5;      //PWM control Left Motor +
int l_dir = 6;      //PWM control Left Motor -
char incomingByte;  // for incoming serial data
#include <Wire.h>
#include <SoftwareSerial.h>

//SoftwareSerial BTserial(12, 13);
SoftwareSerial BTserial(13, 12);

void setup() {
  pinMode(r_motor_pwm, OUTPUT);  //Set control pins to be outputs
  pinMode(l_motor_pwm, OUTPUT);
  pinMode(r_dir, OUTPUT);
  pinMode(l_dir, OUTPUT);

  digitalWrite(r_motor_pwm, LOW);  //set both motors off for start-up
  digitalWrite(l_motor_pwm, LOW);
  digitalWrite(r_dir, LOW);
  digitalWrite(l_dir, LOW);
  //Setup usb serial connection to computer
  Serial.begin(115200);
  Serial.println("115200");
  //Setup BTserial serial connection to android
  BTserial.begin(9600);
  delay(100);
  BTserial.println("U,9600,N");
  BTserial.begin(9600);
}

void loop() {


  if (BTserial.available() > 0) {
    // read the incoming byte:
    incomingByte = BTserial.read();
    Serial.println("BTserial available");
    Serial.write(incomingByte);
  }

  switch (incomingByte) {
    case '1':

      Serial.println("wtf\n");
      incomingByte = '*';
      delay(100); 
      break;
    case 's':
      digitalWrite(r_motor_pwm, LOW);  //Set motor direction, 1 low, 2 high
      digitalWrite(l_motor_pwm, LOW);
      digitalWrite(r_dir, LOW);
      digitalWrite(l_dir, LOW);
      Serial.println("Received s\n");
      incomingByte = '*';

      break;

    case 'f':
      digitalWrite(r_dir, LOW);  //Set motor direction, 1 low, 2 high
      analogWrite(r_motor_pwm, 95);
      digitalWrite(l_dir, HIGH);
      analogWrite(l_motor_pwm, 95);
      Serial.println("f\n");
      incomingByte = '*';
      break;

    case 'b':
      digitalWrite(r_dir, HIGH);  //Set motor direction, 1 low, 2 high
      analogWrite(r_motor_pwm, 95);
      digitalWrite(l_dir, LOW);
      analogWrite(l_motor_pwm, 95);
      Serial.println("b\n");
      incomingByte = '*';
      break;

    case 'l':
      digitalWrite(r_dir, HIGH);  //Set motor direction, 1 low, 2 high
      analogWrite(r_motor_pwm, 65);
      digitalWrite(l_dir, HIGH);
      analogWrite(l_motor_pwm, 65);
      Serial.println("l\n");
      incomingByte = '*';
      break;


    case 'r':
      digitalWrite(r_dir, LOW);  //Set motor direction, 1 low, 2 high
      analogWrite(r_motor_pwm, 65);
      digitalWrite(l_dir, LOW);
      analogWrite(l_motor_pwm, 65);
      Serial.println("r\n");
      incomingByte = '*';
      break;


      delay(500);
  }
}