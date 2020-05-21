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

c_micron_per_second = 3.0e8 * 1e6
mm_to_micron = 1000
Hz_to_THz = 1e-12

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
    
#trap means trapezoidal, will only evaluate the integral at two points. This is faster!
def power_func_trap(T, a, b, r_rad):
    start = a/(k_B * T)  #lowerbound
    end = b/(k_B * T) #upperbound
    return eV_to_J * k_B**2 * T**2 * gamma_0(T, r_rad)*simpson(power_integral,start,end,2)

#returns the output power given the individual slice
def power_intensity(v, slice_size, Temp=2e3):
    E_min = (v-slice_size/2.0)*h #eV
    E_max = (v+slice_size/2.0)*h #eV
    #print("e = " , v*h, " & E_min =", E_min," & E_max =", E_max )
    power = power_func(Temp, E_min, E_max, r_rad_small)
    return power
    
#returns the output power given the individual slice using the trapezoidal, faster integration method
def power_intensity_trap(v, slice_size, Temp=2e3):
    E_min = (v-slice_size/2.0)*h #eV
    E_max = (v+slice_size/2.0)*h #eV
    #print("e = " , v*h, " & E_min =", E_min," & E_max =", E_max )
    power = power_func_trap(Temp, E_min, E_max, r_rad_small)
    return power

#returns the array of blackbody weights for each element in the frequency array (input)
#input freqs which is the numpy array of frequencies, and the slice size between each of these entries
#use of trapezoidal vs not trapezoidal integration methods result in faster/slower results
def blackbodyWeights(freqs,slice_size, Temp=2e3, useTrap=False):
    if(useTrap):
        return np.fromfunction(lambda i : power_intensity_trap(freqs[i],slice_size, Temp=Temp),freqs.shape, dtype=int)
    else:
        return np.fromfunction(lambda i : power_intensity(freqs[i],slice_size, Temp=Temp),freqs.shape, dtype=int)

#return the 'y' output array of signal for the blackbody output, labmda_or_nu is True if the input array is in terms of wavelengths lambda, False if it is in terms of frequencies nu.
#wavlength array should be in terms of micron
#frequnecy array should be in terms of THz
#frequency slice size should be in THz
def blackbody_input_function(lambda_or_nu, freq_or_wave_array, freq_slice_size=0.1, filter='no', dx=-6*mm_to_micron, L=12e3, dL=0.1, sigma=0):
    '''
    Here i need to put in my help string
    '''
    x=np.arange(0,L,dL)
    y_phaseNoise=np.zeros_like(x)
    filter_val=[]
    weights=[]
    k = 0
    
    if filter == 'no':

        for i in range(len(freq_or_wave_array)): #iterate throughout the array
            if lambda_or_nu: #an array of wavelengths in microns
                freq = c_micron_per_second/freq_or_wave_array[i] #converts wavelength in micron to Hz frequency
                weights.append(power_intensity_trap(freq, freq_slice_size/Hz_to_THz)) # for blackbody, this is the blackbody intensity in W
                k = 1/freq_or_wave_array[i]
            else: #False means frequencies
                weights.append(power_intensity_trap(freq_or_wave_array[i]/Hz_to_THz, freq_slice_size/Hz_to_THz))
                k = freq_or_wave_array[i]/(Hz_to_THz*c_micron_per_second) #get wavenumber
            phase = 2.0*pi*dx*k #phase offset depends on wavenumber
            y_phaseNoise += weights[i]*(np.cos(2.0*pi*k*x + phase)+ 1.0)/2
        y = y_phaseNoise + np.random.rand(len(x))*sigma #create the input signal
        return(x, y, weights)
       
    elif filter == 'PEW':
        for i in range(len(freq_or_wave_array)): #iterate throughout the array
            if lambda_or_nu: #True, iterating through an array of wavelengths in microns
                filter_range = [10, 1000] #micron
                if min(filter_range) <= freq_or_wave_array[i] <= max(filter_range):
                    k = 1/freq_or_wave_array[i]
                    freq = c_micron_per_second/freq_or_wave_array[i] #converts wavelength in micron to Hz frequency
                    weights.append(power_intensity_trap(freq, freq_slice_size/Hz_to_THz))# for blackbody, this is the blackbody intensity in W
                    filter_val.append(1)
                else:
                    weights.append(0)
                    filter_val.append(0)
            else:#False, iterating through an array of frequencies in THz
                k = freq_or_wave_array[i]/(Hz_to_THz*c_micron_per_second) #get wavenumber
                filter_range = [0.3, 30] #THz
                if min(filter_range) <= freq_or_wave_array[i] <= max(filter_range): #outside of fiter range, make weight 0
                    weights.append(power_intensity_trap(freq_or_wave_array[i]/Hz_to_THz, freq_slice_size/Hz_to_THz))
                    filter_val.append(1)
                else:
                    weights.append(0)
                    filter_val.append(0)
            phase = 2.0*pi*dx*k #phase offset depends on wavenumber
            y_phaseNoise += weights[i]*0.5*(np.cos(2.0*pi*k*x + phase)+ 1.0)
        y = y_phaseNoise + np.random.rand(len(x))*sigma #create the input signal
        return(x, y, weights, filter_val)
        
    elif filter == 'SiW':
         for i in range(len(freq_or_wave_array)): #iterate throughout the array
             if lambda_or_nu: #True, iterating through an array of wavelengths in microns
                 #There are two different on segments for the SiW filter
                 filter_range_1 = [1.1, 9] #micron
                 filter_range_2 = [50, 1000] #micron
                 if min(filter_range_1) <= freq_or_wave_array[i] <= max(filter_range_1) or min(filter_range_2) <= freq_or_wave_array[i] <= max(filter_range_2):
                     k = 1/freq_or_wave_array[i]
                     freq = c_micron_per_second/freq_or_wave_array[i] #converts wavelength in micron to Hz frequency
                     weights.append(power_intensity_trap(freq, freq_slice_size/Hz_to_THz)) # for blackbody, this is the blackbody intensity in W
                     filter_val.append(1)
                 else:
                    weights.append(0)
                    filter_val.append(0)
             else:#False, iterating through an array of frequencies in THz
                k = freq_or_wave_array[i]/(Hz_to_THz*c_micron_per_second) #get wavenumber
                filter_range_1 = [0.3, 6] #THz
                filter_range_2 = [33.3, 272.5] #THz
                if min(filter_range_1) <= freq_or_wave_array[i] <= max(filter_range_1) or min(filter_range_2) <= freq_or_wave_array[i] <= max(filter_range_2):
                    weights.append(power_intensity_trap(freq_or_wave_array[i]/Hz_to_THz, freq_slice_size/Hz_to_THz))
                    filter_val.append(1)
                else:
                    weights.append(0)
                    filter_val.append(0)
             phase = 2.0*pi*dx*k #phase offset depends on wavenumber
             y_phaseNoise += weights[i]*0.5*(np.cos(2.0*pi*k*x + phase)+ 1.0)
         y = y_phaseNoise + np.random.rand(len(x))*sigma #create the input signal
         return(x, y, weights, filter_val)
   



    
