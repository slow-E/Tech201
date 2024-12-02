# Servo Control
import time
import wiringpi

pwm_pin = 13
maxRight = 480
maxLeft = 110
# use 'GPIO naming'
wiringpi.wiringPiSetupGpio()

# set #18 to be a PWM output
wiringpi.pinMode(pwm_pin, wiringpi.GPIO.PWM_OUTPUT)

# set the PWM mode to milliseconds stype
wiringpi.pwmSetMode(wiringpi.GPIO.PWM_MODE_MS)

# divide down clock
wiringpi.pwmSetClock(270)
wiringpi.pwmSetRange(4000)

delay_period = 0.01

while True:
        for pulse in range(maxLeft, maxRight, 1):
                wiringpi.pwmWrite(pwm_pin, pulse)
                time.sleep(delay_period)
        for pulse in range(maxRight, maxLeft, -1):
                wiringpi.pwmWrite(pwm_pin, pulse)
                time.sleep(delay_period)
