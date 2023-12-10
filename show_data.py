import numpy as np
import matplotlib.pyplot as plot

ptrhL = open("hL.txt",'r')  
longhL = ptrhL.readlines()  
ptrhL.close()  
ptrhR = open("hR.txt",'r')  
longhR = ptrhR.readlines()  
ptrhR.close()  
ptrYL = open("YL.txt",'r')  
longYL = ptrYL.readlines()  
ptrYL.close()  
ptrYR = open("YR.txt",'r') 
longYR = ptrYR.readlines()  
ptrYR.close() 

hLMini5 = np.zeros(len(longhL))  
hRMini5 = np.zeros(len(longhR))  
YLMini5 = np.zeros(len(longYL))  
YRMini5 = np.zeros(len(longYR))  

for i in range(len(longhL)):
    longhL[i] = longhL[i].strip()
    hLMini5[i] = longhL[i]
for i in range(len(longhR)):
    longhR[i] = longhR[i].strip()
    hRMini5[i] =longhR[i]
for i in range(len(longYL)):
    longYL[i] = longYL[i].strip()
    YLMini5[i] =longYL[i] 
for i in range(len(longYR)):
    longYR[i] = longYR[i].strip()            
    YRMini5[i] =longYR[i]

Namexticks = 5  
firsthL = np.linspace(0,len(longhL),Namexticks)
secondhL = np.linspace(0,len(longhL),Namexticks)

Namexticks = 5  
firsthR = np.linspace(0,len(longhR),Namexticks)
secondhR = np.linspace(0,len(longhR),Namexticks)

Namexticks = 5  
firstYL = np.linspace(0,len(longYL),Namexticks)
secondYL = ["{:.2f}".format(i) for i in np.linspace(0,24000,Namexticks)]  

Namexticks = 5 
firstYR = np.linspace(0,len(longYR),Namexticks)
secondYR = ["{:.2f}".format(i) for i in np.linspace(0,24000,Namexticks)] 

xhL =  np.linspace(0,len(longhL),len(longhL))
xhR =  np.linspace(0,len(longhR),len(longhR))
xYL =  np.linspace(0,len(longYL),len(longYL))
xYR =  np.linspace(0,len(longYR),len(longYR))
#produce hL
fig = plot.figure(figsize=(20,8))    
plot.stem(xhL,hLMini5)
plot.xticks(firsthL,secondhL)
plot.title('impulse Response')
plot.xlabel('time')
plot.ylabel('amplitude (strength)')
plot.grid(True)
plot.show()
fig.figure.savefig("picture1.pdf")

#produce hR

fig = plot.figure(figsize=(20,8))    
plot.stem(xhR,hRMini5)
plot.xticks(firsthR,secondhR)
plot.title('impulse Response')
plot.xlabel('time')
plot.ylabel('amplitude (strength)')
plot.grid(True)
plot.show()
fig.figure.savefig("picture2.pdf")

#produce YL

fig = plot.figure(figsize=(20,8))    
plot.stem(xYL,YLMini5)
plot.xticks(firstYL,secondYL)
plot.title('log spectrum')
plot.xlabel('Frequency(Hertz)')
plot.ylabel('Amplitude(decibel)')
plot.grid(True)
plot.show()
fig.figure.savefig("picture3.pdf")

#produce YR

fig = plot.figure(figsize=(20,8))    
plot.stem(xYR,YRMini5)
plot.xticks(firstYR,secondYR)
plot.title('log spectrum')
plot.xlabel('frequency (Hertz)')
plot.ylabel('amplitude (decibel)')
plot.grid(True)
plot.show()
fig.figure.savefig("picture4.pdf") 




