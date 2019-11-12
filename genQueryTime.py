import sys
import numpy as np

def generate(querySize = -1, queryType = -1):
    st = []
    prev = -1
    
    if (queryType != 2):
        k = 2
    else:
        k = querySize
    for _ in range(querySize):
        j = np.random.choice(8, k, replace=False)
        if (queryType == 2):
            for l in j:
                st.append(l)
            break
        if j[0] == prev:
            prev = j[1]
        else:
            prev = j[0]
        st.append(prev)
    st = list(st)
    if (queryType == 2):
        return('('+'U'.join(map(str,st))+')+')
    if (queryType == 4):
        return('(('+')+).(('.join(map(str,st))+')+)')
    if (queryType == 3):
        return('('+'.'.join(map(str,st))+')+')


for inp in ['dblp']:
    ofile = open('../'+inp+'/querytime.txt','w')
    attrs = ['numSubjects', 'numPapers', 'medianRank', 'numVenues', 'yearActive']
    ranges = [30, 50, 5, 50, 50]
    funs = ['l', 'g', 'e', '&', '|']
    inp2 = -1
    for i in range(10000):
        ofile.write('querytime ')
        y = np.random.randint(1750696)
        x = np.random.randint(1750696)
        ofile.write(str(x) +' ' + str(y)+' ')
        qSize = (np.random.randint(4)+1)*2
        qType = (np.random.randint(3)+2)
        st = generate(querySize=qSize,queryType=qType)
        ofile.write(st+' ')
        l = []
        for i in range(8):
            st = ""
            fun_choice = np.random.randint(3)
            attr_choice = np.random.randint(5)
            st+=funs[fun_choice]
            st+='_'
            st+=attrs[attr_choice]
            st+='_'
            st+=str(np.random.randint(2,ranges[attr_choice]))
            l.append(st)
        f = '_'.join((map(str,l)))
        ofile.write(f+'\n')

