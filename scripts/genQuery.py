import sys
import pandas as pd
import numpy as np

def generate(ofile, querySize = -1, queryType = -1, bin_start = 0, bin_end = 20):
    ofile = ofile.head(bin_end).tail(bin_end-bin_start)
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
        j = np.random.choice(bin_end - bin_start, k, replace=False, p=ofile[1]/ofile[1].sum())
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


# This number is only for
for inp in sys.argv[1:]:
    ofile = pd.read_csv('../'+inp+'/labelfrequency.txt',sep = " ", header = None).sort_values(by = 1, ascending = False).reset_index(drop = True)
    input2 = [2,4,6,8]
    input3 = ['mix',2,3,4]
    for inp2 in input2:
        oFile = open('../'+inp+'/queryls'+str(inp2)+'.txt','w')
        for i in range(10000):
            y = np.random.randint(100000)
            x = np.random.randint(100000)
            oFile.write('query ' + str(x) +' ' + str(y) + ' ' + generate(ofile, querySize=inp2)+"\n")
        oFile.close()

    for inp2 in input3:
        oFile = open('../'+inp+'/query'+str(inp2)+'.txt','w')
        if inp2 == 'mix':
            inp2 = -1
        for i in range(10000):
            y = np.random.randint(100000)
            x = np.random.randint(100000)
            oFile.write('query ' + str(x) +' ' + str(y) + ' ' +generate(ofile, queryType=inp2)+"\n")
        oFile.close()

    oFile = open('../'+inp+'/dynquery.txt','w')
    inp2 = -1
    for i in range(10000):
        d = np.random.randint(3)
        if d == 1:
            y = np.random.randint(100000)
            x = np.random.randint(100000)
            oFile.write('query ' + str(x) +' ' + str(y) + ' ' +generate(ofile, queryType=inp2)+"\n")
        elif d == 2:
            y = np.random.randint(100000)
            x = np.random.randint(100000)
            oFile.write('edge ' + str(x) +' ' + str(y) + "\n")
        else:
            y = np.random.choice(len(ofile[1]), 1, p=ofile[1]/ofile[1].sum())[0]
            x = np.random.randint(100000)
            oFile.write('label ' + str(x) +' ' + str(ofile[0][y]) + "\n")