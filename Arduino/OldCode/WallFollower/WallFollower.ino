
#include <Wire.h>

// the i2c address
#define VCNL4000_ADDRESS 0x13

// commands and constants
// Register addresses
#define VCNL4000_COMMAND 0x80
#define VCNL4000_PRODUCTID 0x81
#define VCNL4000_IRLED 0x83
#define VCNL4000_AMBIENTPARAMETER 0x84
#define VCNL4000_AMBIENTDATA 0x85
#define VCNL4000_PROXIMITYDATA 0x87
#define VCNL4000_SIGNALFREQ 0x89
#define VCNL4000_PROXINITYADJUST 0x8A
// Frequency set values
#define VCNL4000_3M125 0
#define VCNL4000_1M5625 1
#define VCNL4000_781K25 2
#define VCNL4000_390K625 3
// Bit masks
#define VCNL4000_MEASUREAMBIENT 0x10
#define VCNL4000_MEASUREPROXIMITY 0x08
#define VCNL4000_AMBIENTREADY 0x40
#define VCNL4000_PROXIMITYREADY 0x20

// millis() counter
unsigned long previousMils1 = 0;
unsigned long previousMils2 = 0;
long scanTriggerTime = 500;
long updateMotorTime = 700;

// Motor A connections
int enA = 10;
int in1 = 9;
int in2 = 8;
// Motor B connections
int enB = 11;
int in3 = 12;
int in4 = 13;

int Prox_data = 0;
int motPwm1 = 0;

uint8_t result = 0;

///////////////////////////////////////////////
///////////  VOID SETUP() ///////////////////////////
void setup() {
  Wire.begin();

  Serial.begin(9600);



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
  // Serial.println("w0");
  write8(VCNL4000_IRLED, 20);        // set to 20 * 10mA = 200mA
  // Serial.println("t0");
  write8(VCNL4000_SIGNALFREQ, 3);
  // Serial.println("t1 and then some");
  write8(VCNL4000_PROXINITYADJUST, 0x81);


}

//////////////////////////////////////////////////
////////////////////////VOID LOOP()///////////////
void loop() {
  //Serial.println("test");
  unsigned long currentMils = millis();

  uint8_t result = read8(VCNL4000_COMMAND);

  if (currentMils - previousMils1 >= scanTriggerTime) {
    previousMils1 = currentMils;
    write8(VCNL4000_COMMAND, VCNL4000_MEASUREAMBIENT | VCNL4000_MEASUREPROXIMITY);


    if ((result & VCNL4000_AMBIENTREADY) && (result & VCNL4000_PROXIMITYREADY)) {
      Prox_data = read16(VCNL4000_PROXIMITYDATA);

    }
    motPwm1 = 255 - ((Prox_data - 2100) / 12);
    if (motPwm1 < 20) {
      motPwm1 = 0;
    }
    if (motPwm1 > 125) {
      motPwm1 = 125;
    }
    //   Serial.println("m");
    // Turn on motor A & B
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, motPwm1);


    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enB, motPwm1);
    Serial.println(Prox_data);


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


///// Read 1 byte from the VCNL4000 at 'address'  ////
uint8_t read8(uint8_t address)
{
  uint8_t data;

  Wire.beginTransmission(VCNL4000_ADDRESS);
#if ARDUINO >= 100
  Wire.write(address);
#else
  Wire.send(address);
#endif
  Wire.endTransmission();

  delayMicroseconds(170);  // delay required

  Wire.requestFrom(VCNL4000_ADDRESS, 1);

#if ARDUINO >= 100
  return Wire.read();
#else
  return Wire.receive();
#endif
}


///// Read 2 byte from the VCNL4000 at 'address'//
uint16_t read16(uint8_t address)
{
  uint16_t data;

  Wire.beginTransmission(VCNL4000_ADDRESS);
#if ARDUINO >= 100
  Wire.write(address);
#else
  Wire.send(address);
#endif
  Wire.endTransmission();

  Wire.requestFrom(VCNL4000_ADDRESS, 2);
#if ARDUINO >= 100
  data = Wire.read();
  data <<= 8;
  data |= Wire.read();
#else
  data = Wire.receive();
  data <<= 8;
  data |= Wire.receive();
#endif

  return data;
}

////// write 1 byte ///////
void write8(uint8_t address, uint8_t data)
{
  Wire.beginTransmission(VCNL4000_ADDRESS);
#if ARDUINO >= 100
  Wire.write(address);
  Wire.write(data);
#else
  Wire.send(address);
  Wire.send(data);
#endif
  Wire.endTransmission();
}
