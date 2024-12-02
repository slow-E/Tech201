""" This originated as the file copied from
# adafruit tutorial.  SPDX something or other
"""

import board
from math import sqrt
from time import sleep
from adafruit_motorkit import MotorKit

""" Bluetooth Code 
"""
def limit(num, minimum=-1, maximum=1):
  """Limits input 'num' between minimum and maximum values.
  Default minimum value is 1 and maximum value is 255."""
  return max(min(num, maximum), minimum)


mtrScale = .7  # scale power to motors
rot_right = False
rot_left = False

kit = MotorKit(i2c=board.I2C())
sleep(0.1)
while True:
#    inputx = select.select([sys.stdin],[],[],0.1)[0]
  inputx  = input("Command: ")
  if inputx == "8":
      print("received 8")
      x_accel = 1
      y_accel = 0
  elif inputx == "2":
      print("received 2")
      x_accel = -1
      y_accel = 0
  elif inputx == "6":
      print("received 6")
      x_accel = 0
      y_accel = -1
  elif inputx == "4":
      print("received 4")
      x_accel = 0
      y_accel = 1
  elif inputx == "9":
      print("received 9")
      x_accel = 1
      y_accel = -1
  elif inputx == "7":
      print("received 7")
      x_accel = 1
      y_accel = 1
  elif inputx == "1":
      print("received 1")
      x_accel = -1
      y_accel = 1
  elif inputx == "3":
      print("received 3")
      x_accel = -1
      y_accel = -1
  elif inputx == "r":
    rot_right = True
  elif inputx == "l":
    rot_left = True
  elif inputx == "s":
    break
  else:
    x_accel = 0
    y_accel = 0

    
  inputx = "z"
  if rot_right:
    frontRight = -0.7
    frontLeft = -0.7
    backRight = 0.7
    backLeft = 0.7
    rot_right = False
    rot_left = False
    moveTime = 0.2
  elif rot_left:
    frontRight = 0.7
    frontLeft = 0.7
    backRight = -0.7
    backLeft = -0.7
    rot_right = False
    rot_left = False
    moveTime = 0.2
  else:
    frontRight = limit(mtrScale*(-x_accel + y_accel),-1 ,1) # Front Right
    frontLeft = limit(mtrScale*(x_accel - y_accel),-1 ,1) #Front Left
    backRight = limit(mtrScale*(x_accel + y_accel),-1 ,1) # Back Right
    backLeft = limit(mtrScale*(-x_accel - y_accel),-1 ,1) #Back Left
    moveTime = 0.7
  kit.motor1.throttle = frontRight
  kit.motor2.throttle = backRight
  kit.motor3.throttle = frontLeft
  kit.motor4.throttle = backLeft
  print("%.4f " % frontRight, end="")
  print("%.4f " % backRight, end="")
  print("%.4f " % frontLeft, end="")
  print("%.4f " % backLeft)
  sleep(moveTime)
  kit.motor1.throttle = 0
  kit.motor2.throttle = 0
  kit.motor3.throttle = 0
  kit.motor4.throttle = 0
#      print("  ",backRight, end="")
#      print(frontLeft, end="")
#      print(backLeft)
    # Forward: fR bR fL bL + - - +
    # Back   : fR bR fL bL - + + -
    # Right  : fR bR fL bL + + + +
    # Left   : fR bR fL bL - - - -


print("Setting motors to Zero")





