import sys
import numpy as np

d = {}

cons = ["2500", "5000", "7500"]
for inp in sys.argv[1:]:
    infile1 = open("../"+inp+"/labels.txt", 'r')
    for inp2 in cons:
        outfile = open("../"+inp+"/subgraphs/labels"+inp2+".txt", 'w')  
        line = infile1.readline()
        while line:
            try:
                if d[int(line.split()[0])] == 1:
                    outfile.write(line)
            except:
                x = np.random.randint(10000)
                if x < int(inp2):
                    d[int(line.split()[0])] = 1
                    outfile.write(line)
                else:
                    d[int(line.split()[0])] = 0
            line = infile1.readline()
        infile2 = open("../"+inp+"/edges.txt", 'r')
        outfile2 = open("../"+inp+"/subgraphs/edges"+inp2+".txt", 'w')  
        line = infile2.readline()
        while line:
            try:
                if d[int(line.split()[0])] == 1 and d[int(line.split()[1])] == 1:
                    outfile2.write(line)
            except:
                pass
            line = infile2.readline()