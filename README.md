# THz-FTS
Code for simulating/analyzing output from the BREAD THz Fourier Transform Spectrometer. 

## Hardware setup
* The Thorlabs motorized stage actuator is the Z812B model connected to a KDC101 control cube (COM3).
* The Gentec detector is interfaced to a TRAD-USB for serial interface (COM4)
* Please see the Windows Device Manager to check the COM port number on the lab PC.

## Known issues/todo:
* Right now, manual intervention is needed to restart the Thorlabs stage stops responding, such as unplugging/replugging power cable.
* The GUI is used to home the Thorlabs stage and moving it to the initial offset displacement.
* The Gentec detector sometimes fails to send back data and/or the script does not read it out.
In such cases, the error handling in `gentec.py` sets the resulting power to a small negative number. 
* To debug the power range setting - sending this command seems to cause the Gentec detector to fail to send back data and need to restart. 
* Right now the readout rate is about 1 Hz, such that it is slower than the Gentec approx 5 Hz readout. It might be good to have the stage advance at a set velocity and readout the stage position/detector power a little faster. 
* Nice-to-have: add real-time plotting of the interferogram and interface with power spectral density calculation. 
* Nice-to-have: add `argparse` to the main driver script and refactor the Thorlabs stage part into its own class like `gentec.py`.

## Basic instructions
The main driving script for control/readout the stage and readout data is run using
```
python automation/thorlabs-pyserial.py
```
* For now, the stage configuration is hard-coded in this file. 
* The user should open this file to change step size, counts etc.
* The output is a CSV in format `date,motor-count,motor-position,power`. 

The Gentec detector interface class is written in 
```
authomation/devices/gentec.py
```