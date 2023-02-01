import max30102
import hrcalc

m = max30102.MAX30102()

hr2 = 0
sp2 = 0

while True:
    red, ir = m.read_sequential()
    print("red value :",red[0],"ir value :",ir[0])
    f = open("rir.txt", "w")
    s=str(red[0])+"###"+str(ir[0])
    f.write(s)
    f.close()
