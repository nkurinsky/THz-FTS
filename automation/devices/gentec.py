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
        self.scales = {'9':2e-6,'10':2e-5,'11':2e-4,'12':2e-3,'13':2e-2}
        self.cRange = self.getRange()
        self.scale=self.scales[cRange]
        self.minRange = self.getMinRange()
        self.maxRange = self.getMaxRange()
        self.tau = self.getTau()
        
        if(verbose):
            self.getInfo()

    def send(self,cmd,sleepTime=0.05):
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
                    print(rStr[:-2],end='')                
            rcv = self.port.readline()
        if(len(msg) == 1):
            return msg[0]
        else:
            return msg

    def getTau(self):
        return self.send("tau")

    def setTau(self,val):
        return self.send("tau"+str(val))

    def getSerialNum(self):
        return self.send("USN")

    def getMaxReading(self):
        return self.send("MRD")

    def getMaxRange(self):
        return self.send("MAX")

    def getMinRange(self):
        return self.send("MIN")

    def getRange(self):
        return self.send("RNG")

    def setRange(self,rng):
        return self.send("RNG"+str(int(rng)))

    def setZero(self):
        return self.send("ZRO")

    def getValues(self,nSamples=1):
        startErr = self.send("STR1")
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
        
        endErr = self.send("STR0")
        
        return vals

    def getInfo(self):
        print("Allowed Ranges:",self.minRange,'-',self.maxRange)
        print("Current Range:"+str(self.cRange)+"("+str(self.scale)+")")
        print("Tau:",self.tau)
