import numpy as np
import pandas as pd
inps=['gplus','dblp']
b = open("runRandom.sh", 'w')
for inp1 in inps:
    a = open("../"+inp1+"/subgraphs/queryedgeLabel.txt",'r')
    rin = pd.read_csv("../"+inp1+"/subgraphs/edgeLabel.txt", delimiter = " ", header = None)
    l = a.readline()
    for i in range(10):
        ofile = open("../"+inp1+"/subgraphs/queryedgeLabel"+str(i)+".txt",'w')
        for j in range(10):
            ofile.write(l)
            l = a.readline()
        ofile.close()

    b.write('echo '+inp1+'>>rare.txt\n')
    for i in range(100):
        start = int(rin[0][np.random.randint(len(rin[0]))])
        end = int(rin[1][np.random.randint(len(rin[1]))])
        regex = np.random.randint(10)
        b.write('java -Xmx40960 Graphregexp -nogui -e ../'+inp1+'/subgraphs/queryedgeLabel.txt -ex '+'../'+inp1+'/subgraphs/queryedgeLabel'+str(regex)+".txt"+' -start '+str(start)+' -end '+str(end)+' -exist >> rare.txt\n')
    