

// include the library code:
#include <LiquidCrystal.h>
#include<Wire.h>

// Vars for the MEMs accelerometer
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Joystick pins
const int SW_pin = 2; // Digital input from joystick
const int X_pin = A1; // analog x direction pin
const int Y_pin = A0; // analog Y direction pin

// Photo Resistor input
const int photoPin = A2;

// Variables for timing different events
int interval1 = 200;
int interval2 = 700;
int interval3 = 500;

int prevTime1 = 0;
int prevTime2 = 0;
int prevTime3 = 0;

int photoVal = 0;

int x_value, y_value = 0;
void setup() {

  // Setup for I2C and serial bus
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);


  //For the joystick digital input.
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);  //Why write to an input?

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("X = ");
  lcd.setCursor(0, 1);
  lcd.print("Y = ");
    lcd.setCursor(9, 0);
  lcd.print("PR=");
}

void loop() {
  unsigned long currentMils = millis();
  ///////////////LCD
  if (millis() - prevTime1 > interval1) {
    prevTime1 = millis();
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.print(" ");
    lcd.setCursor(4, 0);
    lcd.print(x_value);
    lcd.setCursor(4, 1);
    lcd.print(y_value);
    lcd.setCursor(12, 0);
    lcd.print(photoVal);

  }

  ///////////////Analog Inputs
  if (millis() - prevTime2 > interval2) {
    prevTime2 = millis();
    x_value = analogRead(X_pin);
    y_value = analogRead(Y_pin);

    photoVal = analogRead(photoPin);
  }

  ///////////////// I2C interface to Accelerometer
  if (millis() - prevTime3 > interval3) {
    prevTime3 = millis();
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
    AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    Serial.print("AcX = "); Serial.print(AcX);
    Serial.print(" | AcY = "); Serial.println(AcY);
    //  Serial.print(" | AcZ = "); Serial.print(AcZ);
    //  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
    //  Serial.print(" | GyX = "); Serial.print(GyX);
    //  Serial.print(" | GyY = "); Serial.print(GyY);
    //  Serial.print(" | GyZ = "); Serial.println(GyZ);

  }
  delay(10);


}
