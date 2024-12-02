int red_pin = 9;
int green_pin = 10;
int blue_pin = 11;
void setup() {
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);


  // put your setup code here, to run once:
}

void loop() {
for (int x=0;x<255;x++;int y=255;y=0;y++) {
  analogWrite(red_pin, x);
  delay(100);
analogWrite(redpin, y);
delay(100);
  analogWrite(green_pin,x);
  delay(100);
  analogWrite(green_pin,y);
delay(100)
  analogWrite(blue_pin, x);
  delay(100);
analogwrite(blue_pin, y);
delay(100)
  }
  // put your main code here, to run repeatedly:
}