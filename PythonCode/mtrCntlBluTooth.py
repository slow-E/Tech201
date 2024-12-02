""" This originated as the file copied from
# adafruit tutorial.  SPDX something or other
"""

import time,os
import board
import socket
import curses
import binascii
import sys
import select


from math import sqrt
from time import sleep
from adafruit_motorkit import MotorKit

""" Bluetooth Code 
"""
def limit(num, minimum=-1, maximum=1):
  """Limits input 'num' between minimum and maximum values.
  Default minimum value is 1 and maximum value is 255."""
  return max(min(num, maximum), minimum)


mtrScale = .75  # scale power to motors
addr = "00:20:04:BD:D1:A0"  # MAC of HC-06
# addr = "E4:5F:01:5A:3E:E3" Rpi
port = 1 # This needs to match HC-06
x_now = 0

s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
s.connect((addr, port))
kit = MotorKit(i2c=board.I2C())
sleep(0.1)
while True:
    #s.sendall(b'X\n')
# Data looks like x y line
#0123456789123456 <-is index reference
#x 00036  y -1010
    inputx = select.select([sys.stdin],[],[],0.1)[0]
    if inputx:
      break
    data_dec = s.recv(16)
    sleep(0.001)
    data = data_dec.decode()
#    sleep(0.01)        
    if data[3:7].isnumeric() & data[13:16].isnumeric():
        no_data = False
        x_data = data[1:7]
        y_data = data[10:16]
        x_accel = float(x_data)/1024 
        y_accel = float(y_data)/1024
#       print(data)

    else:
      no_data = True
#     print("bad Data")
#    x_now = (time.time_ns())
#    print(x_now-x_old)#

    if not no_data:    
      frontRight = limit(mtrScale*(-x_accel + y_accel),-1 ,1) # Front Right
      frontLeft = limit(mtrScale*(x_accel - y_accel),-1 ,1) #Front Left
      backRight = limit(mtrScale*(x_accel + y_accel),-1 ,1) # Back Right
      backLeft = limit(mtrScale*(-x_accel - y_accel),-1 ,1) #Back Left
      kit.motor1.throttle = frontRight
      kit.motor2.throttle = backRight
      kit.motor3.throttle = frontLeft
      kit.motor4.throttle = backLeft
#     print(frontRight," ",backRight," ",frontLeft," ",backLeft)
      print("%.4f " % frontRight, end="")
      print("%.4f " % backRight, end="")
      print("%.4f " % frontLeft, end="")
      print("%.4f " % backLeft)
#      print("  ",backRight, end="")
#      print(frontLeft, end="")
#      print(backLeft)


  #  sleep(0.2)
    # Forward: fR bR fL bL + - - +
    # Back   : fR bR fL bL - + + -
    # Right  : fR bR fL bL + + + +
    # Left   : fR bR fL bL - - - -
        

        
s.close()
    

"""End bluetooth code """

"""  Motor Code
"""
kit.motor1.throttle = 0
kit.motor2.throttle = 0
kit.motor3.throttle = 0
kit.motor4.throttle = 0

print("Setting motors to Zero")





