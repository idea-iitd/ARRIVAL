ifile = open('../Baselines/GraphRegExp/rare.txt','r')

l = ifile.readline()

while l:
    mem = 0
    time = 0
    if (l[5] == '5'):
        label = 5
    else:
        label= int(l[5:7])
    edge = int(l[-4:])
    for i in range(100):
        for i in range(10):
            l = ifile.readline()
        mem += int(l.split('~')[1].split(' ')[0])
        for i in range(6):
            l = ifile.readline()
        time += int(l.split(' ')[2])
        for i in range(3):
            l = ifile.readline()

    print(edge, label, mem/100, time/1000)
    l = ifile.readline()