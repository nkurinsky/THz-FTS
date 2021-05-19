import os, sys
sys.path.append('./devices/')

from gentec import *

gentecPort="COM11"
res = Gentec(gentecPort,verbose=False)

print(res.getValues(10))
