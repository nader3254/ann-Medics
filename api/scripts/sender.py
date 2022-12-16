import socket
import time
    
TCP_IP = '127.0.0.1'
TCP_PORT = 8082
BUFFER_SIZE = 8084  # Normally 1024, but we want fast response
MESSAGE = "Hello, World!"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
f  = open("./tosend.txt", "r")
tmp = f.read()
f.close()   
if (not(tmp=="no data to send")):
        print("sending msg......")
        s.send(tmp.encode('utf-8'))  # echo
        f2  = open("tosend.txt", "w")
        f2.write("no data to send")
        f2.close()           
s.close()