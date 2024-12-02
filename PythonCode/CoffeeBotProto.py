import time
import RPi.GPIO as GPIO
from adafruit_motorkit import MotorKit

# Set up motor HAT
kit = MotorKit()

# GPIO setup for ultrasonic sensors
GPIO.setmode(GPIO.BCM)

# Define sensor pins (adjust for your setup)
TRIG_PIN1 = 17
ECHO_PIN1 = 23
TRIG_PIN2 = 27
ECHO_PIN2 = 16

GPIO.setup(TRIG_PIN1, GPIO.OUT)
GPIO.setup(ECHO_PIN1, GPIO.IN)
GPIO.setup(TRIG_PIN2, GPIO.OUT)
GPIO.setup(ECHO_PIN2, GPIO.IN)

def get_right_distance():
    # Trigger the sensor
    GPIO.output(TRIG_PIN1, True)
    time.sleep(0.00001)
    GPIO.output(TRIG_PIN1, False)

    # Measure the time for echo response
    start_time = time.time()
    stop_time = time.time()

    while GPIO.input(ECHO_PIN1) == 0:
        start_time = time.time()

    while GPIO.input(ECHO_PIN1) == 1:
        stop_time = time.time()

    # Calculate distance
    time_elapsed = stop_time - start_time
    distance = (time_elapsed * 34300) / 2  # Speed of sound is 34300 cm/s
    return distance

def get_front_distance():
    # Trigger the sensor
    GPIO.output(TRIG_PIN2, True)
    time.sleep(0.00001)
    GPIO.output(TRIG_PIN2, False)

    # Measure the time for echo response
    start_time = time.time()
    stop_time = time.time()

    while GPIO.input(ECHO_PIN2) == 0:
        start_time = time.time()

    while GPIO.input(ECHO_PIN2) == 1:
        stop_time = time.time()

    # Calculate distance
    time_elapsed = stop_time - start_time
    distance = (time_elapsed * 34300) / 2  # Speed of sound is 34300 cm/s
    return distance

kit.motor1.throttle = 0.5
kit.motor2.throttle = 0.5
kit.motor3.throttle = 0.5
kit.motor4.throttle = 0.5

def motorLimit(x):
    if kit.motor1.throttle > x:
        kit.motor1.throttle = x
    elif kit.motor1.throttle < 0:
        kit.motor1.throttle = 0
    if kit.motor2.throttle > x:
        kit.motor2.throttle = x
    elif kit.motor2.throttle < 0:
        kit.motor2.throttle = 0
    if kit.motor3.throttle > x:
        kit.motor3.throttle = x
    elif kit.motor3.throttle < 0:
        kit.motor3.throttle = 0
    if kit.motor4.throttle > x:
        kit.motor4.throttle = x
    elif kit.motor4.throttle < 0:
        kit.motor4.throttle = 0

def checkFront():
    bdistance = 30
    distance = get_front_distance()
    if distance <= bdistance:
        print(f"The front wall is {distance:.2f}cm away oh no")
        kit.motor2.throttle = .45
        kit.motor4.throttle = .45
        kit.motor1.throttle = -.45
        kit.motor3.throttle = -.45



def checkRight():
    gdistance = 20
    distance = get_right_distance()
    print(f"The right wall is {distance:.2f} cm")
    if distance > gdistance:
        front = get_front_distance()
        print(f"Front wall is {front:.2f}cm distance")
        if front <= 15:
            kit.motor2.throttle = .5
            kit.motor4.throttle = .5
            kit.motor1.throttle = -.5
            kit.motor3.throttle = -.5
            print("Boutta faceplant")

        else:
            kit.motor2.throttle = .4
            kit.motor4.throttle = .4
            kit.motor1.throttle = .7
            kit.motor3.throttle = .7
            print("Too f a r")
    elif distance < gdistance:
        #Too CLOSE
        kit.motor2.throttle = 0.7
        kit.motor4.throttle = 0.7
        kit.motor1.throttle = 0.5
        kit.motor3.throttle = 0.5
        print("TOO CLOSE OH MY GOSH")
    else:
        motorLimit(.4)



try:
    while True:

        checkFront()
        checkRight()
        motorLimit(.4)


except KeyboardInterrupt:
    print("STOPPING")
    kit.motor1.throttle = 0
    kit.motor2.throttle = 0
    kit.motor3.throttle = 0
    kit.motor4.throttle = 0
    GPIO.cleanup()
