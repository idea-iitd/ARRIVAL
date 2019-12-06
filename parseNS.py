nsa = [25,50,75,100]
import pandas as pd

ds = ['gplus','dblp','freebase']
for d in ds:
    for e in nsa:
        a = open("../"+d+"/queryns"+str(e)+".csv",'r')
        l = fil.readline()
        l = fil.readline()
        l = fil.readline()
        l = fil.readline()
        neg = int(l.split(' ')[1])*float(l.split(' ')[2])
        l = fil.readline()
        pos = int(l.split(' ')[1])*float(l.split(' ')[2])
        l = fil.readline()
        l = fil.readline()
        l = fil.readline()
        print(d,e,0,pos,neg)