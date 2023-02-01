import max30102
import hrcalc

m = max30102.MAX30102()

hr2 = 0
sp2 = 0

while True:
    red, ir = m.read_sequential()
 #   HR_Sum=0 
 #   HR_SumAvg=len(red)
  #  HR_AVG=0
   # print("red size : ",len(red))
  #  print("ir size : ",len(ir))
  #  for i in range(len(red)):
  #      if (red[i]>5000):
  #        #print("red value :",red[i],"ir value :",ir[i])
  #        HR_Sum += red[i]

   ## HR_AVG= HR_Sum / HR_SumAvg
   # if (HR_AVG <255 and HR_AVG > 20):
    #    print("Heart Rate  : ", HR_AVG)










          #print("ir value :",ir[i])
    hr,hrb,sp,spb = hrcalc.calc_hr_and_spo2(ir, red)

#    print("hr detected:",hrb)
#    print("sp detected:",spb)
   # print("frfo buffer :",m.read_fifo)
    if(hrb == True and spb == True):
        if(hrb == True and hr != -999):
            hr2 = int(hr)
            print("Heart Rate : ",hr2)
        if(spb == True and sp != -999):
            sp2 = int(sp)
            print("SPO2       : ",sp2)
