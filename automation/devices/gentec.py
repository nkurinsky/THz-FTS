import serial,time
import datetime

defPort="COM1"

class Gentec:

    def __init__(self,portName=defPort,verbose=False,debug=False):
        try:
            self.port = serial.Serial(portName, baudrate=921600, timeout=0.0)
        except:
            raise(ValueError("Could not open serial port "+portName))
        self.verbose=verbose
        self.debug=debug
        self.scale=2e-3
        if(verbose):
            self.getInfo()

    def send(self,cmd,sleepTime=0.01):
        if(self.debug):
            print("Sending: ",cmd)
        self.port.write((cmd+"\r\n").encode())
        time.sleep(sleepTime)
        rcv = self.port.readline()

        msg=list()
        while(len(rcv) > 0):
            rStr = rcv.decode()
            if(rStr[0] != '#'):
                msg.append(rStr[:-2])
                if(self.verbose):
                    print(rStr,end='')                
            rcv = self.port.readline()
        return msg

    def formatResponse(myStrs):
        return myStrs[0][:-2]

    def getTau(self):
        return formatResponse(self.send("tau"))

    def setTau(self,val):
        return formatResponse(self.send("tau"+str(val)))

    def getSerialNum(self):
        return formatResponse(self.send("USN"))

    def getMaxReading(self):
        return formatResponse(self.send("MRD"))

    def getMaxRange(self):
        return formatResponse(self.send("MAX"))

    def getMinRange(self):
        return formatResponse(self.send("MIN"))

    def getRange(self):
        return formatResponse(self.send("RNG"))

    def setRange(self,rng):
        return formatResponse(self.send("RNG"+str(int(rng))))

    def setZero(self):
        return formatResponse(self.send("ZRO"))

    def getValues(self,nSamples=1):
        startErr = formatResponse(self.send("STR1"))
        if(startErr == "ERR"):
            print("Error: Couldn't start data stream")
        else:
            if(self.verbose):
                print("Data Streaming Starting, Will Gather",nSamples,"Samples")

        vals=list()
        self.port.reset_input_buffer()
        while(len(vals) < nSamples):
            loopCount=0
            while(self.port.in_waiting < 1):
                time.sleep(0.05) # data is being streamed at 5 Hz, get time accurate to 50ms
                loopCount+=1
                if(loopCount > 10):
                    print("No values being received from device, aborting data collection")
            if(loopCount > 10):
                break
            rcv = self.port.readline()
            rStr = rcv.decode()
            counts = int(rStr[0:4],16)
            freq = 1e6/float(counts)
            pADC = int(rStr[5:9],16)
            power = float(pADC)/3276.0 * self.scale
            vals.append([datetime.datetime.now(),counts,freq,pADC,power])
        
        endErr = formatResponse(self.send("STR0"))
        
        return vals

    def getInfo(self):
        print("S/N:",end='')
        print(self.getSerialNum())
        print("Allowed Ranges:",end='')
        print(self.getMinRange(),'-',self.getMaxRange())
        print("Current Range:",end='')
        print(self.getRange())
        print("Max Reading:",end='')
        print(self.getMaxReading())
        print("Tau:",self.getTau())
