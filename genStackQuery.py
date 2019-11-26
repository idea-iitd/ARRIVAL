import pandas as pd
import numpy as np
import random

def generate(ofile, querySize = -1, queryType = -1, bin_start = 0, bin_end = 3):
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
        return('('+'U'.join(map(str,st))+')+')
    if (queryType == 4):
        return('(('+')+).(('.join(map(str,st))+')+)')
    if (queryType == 3):
        return('('+'.'.join(map(str,st))+')+')

ofile = pd.read_csv('../stack/labelfrequency.txt',sep = " ", header = None).sort_values(by = 1, ascending = False).reset_index(drop = True)
inFile = open('../stack/dynamicBase.txt', 'r')
outFile = open('../stack/query.txt', 'w')

start = 1367383847
end = 1457266693

queries = sorted(list(np.random.randint(low=start, high=end, size=10000)))
i = 0

line = inFile.readline()
while line:
    line = inFile.readline()
    intlist = list(map(int,line.split()[1:]))
    try:
        while queries[i] < intlist[3]:
            queryType = random.randint(1,3) + 1
            if queryType == 2:
                querySize = random.randint(1,3)
                labels = generate(ofile, querySize=querySize, queryType=queryType)
            else:
                querySize = random.randint(2,8)
                labels = generate(ofile, querySize=querySize, queryType=queryType)

            x = str(random.randint(1,1000000))
            y = str(random.randint(1,1000000))
            outFile.write('query ' + x + ' ' + y + ' U '+ labels+'\n')
            i+=1
    except:
        pass
    outFile.write(' '.join(line.split()[:-1])+'\n')

inFile.close()
outFile.close()
