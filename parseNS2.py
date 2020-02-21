import pandas as pd
import sys

ds = sys.argv[1:]
nsa = [25,50,75,100]
for d in ds:
    for e in nsa:
        fil = open("../"+d+"/queryns"+str(e)+".csv",'r')
        l = fil.readline()
        l = fil.readline()
        l = fil.readline()
        neg = float(l.split(', ')[2])
        l = fil.readline()
        pos = float(l.split(', ')[2])
        print(d,e,0,pos,neg)