

// millis() counter
long previousMils1 = 0;
long previousMils2 = 0;
long scanTriggerTime = 250;
long updateMotorTime = 500;

// Motor speed adjust
int speedAdjust = 50;

// Motor A connections
int enA = 3;
int in1 = 6;
int in2 = 7;
// Motor B connections
int enB = 8;
int in3 = 5;
int in4 = 2;

//Sonic sensors
int sens1_trig = 13;
int sens1_echo = 12;
int sens2_trig = 9;
int sens2_echo = 11;

int Prox_data = 0;
int motPwm1 = 0;
int motPwm2 = 0;

uint8_t result = 0;

// defines variables
long duration;
int distance1;
int distance2;
///////////////////////////////////////////////
///////////  VOID SETUP() ///////////////////////////
void setup() {


  Serial.begin(9600);
  pinMode(sens1_trig, OUTPUT); // Sets the sens1_trig as an Output
  pinMode(sens1_echo, INPUT); // Sets the sens1_echo as an Input
  pinMode(sens2_trig, OUTPUT); // Sets the sens1_trig as an Output
  pinMode(sens2_echo, INPUT); // Sets the sens1_echo as an Input
  // Clears the sens1_trig
  digitalWrite(sens1_trig, LOW);

  // Set all the motor control pins to outputs

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Test LED
  pinMode(LED_BUILTIN, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  //Serial.println("Hello");

}

//////////////////////////////////////////////////
////////////////////////VOID LOOP()///////////////
void loop() {
  //Serial.println("test");
  unsigned long currentMils = millis();



  if (currentMils - previousMils1 > updateMotorTime) {
    previousMils1 = currentMils;

    //	if distance1 is too close, stop and turn....
    if (distance1 <= 30) {
      motPwm1 = 50;
      motPwm2 = 50;
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      delay(500);
      Serial.println("STOP");
    }
    else {
      //else follow the wall.
      motPwm1 = 75; //distance2; //Rigth, starboard.
      motPwm2 = 50 + distance2;  //Left, port

      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enA, motPwm1);

      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enB, motPwm2);

      Serial.print("PWM 1 = ");
      Serial.println (motPwm1);
      Serial.print("PWM 2 = ");
      Serial.println (motPwm2);
    }
  }



  if (currentMils - previousMils2 > scanTriggerTime) {
    previousMils2 = currentMils;

    //----------------------Front Sensor----------------//
    digitalWrite(sens1_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(sens1_trig, LOW);
    // Reads the sens1_echo, returns the sound wave travel time in microseconds
    duration = pulseIn(sens1_echo, HIGH);
    // Calculating the distance
    distance1 = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    //	Serial.print("Distance1: ");
    //	Serial.println(distance1);

    delayMicroseconds(3000);
    //-------------------Side Sensor--------------------//
    // Sets the sens2_trig on HIGH state for 10 micro seconds
    digitalWrite(sens2_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(sens2_trig, LOW);
    // Reads the sens2_echo, returns the sound wave travel time in microseconds
    duration = pulseIn(sens2_echo, HIGH);
    // Calculating the distance
    distance2 = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    //	Serial.print("Distance2: ");
    //	Serial.println(distance2);
    if (distance2 >= 255) {
      distance2 = 255;
    }
  }








  //  if (currentMils - previousMils2 >= updateMotorTime) {
  //    previousMils2 = currentMils;
  //
  //
  //  }

}

///////////////END VOID LOOP()



//////////////////////////////////////////////////
///  FUNCTIONS
//////////////////////////////////////////////////
