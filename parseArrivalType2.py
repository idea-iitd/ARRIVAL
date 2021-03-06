import pandas as pd
import sys

ds = sys.argv[1:]
for d in ds:
    for e in [2,3,4]:
        a = pd.read_csv("../"+d+"/query"+str(e)+".log", delimiter = ',')
        b = pd.read_csv("../BBFS/"+d+"q"+str(e)+"BBFS.txt", delimiter = ' ')
        pospos = 0
        posbbfs = 0
        negbbfs = 0
        posrr = 0
        negrr = 0
        negneg = 0
        posneg = 0
        negpos = 0
        
        for i in range(10000):
            if b['Result'][i] == 1:
                if a[' response'][i] == 1:
                    pospos+=1
                    posbbfs += b['Time'][i]
                    posrr += a[' time'][i]
                else:
                    posneg += 1
                    posbbfs += b['Time'][i]
                    posrr += a[' time'][i]
            elif b['Result'][i] == 2:
                if a[' response'][i] == 1:
                    pospos += 1
                    posbbfs += b['Time'][i]
                    posrr += a[' time'][i]
                else:
                    negneg += 1
                    negbbfs += b['Time'][i]
                    negrr += a[' time'][i]
            else:
                if a[' response'][i] == 1:
                    negpos += 1
                    negbbfs += b['Time'][i]
                    negrr += a[' time'][i]
                else:
                    negneg += 1
                    negbbfs += b['Time'][i]
                    negrr += a[' time'][i]
        try:
            print(d,e-1,float(pospos)/(posneg+pospos), posbbfs/posrr, negbbfs/negrr)
        except:
            print(d,e-1,0,0,0)