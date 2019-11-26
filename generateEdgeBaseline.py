import pandas as pd
import time

cons = ["100", "133", "150", "166", "175", "200"]
freqs =  [5,10,15,20,25,30]

a1 = 'twitter'
a2 = 'labels200'
a3 = 'edges200'

def generate(ofile, querySize = -1, queryType = -1, bin_start = 0, bin_end = 20):
    ofile = ofile.head(bin_end).tail(bin_end-bin_start).reset_index(drop = True)
    if (querySize == -1):
        querySize = (np.random.randint(4)+1)*2
    if (queryType == -1):
        queryType = (np.random.randint(3)+2)
    st = []
    prev = -1
    bin_end = min(bin_end, len(ofile.index))
    
    if (queryType != 2):
        k = 2
    else:
        k = querySize
    for _ in range(querySize):
        j = np.random.choice(bin_end - bin_start, min(k,bin_end - bin_start), replace=False, p=ofile[1]/ofile[1].sum())
        if (queryType == 2):
            for l in j:
                st.append(ofile[0][l])
            break
        if ofile[0][j[0]] == prev:
            prev = ofile[0][j[1]]
        else:
            prev = ofile[0][j[0]]
        st.append(prev)
    st = list(st)
    if (queryType == 2):
        return('('+'U'.join(map(str,st))+')+')
    if (queryType == 4):
        return('(('+')+).(('.join(map(str,st))+')+)')
    if (queryType == 3):
        return('('+'.'.join(map(str,st))+')+')

ls = pd.read_csv('../'+a1+'/subgraphs/'+a2+'.txt', delimiter= ' ', header = None)
ls.index = ls[0]
labels = {}

edgeFile = open('../'+a1+'/subgraphs/'+a3+'.txt', 'r')
lines = edgeFile.readline()
j = 0
while lines:
    j += 1
    if j%1000 == 0:
        print (j, lines)
    try:
        a = list(ls[1][int(lines.split()[0])])
    except:
        a = [ls[1][int(lines.split()[0])]]
    for i in a:
        try:
            labels[i] += 1
        except:
            labels[i] = 1
    lines = edgeFile.readline()
a = pd.DataFrame(labels,index = [0])
a = a.transpose().sort_values(by = 0, ascending = False).head(30)
a.reset_index(inplace =True)
a.rename(columns = {"index": 0, 0:1},inplace = True)
labelfreqs = list(a.index)

for i in cons:
    for inp2 in [30]:
        print((i, inp2))
        oFile = open('../twitter/subgraphs/labels'+i+'_'+str(inp2)+'.txt','w')
        iFile = open('../twitter/subgraphs/labels'+i+'.txt','r')
        line = iFile.readline()
        while line:
            if int(line.split()[1]) in b:
                oFile.write(line)
            line = iFile.readline()
        oFile.close()

for inp in ["200"]:
    for inp2 in freqs:
        print((inp, inp2))
        oFile = open('../twitter/subgraphs/labels'+inp+'_'+str(inp2)+'.txt','w')
        iFile = open('../twitter/subgraphs/labels'+inp+'.txt','r')
        line = iFile.readline()
        while line:
            if int(line.split()[1]) in b[:inp2]:
                oFile.write(line)
            line = iFile.readline()
        oFile.close()

nodes = pd.read_csv("../twitter/subgraphs/labels100.txt", delimiter = ' ', header=None)
for inp in ["100_30", "133_30", "150_30", "166_30","175_30", "200_30", "200_25", "200_20", "200_15", "200_10", "200_5"]:
    input3 = ['mix']
    k = int(inp.split('_')[1])
    b = a.head(k)
    for inp2 in input3:
        oFile = open('../twitter/subgraphs/query'+str(inp)+'.txt','w')
        if inp2 == 'mix':
            inp2 = -1
        for i in range(10000):
            y = nodes[0][np.random.randint(len(nodes.index))]
            x = nodes[0][np.random.randint(len(nodes.index))]
            oFile.write('query ' + str(x) +' ' + str(y) + ' ' +generate(b, queryType=inp2)+"\n")
        oFile.close()

for inp in cons:
    for inp2 in [30]:
        print((inp, inp2))
        labels = pd.read_csv("../twitter/subgraphs/labels"+ inp +".txt", delimiter=" ", header= None,index_col=0)
        ifile = open("../twitter/subgraphs/edges"+inp+".txt", 'r')
        ofile = open("../twitter/subgraphs/label"+str(inp2)+"edges"+inp+".txt", 'w')
        i = ifile.readline()
        while i:
            try:
                q = list(labels.loc[int(i.split()[0])][1])
                for j in q:
                    if j in labelfreqs[:inp2]:
                        ofile.write(i.split()[0]+' '+i.split()[1]+' '+str(int(j))+'\n')
            except:
                try:
                    q = int(labels.loc[int(i.split()[0])][1])
                    if q in labelfreqs[:inp2]:
                        ofile.write(i.split()[0]+' '+i.split()[1]+' '+str(q)+'\n')
                except:
                    pass
            i= ifile.readline()
        ofile.close()  

for inp in ["200"]:
    for inp2 in freqs:
        print((inp, inp2))
        labels = pd.read_csv("../twitter/subgraphs/labels"+ inp +".txt", delimiter=" ", header= None,index_col=0)
        ifile = open("../twitter/subgraphs/edges"+inp+".txt", 'r')
        ofile = open("../twitter/subgraphs/label"+str(inp2)+"edges"+inp+".txt", 'w')
        i = ifile.readline()
        while i:
            try:
                q = list(labels.loc[int(i.split()[0])][1])
                for j in q:
                    if j in labelfreqs[:inp2]:
                        ofile.write(i.split()[0]+' '+i.split()[1]+' '+str(int(j))+'\n')
            except:
                try:
                    q = int(labels.loc[int(i.split()[0])][1])
                    if q in labelfreqs[:inp2]:
                        ofile.write(i.split()[0]+' '+i.split()[1]+' '+str(q)+'\n')
                except:
                    pass
            i= ifile.readline()
        ofile.close()  