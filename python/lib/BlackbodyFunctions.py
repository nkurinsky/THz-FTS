from pylab import *
from scipy import fft
import matplotlib.pyplot as plt
from scipy.signal import periodogram as psd
import numpy as np
from scipy.signal import find_peaks
from math import sqrt, sin
from cmath import pi
from numba import njit

#fixed variables
k_B = 8.617333262145e-5 #eV K^{-1}
h = 4.135667696e-15 #eV * s
c = 299792458 #m / s
eV_to_J = 1.602176565e-19 
Temp = 2000 #K

#modifiable variables
r_rad_small = 0.001 #m -radius of radiator
r_abs = 0.001 #m -radius of absorber
d =  0.1 #m -distance between absorber and radiator ?

#a is lower lim, b is upper lim, n is number of slices
def simpson(g, a, b, n): 
    h=(b-a)/n
    k=0.0
    x=a + h
    for i in arange(1,n/2 + 1):
        k += 4*g(x)
        x += 2*h
    x = a + 2*h
    for i in arange(1,n/2):
        k += 2*g(x)
        x += 2*h
    r = (h/3)*(g(a)+g(b)+k)
    return r

def gamma_0(T, r_rad):  
    area = pi * r_abs**2
    sin_theta = r_rad /np.sqrt(r_rad**2 + d**2)
    return area*sin_theta * (8 * pi * (k_B * T)**2)/(h**3 * c**2)

#function to integrate via Sumpson's rule
#Noah's modifications to be overflow safe
def power_integral(x):
    #if we have a list, convert to numpy array
    if(type(x)==list):
        x = np.array(dtype=np.float128)
        
    #if we have a numpy array, proceed
    if(type(x)== np.ndarray):
        retvals = np.zeros_like(x,dtype=np.float128)
        inds = x < 1e3
        #small values can be directly calculated
        retvals[inds] = x[inds]**3/(np.exp(x[inds])-1.0)
        #in the limit of large x, f(x)~exp(-x)
        retvals[~inds] = np.exp(-x[~inds])
        return retvals
    
    #assume we have a number
    else: 
        if(type(x)!='float128'):
            x=np.float128(x)
        if(x>1e3):
            return np.exp(-x)
        else:
            return x**3/(np.exp(x)-1.0)

#this function returns power, given bounds in terms of energy
def power_func(T, a, b, r_rad):
    start = a/(k_B * T)  #lowerbound
    end = b/(k_B * T) #upperbound
    n = 100 #slices
    return eV_to_J * k_B**2 * T**2 * gamma_0(T, r_rad)*simpson(power_integral,start,end,n)

def power_func_trap(T, a, b, r_rad):
    start = a/(k_B * T)  #lowerbound
    end = b/(k_B * T) #upperbound
    return eV_to_J * k_B**2 * T**2 * gamma_0(T, r_rad)*simpson(power_integral,start,end,2)

def power_intensity(v, slice_size, Temp=2e3):
    E_min = (v-slice_size/2.0)*h #eV 
    E_max = (v+slice_size/2.0)*h #eV 
    #print("e = " , v*h, " & E_min =", E_min," & E_max =", E_max )
    power = power_func(Temp, E_min, E_max, r_rad_small)
    return power

def power_intensity_trap(v, slice_size, Temp=2e3):
    E_min = (v-slice_size/2.0)*h #eV 
    E_max = (v+slice_size/2.0)*h #eV 
    #print("e = " , v*h, " & E_min =", E_min," & E_max =", E_max )
    power = power_func_trap(Temp, E_min, E_max, r_rad_small)
    return power

def blackbodyWeights(freqs,slice_size, Temp=2e3, useTrap=False):
    if(useTrap):
        return np.fromfunction(lambda i : power_intensity_trap(freqs[i],slice_size, Temp=Temp),freqs.shape, dtype=int)
    else:
        return np.fromfunction(lambda i : power_intensity(freqs[i],slice_size, Temp=Temp),freqs.shape, dtype=int)






    
