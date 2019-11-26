files = ["5_200","10_200","15_200","20_200","25_200","30_200","30_175","30_166","30_150","30_133","30_100"]

for f in files:
    fil = open('../'+f+'.csv','r')

    while l:
        for i in range(4):
            l = fil.readline()
        mem = l.split(',')[2]
    print(f.split('_')[1], f.split('_')[0], mem, 0)