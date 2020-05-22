from scipy.signal import periodogram as psd
import numpy as np

L=12e3
dL = 0.1 #micron, step size
fs = 1/dL #micron^-1, inv. step size (multiply by h gives energy resolution)
c_micron_per_second = 3.0e8 * 1e6
m_to_micron = 1e-6
Hz_to_THz = 1e-12

#given the input of some array (y) which holds the values of the input signal over the travel length, return the frequency (in THz) and sqrt of the spectrum, to be plotted directly
def psd_frequency(y, windowing='parzen', fs=fs, frequency_slice_size = 0.01):
    wave_number,spectrum = psd(y,fs=fs, scaling = 'spectrum', window=windowing) #wavenumber, spectrum
    spectrum_hz =  spectrum/c_micron_per_second #converts spectrum from being in usints W^2 micron to W^2/hz
    frequency = wave_number*c_micron_per_second
    df = frequency[1]-frequency[0]
    return (frequency*Hz_to_THz, np.sqrt(spectrum_hz*df)/df*1e9*np.sqrt(2) )
    
def adjust_spectrum(spectrum, adjustment=1e-18):
    adjusted_spectrum = spectrum -adjustment
    for p in range(len(adjusted_spectrum)):
        if adjusted_spectrum[p] < 0:
          adjusted_spectrum[p] = 0
    return adjusted_spectrum

def getFreqList_fromPSD(L=L):
    y=np.arange(0,L,dL)
    wave_number, dummy_spectrum = psd(y,fs=fs)
    freq = wave_number*c_micron_per_second*Hz_to_THz
    frequency_slice_size = abs(freq[0]-freq[1]) #slice size in THz, doesnt change throughout the arrange so we can just use the first separation
    #create seprate array to avoid the issue of first entry being 0
    frequencies = np.arange(frequency_slice_size, max(freq), frequency_slice_size) #still in THz (smallest entry is slice size to avoid 0)
    return frequencies, frequency_slice_size

