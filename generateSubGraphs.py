import sys
import numpy as np


cons = ["2500", "5000", "7500"]
for inp in sys.argv[1:]:
    print(inp)
    
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
                    outfile.write(line)
            except:
                pass
            line = infile2.readline()

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
    while line:
        n+=1
        if (n % 10000 == 0):
            print(n)
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
                if x < int(inp2):
                    d[i][int(line.split()[0])] = kl[i]
                    kl[i]+=1
                    outfile[i].write(str(d[i][int(line.split()[0])])+' '+line.split()[1]+'\n')
                else:
                    d[i][int(line.split()[0])] = 0
        line = infile1.readline()
    infile2 = open("../"+inp+"/edges.txt", 'r')
    outfile6 = open("../"+inp+"/subgraphs/edges100.txt", 'w')  
    outfile7 = open("../"+inp+"/subgraphs/edges133.txt", 'w') 
    outfile8 = open("../"+inp+"/subgraphs/edges150.txt", 'w') 
    outfile9 = open("../"+inp+"/subgraphs/edges166.txt", 'w') 
    outfile10 = open("../"+inp+"/subgraphs/edges175.txt", 'w') 
    outfile_1 = open("../"+inp+"/subgraphs/edges200.txt", 'w')
    outfile = [outfile6, outfile7, outfile8, outfile9, outfile10, outfile_1]
    line = infile2.readline()
    while line:
        try:
            for i in range(6):
                if d[i][int(line.split()[0])] >= 1 and d[i][int(line.split()[1])] >= 1:
                    outfile[i].write(str(d[i][int(line.split()[0])])+' '+str(d[i][int(line.split()[1])])+'\n')
        except:
            pass
        line = infile2.readline()