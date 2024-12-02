
# Code from blog.kevindoran.co/bluetooth-programming-with-python-3
backlog = 1
size = 1024
hostMACAddress = '00:20:04:BD:D1:A0'
port = 1
s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
s.bind((hostMACAddress,port))
s.listen(backlog)
try:
    client, address = s.accept()
    while 1:
        data = client.recv(size)
        if data:
            print(data)
            client.send(data)
except:
    print("Closing socket")
    client.close()
    s.close()

""" end kevindoran code
"""

"""
# From Zuzebox's Blog
bd_addr = "00:20:04:BD:D1:A0"  # HC-06 with Arduino
# bd_addr = "E4:5F:01:5A:3E:E3"  # Raspberry Pi
port = 1
sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((bd_addr, port))
# sock.send ('\x15')
while 1:
    text = input()
    if text == "quit":
        break
    sock.send(bytes(text, 'UTF-8'))
    sock.close()
 """   
