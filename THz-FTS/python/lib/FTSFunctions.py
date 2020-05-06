from scipy.signal import periodogram as psd
import numpy as np

dL = 0.1 #micron, step size
fs = 1/dL #micron^-1, inv. step size (multiply by h gives energy resolution)
c_micron_per_second = 3.0e8 * 1e6
Hz_to_THz = 1e-12

#given the input of some array (y) which holds the values of the input signal over the travel length, return the frequency (in THz) and sqrt of the spectrum, to be plotted directly
def psd_frequency(y, windowing='parzen', fs=fs):
    wave_number,spectrum = psd(y,fs=fs, window=windowing) #wavenumber, spectrum
    return (wave_number*c_micron_per_second*Hz_to_THz, np.sqrt(spectrum))
    
def adjust_spectrum(spectrum, adjustment=1e-7):
    adjusted_spectrum = spectrum -adjustment
    for p in range(len(adjusted_spectrum)):
        if adjusted_spectrum[p] < 0:
          adjusted_spectrum[p] = 0
    return adjusted_spectrum

