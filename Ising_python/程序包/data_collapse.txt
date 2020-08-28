import matplotlib.pyplot as plt
import numpy as np
from math import sqrt
L1=8
L2=12
L3=16
Tc=2.269
tL_list=[]
T_list=np.loadtxt('T_list.txt')
C_list_8=np.loadtxt('C_list_8.txt')
C_list_12=np.loadtxt('C_list_12.txt')
C_list_16=np.loadtxt('C_list_16.txt')
C_list_new=[]

def generate_xLyL(gamma,mu):
    for t in T_list:
        index=T_list.index(t)
        reduce_T=(t-Tc)/Tc
        x1=reduce_T*L1**(1/mu)
        x2=reduce_T*L2**(1/mu)
        x3=reduce_T*L3**(1/mu)
        if abs(x1)<=0.5:   
            tL_list.append(x1)
            c1=C_list_8[index]
            C_list_new.append(c1*L1**(-gamma/mu))
        if abs(x2)<=0.5:   
            tL_list.append(x2)    
            c2=C_list_12[index]
            C_list_new.append(c2*L2**(-gamma/mu))
        if abs(x3)<=0.5:   
            tL_list.append(x3)
            c3=C_list_16[index]
            C_list_new.append(c3*L3**(-gamma/mu))
    # print(tL_list)
    return tL_list,C_list_new


error_list=[]
exponents=[]
for gamma in np.arange(0,0.5,0.01):
    for mu in np.arange(0.9,1.3,0.01):
        tL_list,C_list_new=generate_xLyL(gamma,mu)
        tL_array=np.array(tL_list)
        C_array=np.array(C_list_new)
        poly=np.polyfit(tL_array,C_array,5)
        length=len(C_list_new)
        error=0
        for x in tL_list:
            indexnew=tL_list.index(x)
            y1=np.polyval(poly,x)
            y=C_list_new[indexnew]
            error += (y-y1)**2/length**2
            exponents.append((gamma,mu))
        error_list.append(error)
index_min=error_list.index(min(error_list))
gamma_mu=exponents[index_min]
# print(min(error_list))
print(gamma_mu)
