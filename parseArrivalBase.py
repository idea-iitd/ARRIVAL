fil = open('results.txt','r')
l = fil.readline()
while l:
    f = line
    l = fil.readline()
    l = fil.readline()
    mem = l.split(' ')[2]
    l = fil.readline()
    neg = int(l.split(' ')[1])*float(l.split(' ')[2])
    l = fil.readline()
    pos = int(l.split(' ')[1])*float(l.split(' ')[2])
    l = fil.readline()
    l = fil.readline()
    l = fil.readline()
    print(f.split('_')[0], f.split('_')[1], mem, (neg+pos)/10000)