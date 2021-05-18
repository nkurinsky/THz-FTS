import os, sys
sys.path.append('./devices/')

from gentec import *

gentecPort="COM11"
res = Gentec(gentecPort,verbose=True)

print(res.getValues(10))
