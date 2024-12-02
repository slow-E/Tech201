# is this a comment.  it appears to be.

import RPi.GPIO as GPIO
from time import sleep


GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD) #use physical pin numbering
GPIO.setup(3, GPIO.OUT, initial=GPIO.LOW)  # Set pin 2 to be an output pin, initial value low

while True:  # Run Forever
   GPIO.output(3, GPIO.HIGH) 
   print("Blink on")
   sleep(1)
   GPIO.output(3, GPIO.LOW)
   print("Blink off")
   sleep(1)


