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
    time.sleep(0.000011)  # add a bit to the trigger signal. SCL
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
    # Looks like motorLimit does not allow for a negative value whereas
    # the checkFront and checkRight defs set negative values.
    if kit.motor1.throttle > x:
        kit.motor1.throttle = x
    elif kit.motor1.throttle < 0: #should this be "-x", not 0? same for other 0's SCL
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
    bdistance = 25
    distance = get_front_distance()
    if distance <= bdistance:
        print(f"The front wall is {distance:.2f}cm away oh no")
        kit.motor2.throttle = .7
        kit.motor4.throttle = .7
        kit.motor1.throttle = -.7
        kit.motor3.throttle = -.7
        motorLimit(.6)  # ?? Set values to [0.6 0.6 0.0 0.0]? SCL
        time.sleep(1.5)  

def checkRight():
    gdistance = 20
    distance = get_right_distance()
    print(f"Distance: {distance:.2f} cm")
    if distance > gdistance:  # is right side distance  too far
        front = get_front_distance() #are we about to run into anything
        print(f"Front wall is {front:.2f}cm distance")
        if front <= 15:  # too close, turn it around
            kit.motor2.throttle = 7
            kit.motor4.throttle = 7
            kit.motor1.throttle = -.7
            kit.motor3.throttle = -.7
            print("Boutta faceplant")
            time.sleep(.5)  # give it a bit to turn around
            motorLimit(.7)  # ??  [0.7 0.7 0 0] ?

        else: #nothing infront of us
            kit.motor2.throttle = .4  # go forward and right.
            kit.motor4.throttle = .4
            kit.motor1.throttle = .7
            kit.motor3.throttle = .7
            print("Too f a r")
            motorLimit(.7)  # [0.4 0.4 0.7 0.7]
    elif distance < gdistance:
        #Too CLOSE
        kit.motor2.throttle = 0.7
        kit.motor4.throttle = 0.7
        kit.motor1.throttle = 0.5
        kit.motor3.throttle = 0.5
        print("TOO CLOSE OH MY GOSH")
    else:
        kit.motor2.throttle = .5
        kit.motor4.throttle = .5
        kit.motor1.throttle = .5
        kit.motor3.throttle = .5



try:
    while True:

        checkFront()
        checkRight()
        # checkFront()  SCL
        # motorLimit(.9)  SCL

except KeyboardInterrupt:
    print("STOPPING")
    kit.motor1.throttle = 0
    kit.motor2.throttle = 0
    kit.motor3.throttle = 0
    kit.motor4.throttle = 0
    GPIO.cleanup()
