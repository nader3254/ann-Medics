#!/usr/bin/env python
    
import socket
import time    


#
       #send and recieve data throught file for read and file for write
       # if the write file changed  



print ("starting new tcp server script........")
TCP_IP = '127.0.0.1'
TCP_PORT = 8081
BUFFER_SIZE = 1024  # Normally 1024, but we want fast response
print ("server address : ",TCP_IP,TCP_PORT)    
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)
conn, addr = s.accept()
print ('Connection address:', addr)
while 1:

       data = conn.recv(BUFFER_SIZE)
       f2  = open("./tosend.txt", "r")
       tmp = f2.read()
       f2.close()
       if not data: 
              print ("received :", data)
              f = open("./recieved.txt", "w")
              f.write(data.decode('utf-8'))
              f.close()
       if (not(tmp=="no data to send")):
              conn.send(tmp.encode('utf-8'))  # echo
              f2  = open("./tosend.txt", "w")
              f2.write("no data to send")
              f2.close()
            
       
       #time.sleep(0.3)
conn.close()