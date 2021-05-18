import serial,time

defPort="COM1"

class Gentec:

    def __init__(self,portName=defPort,verbose=True,debug=False):
        try:
            self.port = serial.Serial(portName, baudrate=921600, timeout=0.0)
        except:
            raise(ValueError("Could not open serial port "+portName))
        self.verbose=verbose
        self.debug=debug
        if(verbose):
            self.getInfo()

    def send(self,cmd,sleepTime=0.1):
        if(self.debug):
            print("Sending: ",cmd)
        self.port.write((cmd+"\r\n").encode())
        time.sleep(sleepTime)
        rcv = self.port.readline()

        msg=list()
        while(len(rcv) > 0):
            rStr = rcv.decode()
            if(rStr[0] != '#'):
                msg.append(rStr)
                if(self.verbose):
                    print(rStr,end='')                
            rcv = self.port.readline()
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

        vals=list()
        while(len(vals) < nSamples):
            rcv = self.port.readline()
            vals.append(rcv)
            time.sleep(0.1)            
        
        endErr = self.send("STR0")
        
        return vals

    def getInfo(self):
        print("S/N:",end='')
        print(self.getSerialNum[0])
        print("Allowed Ranges:",end='')
        print(self.getMinRange(),'-',self.getMaxRange())
        print("Current Range:",end='')
        print(self.getRange())
        print("Max Reading:",end='')
        print(self.getMaxReading())
        print("Tau:",self.getTau())
