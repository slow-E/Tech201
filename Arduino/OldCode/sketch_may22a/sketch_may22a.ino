void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(10, 125);
  delay(1000);
  analogWrite(10, 50);
  delay(1000);
  analogWrite(10, 222);
  delay(1000);
}