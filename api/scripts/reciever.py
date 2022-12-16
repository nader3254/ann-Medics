import socket
import time
    
TCP_IP = '127.0.0.1'
TCP_PORT = 8081
BUFFER_SIZE = 8084  # Normally 1024, but we want fast response
print("the reciever service is running now ......")    

while 1:
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.bind((TCP_IP, TCP_PORT))
        s.listen(1)
        conn, addr = s.accept()
        print ('Connection address:', addr) 
        data = conn.recv(BUFFER_SIZE)
        if not data: break
        else:
            print ("received :", data)
            f = open("./recieved.txt", "w")
            f.write(data.decode('utf-8'))
            f.close()
        print ("received data:", data)     
    except:
        print("An tcp connection occured .....")
       
                
conn.close()