import pandas as pd
import numpy as np
import random

start = 1367383847
end = 1457273425


def generate(ofile, querySize = -1, queryType = -1, bin_start = 0, bin_end = 3):
    ofile = ofile.head(bin_end).tail(bin_end-bin_start).reset_index(drop = True)
    if (querySize == -1):
        querySize = (np.random.randint(3))
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

ofile = pd.read_csv('../stack/labelfrequency.txt',sep = " ", header = None).sort_values(by = 1, ascending = False).reset_index(drop = True)
    
queries = sorted(list(np.random.randint(low=start, high=end, size=10000)))
for jk in [2,3,4]:
    i = 0
    inFile = open('../stack/dynamicBase.txt', 'r')
    outFile = open('../stack/oldquery'+str(jk)+'.txt', 'w')
    outFile2 = open('../stack/query'+str(jk)+'.txt', 'w')
    line = inFile.readline()
    line = inFile.readline()
    while line:
        if i == 1000 :
            break
        intlist = map(int,line.split()[1:])
        while i<1000 and queries[i] < intlist[3]:
            queryType = jk
            querySize = random.randint(1, 3)
            a = generate(ofile, querySize=querySize,queryType=queryType)
            labels = ' '.join(map(str,a[1]))
            x = str(random.randint(1,1000000))
            y = str(random.randint(1,1000000))
            outFile.write('eQuery ' + x + ' ' + y + ' ' + str(queryType) + ' ' + str(querySize)+ ' ' + labels+'\n')
            outFile2.write('query ' + x + ' ' + y + ' U ' + a[0]+'\n')
            i+=1
        outFile.write(' '.join(line.split()[:-1])+'\n')
        outFile2.write(' '.join(line.split()[:-1])+'\n')
        line = inFile.readline()

    inFile.close()
    outFile.close()
