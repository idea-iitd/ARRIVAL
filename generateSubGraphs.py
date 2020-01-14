import sys
import numpy as np
import pandas as pd


def selectNodes():
    try:
        nextQ = list(edges.loc[int(line.split()[0])][1])
        for j in nextQ:
            d[i][j] = kl[i]
            kl[i] += 1
            nodesSelected[i] += 1
            try:
                nnextQ = list(edges.loc[j][1])
                for jko in nnextQ:
                    d[i][jko] = kl[i]
                    kl[i] += 1
                    nodesSelected[i] += 1
            except:
                try:
                    jko = edges.loc[j][1]
                    d[i][jko] = kl[i]
                    kl[i] += 1
                    nodesSelected[i] += 1
                except:
                    pass
    except:
        try:
            j = edges.loc[int(line.split()[0])][1]
            d[i][j] = kl[i]
            kl[i] += 1
            nodesSelected[i] += 1
        except:
            pass
        

cons = ["2500", "5000", "7500"]
ktk = sys.argv[1:]
if ktk[-1] == "twitter":
    ktk = ktk[:-1]
    edges = pd.read_csv("../twitter/edges.txt", delimiter = ' ',index_col = 0, header = None)
    cons = ["100", "133", "150", "166", "175","200"]
    for inp in ["twitter"]:
        n = 0
        print(inp)
        infile1 = open("../"+inp+"/labels.txt", 'r')
        d1 = {}
        d2 = {}
        d3 = {}
        d4 = {}
        d5 = {}
        d_0 = {}

        outfile1 = open("../"+inp+"/subgraphs/labels100.txt", 'w') 
        outfile2 = open("../"+inp+"/subgraphs/labels133.txt", 'w') 
        outfile3 = open("../"+inp+"/subgraphs/labels150.txt", 'w') 
        outfile4 = open("../"+inp+"/subgraphs/labels166.txt", 'w') 
        outfile5 = open("../"+inp+"/subgraphs/labels175.txt", 'w') 
        outfile_0 = open("../"+inp+"/subgraphs/labels200.txt", 'w') 

        d = [d1,d2,d3,d4,d5,d_0]
        outfile = [outfile1, outfile2, outfile3, outfile4, outfile5, outfile_0]
        line = infile1.readline()
        kl = [1,1,1,1,1,1]
        nodesSelected = [0,0,0,0,0,0]
        while line:
            n+=1
            try:
                if d[0][int(line.split()[0])] >= 1:
                    outfile1.write(str(d[0][int(line.split()[0])])+' '+line.split()[1]+'\n')
                if d[1][int(line.split()[0])] >= 1:
                    outfile2.write(str(d[1][int(line.split()[0])])+' '+line.split()[1]+'\n')
                if d[2][int(line.split()[0])] >= 1:
                    outfile3.write(str(d[2][int(line.split()[0])])+' '+line.split()[1]+'\n')
                if d[3][int(line.split()[0])] >= 1:
                    outfile4.write(str(d[3][int(line.split()[0])])+' '+line.split()[1]+'\n')
                if d[4][int(line.split()[0])] >= 1:
                    outfile5.write(str(d[4][int(line.split()[0])])+' '+line.split()[1]+'\n')
                if d[5][int(line.split()[0])] >= 1:
                    outfile_0.write(str(d[5][int(line.split()[0])])+' '+line.split()[1]+'\n')
            except:
                x = np.random.randint(10000) 
                i = -1
                for inp2 in cons:
                    i+=1
                    if nodesSelected[i] > int(inp2)*400:
                        x = 10000
                    if x < int(inp2):
                        d[i][int(line.split()[0])] = kl[i]
                        kl[i]+=1
                        outfile[i].write(str(d[i][int(line.split()[0])])+' '+line.split()[1]+'\n')
                        nodesSelected[i] += 1
                        normalSelected[i] += 1
                        selectNodes()
                    else:
                        d[i][int(line.split()[0])] = 0
            line = infile1.readline()
for inp in ktk:
    for inp2 in cons:
        infile1 = open("../"+inp+"/labels.txt", 'r')
        print(inp2)
        d = {}
        i = 1
        outfile = open("../"+inp+"/subgraphs/labels"+inp2+".txt", 'w')  
        line = infile1.readline()
        while line:
            try:
                if d[int(line.split()[0])] >= 1:
                    outfile.write(line)
            except:
                x = np.random.randint(10000)
                if x < int(inp2):
                    d[int(line.split()[0])] = 1
                    i+=1
                    outfile.write(line)
                else:
                    d[int(line.split()[0])] = 0
            line = infile1.readline()
        infile2 = open("../"+inp+"/edges.txt", 'r')
        outfile2 = open("../"+inp+"/subgraphs/edges"+inp2+".txt", 'w') 
        line = infile2.readline()
        while line:
            try:
                if d[int(line.split()[0])] >= 1 and d[int(line.split()[1])] >= 1:
                    outfile2.write(line)
            except:
                pass
            line = infile2.readline()


