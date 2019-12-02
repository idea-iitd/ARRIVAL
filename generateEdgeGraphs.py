import pandas as pd

cons = ["gplus","dblp"]

for a in cons:
    ofile = open("../"+a+"/subgraphs/edgeLabel.txt",'w')
    ifile = open("../"+a+"/edges.txt",'r')
    labels = pd.read_csv("../"+a+"/labels.txt", delimiter = ' ', header = None, index_col = 0)
    i = ifile.readline()
    while i:
        try:
            q = list(labels.loc[int(i.split()[0])][1])
            for j in q:
                ofile.write(i.split()[0]+' '+i.split()[1]+' '+str(int(j))+'\n')
        except:
            try:
                q = int(labels.loc[int(i.split()[0])][1])
                ofile.write(i.split()[0]+' '+i.split()[1]+' '+str(q)+'\n')
            except:
                pass
        i= ifile.readline()
    ofile.close()  