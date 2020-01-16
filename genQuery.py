import sys
import pandas as pd
import numpy as np

def generate(ofile, querySize = -1, queryType = -1, bin_start = 0, bin_end = 20):
    ofile = ofile.head(bin_end).tail(bin_end-bin_start).reset_index(drop = True)
    if (querySize == -1):
        querySize = (np.random.randint(4)+1)*2
    if (queryType == -1):
        queryType = (np.random.randint(3)+2)
    st = []
    prev = -1
    
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
        return[('('+'U'.join(map(str,st))+')+'),st]
    if (queryType == 4):
        return[('(('+')+).(('.join(map(str,st))+')+)'),st]
    if (queryType == 3):
        return[('('+'.'.join(map(str,st))+')+'),st]



nodes = {"gplus":100000, "dblp":1750696, "freebase":3674915, "twitter":40000000}
# This generates queries for querySize, queryType, querydensitybin
ktk = sys.argv[1:]
if ktk[-1] == "twitter":
    ktk = ktk[:-1]
    inp = 'twitter'
    oFile = open('../twitter/querymix.txt','w')
    oFile2 = open('../twitter/oldquerymix.txt','w')
    ofile = pd.read_csv('../'+inp+'/labelfrequency.txt',sep = " ", header = None).sort_values(by = 1, ascending = False).reset_index(drop = True)
    inp2 = -1
    for i in range(10000):
        inp2 = np.random.randint(3)+2
        qs = (np.random.randint(4)+1)*2
        y = np.random.randint(nodes[inp])
        x = np.random.randint(nodes[inp])
        k = generate(ofile, queryType=inp2, querySize=qs)
        oFile.write('query ' + str(x) +' ' + str(y) + ' ' +k[0]+"\n")
        oFile2.write('query ' + str(x) +' ' + str(y) + ' ' + str(inp2) +" " + str(len(k[1])) +" " +' '.join(map(str,k[1]))+ "\n")

    oFile.close()
for inp in ktk:
    ofile = pd.read_csv('../'+inp+'/labelfrequency.txt',sep = " ", header = None).sort_values(by = 1, ascending = False).reset_index(drop = True)
    input2 = [2,4,6,8]
    input3 = ['mix',2,3,4]
    input4 = [1,2,3,4,5]
    for inp2 in input2:
        oFile = open('../'+inp+'/queryls'+str(inp2)+'.txt','w')
        oFile2 = open('../'+inp+'/oldqueryls'+str(inp2)+'.txt','w')
        for i in range(10000):
            inpx = np.random.randint(3)+2
            y = np.random.randint(nodes[inp])
            x = np.random.randint(nodes[inp])
            k = generate(ofile, queryType = inpx, querySize=inp2)
            oFile.write('query ' + str(x) +' ' + str(y) + ' ' +k[0] +"\n")
            oFile2.write('query ' + str(x) +' ' + str(y) + ' ' + str(inpx) +" " + str(len(k[1])) +" " +' '.join(map(str,k[1]))+ "\n")
        oFile.close()

    for inp2 in input3:
        oFile = open('../'+inp+'/query'+str(inp2)+'.txt','w')
        oFile2 = open('../'+inp+'/oldquery'+str(inp2)+'.txt','w')
        if inp2 == 'mix':
            inpx = -1
        else:
            inpx = 0
        for i in range(10000):
            if inpx == -1:
                inp2 = np.random.randint(3)+2
            qs = (np.random.randint(4)+1)*2
            y = np.random.randint(nodes[inp])
            x = np.random.randint(nodes[inp])
            k = generate(ofile, queryType=inp2, querySize=qs)
            oFile.write('query ' + str(x) +' ' + str(y) + ' ' + k[0] +"\n")
            oFile2.write('query ' + str(x) +' ' + str(y) + ' ' + str(inp2) +" " + str(len(k[1])) +" " +' '.join(map(str,k[1]))+ "\n")
        oFile.close()

    for inp2 in input4:
        oFile = open('../'+inp+'/querydb'+str(inp2)+'.txt','w')
        oFile2 = open('../'+inp+'/oldquerydb'+str(inp2)+'.txt','w')
        for i in range(10000):
            qs = (np.random.randint(4)+1)*2
            inpx = np.random.randint(3)+2
            y = np.random.randint(nodes[inp])
            x = np.random.randint(nodes[inp])
            k = generate(ofile, queryType = inpx, querySize=qs, bin_start=(int(inp2)-1)*5, bin_end=int(inp2)*5)
            oFile.write('query ' + str(x) +' ' + str(y) + ' ' + k[0]+"\n")
            oFile2.write('query ' + str(x) +' ' + str(y) + ' ' + str(inpx) +" " + str(len(k[1])) +" " +' '.join(map(str,k[1]))+ "\n")
        oFile.close()

