import pandas as pd
import matplotlib.pyplot as plt

dataLCR = pd.read_csv('LCROutput.txt', index_col = None, header = None)
dataRare = pd.read_csv('RareOutput.txt', index_col = None, header = None)
dataArr = pd.read_csv('ArrivalOutput.txt', index_col = None, header = None)

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [1,1.33,1.5,1.66,1.75,2]
y1 = [dataLCR[2][10],dataLCR[2][9],dataLCR[2][8],dataLCR[2][7],dataLCR[2][6],dataLCR[2][5]]
y2 = [dataArr[2][0],dataArr[2][1],dataArr[2][2],dataArr[2][3],dataArr[2][4],dataArr[2][5]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.set_xlabel('Percentage of Nodes (%)',fontsize=22)
ax.set_ylabel('Memory Consumption (GB)',fontsize=22)
plt.savefig('figures/fig4a_mem_percent.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [5,10,15,20,25,30]
y1 = [dataLCR[2][0],dataLCR[2][1],dataLCR[2][2],dataLCR[2][3],dataLCR[2][4],dataLCR[2][5]]
y2 = [dataArr[2][10],dataArr[2][9],dataArr[2][8],dataArr[2][7],dataArr[2][6],dataArr[2][5]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.set_xlabel('# of Labels',fontsize=22)
ax.set_ylabel('Memory Consumption (GB)',fontsize=22)
plt.savefig('figures/fig4b_mem_labels.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
plt.yscale = "log"
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [1,1.33,1.5,1.66,1.75,2]
y1 = [dataRare[3][0],dataRare[3][1],dataRare[3][2],dataRare[3][3],dataRare[3][4],dataRare[3][5]]
y2 = [dataArr[3][0],dataArr[3][1],dataArr[3][2],dataArr[3][3],dataArr[3][4],dataArr[3][5]]
y3 = [dataLCR[3][10],dataLCR[3][9],dataLCR[3][8],dataLCR[3][7],dataLCR[3][6],dataLCR[3][5]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.plot(x,y3,marker = 'v',linewidth=4.0,markersize= 12)
ax.set_xlabel('Percentage of Nodes (%)',fontsize=22)
ax.set_ylabel('Querying Time (ms)',fontsize=22)
plt.savefig('figures/fig4c_time_percent.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
plt.yscale = "log"
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [1,1.33,1.5,1.66,1.75,2]
y1 = [dataRare[3][10],dataRare[3][9],dataRare[3][8],dataRare[3][7],dataRare[3][6],dataRare[3][5]]
y2 = [dataArr[3][10],dataArr[3][9],dataArr[3][8],dataArr[3][7],dataArr[3][6],dataArr[3][5]]
y3 = [dataLCR[3][0],dataLCR[3][1],dataLCR[3][2],dataLCR[3][3],dataLCR[3][4],dataLCR[3][5]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.plot(x,y3,marker = 'v',linewidth=4.0,markersize= 12)
ax.set_xlabel('# of Labels',fontsize=22)
ax.set_ylabel('Querying Time (ms)',fontsize=22)
plt.savefig('figures/fig4d_time_labels.eps', format='eps',bbox_inches='tight')

dataType = pd.read_csv('TypeOutput.txt', index_col = None, header = None)

fig = plt.figure()
index = np.arange(3)
colwidth = 0.1
plt.rcParams.update({'font.size': 25})
ax = fig.add_subplot(111)
ax.bar(index-2*colwidth,[dataType[2][0],dataType[2][1],dataType[2][2]],width = colwidth)
ax.bar(index-colwidth,[dataType[2][3],dataType[2][4],dataType[2][5]],width = colwidth)
ax.bar(index,[dataType[2][6],dataType[2][7],dataType[2][8]],width = colwidth)
ax.bar(index+colwidth,[dataType[2][9],dataType[2][10],dataType[2][11]],width = colwidth)
ax.bar(index+2*colwidth,[dataType[2][12],dataType[2][13],dataType[2][14]],width = colwidth)
ax.set_ylabel('Recall')
ax.set_xlabel('Query Type')
ax.set_xticklabels(['',"Type 1", "Type 2", "Type 3"],fontsize= 15)
ax.legend(['Gplus','DBLP','Freebase', 'Twitter', 'Stack'], loc='upper left', fontsize = 12)
plt.savefig('fig5a_recall_type.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
index = np.arange(3)
colwidth = 0.3
plt.rcParams.update({'font.size': 25})
ax = fig.add_subplot(111)
ax.bar(index-colwidth/2,[dataType[3][3],dataType[3][4],dataType[3][5]],width = colwidth)
ax.bar(index+colwidth/2,[dataType[4][3],dataType[4][4],dataType[4][5]],width = colwidth)
ax.set_ylabel('Speedup')
ax.set_xlabel('Query Type')
ax.set_xticklabels(['',"Type 1", "Type 2", "Type 3"],fontsize= 15)
ax.legend(['Positive Queries', 'Negative Queries'], loc='upper left', fontsize = 12)
plt.savefig('fig5b_dblp_type_speedup.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
index = np.arange(3)
colwidth = 0.3
plt.rcParams.update({'font.size': 25})
ax = fig.add_subplot(111)
ax.bar(index-colwidth/2,[dataType[3][6],dataType[3][7],dataType[3][8]],width = colwidth)
ax.bar(index+colwidth/2,[dataType[4][6],dataType[4][7],dataType[4][8]],width = colwidth)
ax.set_ylabel('Speedup')
ax.set_xlabel('Query Type')
ax.set_xticklabels(['',"Type 1", "Type 2", "Type 3"],fontsize= 15)
ax.legend(['Positive Queries', 'Negative Queries'], loc='upper left', fontsize = 12)
plt.savefig('fig5c_freebase_type_speedup.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
index = np.arange(3)
colwidth = 0.3
plt.rcParams.update({'font.size': 25})
ax = fig.add_subplot(111)
ax.bar(index-colwidth/2,[dataType[3][0],dataType[3][1],dataType[3][2]],width = colwidth)
ax.bar(index+colwidth/2,[dataType[4][0],dataType[4][1],dataType[4][2]],width = colwidth)
ax.set_ylabel('Speedup')
ax.set_xlabel('Query Type')
ax.set_xticklabels(['',"Type 1", "Type 2", "Type 3"],fontsize= 15)
ax.legend(['Positive Queries', 'Negative Queries'], loc='upper left', fontsize = 12)
plt.savefig('fig5d_gplus_type_speedup.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
index = np.arange(3)
colwidth = 0.3
plt.rcParams.update({'font.size': 25})
ax = fig.add_subplot(111)
ax.bar(index-colwidth/2,[dataType[3][12],dataType[3][13],dataType[3][14]],width = colwidth)
ax.bar(index+colwidth/2,[dataType[4][12],dataType[4][13],dataType[4][14]],width = colwidth)
ax.set_ylabel('Speedup')
ax.set_xlabel('Query Type')
ax.set_xticklabels(['',"Type 1", "Type 2", "Type 3"],fontsize= 15)
ax.legend(['Positive Queries', 'Negative Queries'], loc='upper left', fontsize = 12)
plt.savefig('fig5e_stack_type_speedup.eps', format='eps',bbox_inches='tight')


dataLS = pd.read_csv('LsizeOutput.txt', index_col = None, header = None)

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [2,4,6,8]
y1 = [dataLS[2][0],dataLS[2][1],dataLS[2][2],dataLS[2][3]]
y2 = [dataLS[2][4],dataLS[2][5],dataLS[2][6],dataLS[2][7]]
y3 = [dataLS[2][8],dataLS[2][9],dataLS[2][10],dataLS[2][11]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.plot(x,y3,marker = 'v',linewidth=4.0,markersize= 12)
ax.set_xlabel('Network Size (in % of total)',fontsize=22)
ax.set_ylabel('Recall',fontsize=22)
ax.legend(['GPlus', 'DBLP', 'Freebase'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig5f_recall_lsize.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [2,4,6,8]
y1 = [dataLS[3][4],dataLS[3][5],dataLS[3][6],dataLS[3][7]]
y2 = [dataLS[4][4],dataLS[4][5],dataLS[4][6],dataLS[4][7]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.set_xlabel('Query Label Set Size',fontsize=22)
ax.set_ylabel('Speedup',fontsize=22)
ax.legend(['Positive Queries', 'Negative Queries'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig5g_dblp_speedup_lsize.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [2,4,6,8]
y1 = [dataLS[3][8],dataLS[3][9],dataLS[3][10],dataLS[3][11]]
y2 = [dataLS[4][8],dataLS[4][9],dataLS[4][10],dataLS[4][11]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.set_xlabel('Query Label Set Size',fontsize=22)
ax.set_ylabel('Speedup',fontsize=22)
ax.legend(['Positive Queries', 'Negative Queries'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig5h_freebase_speedup_lsize.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [2,4,6,8]
y1 = [dataLS[3][0],dataLS[3][1],dataLS[3][2],dataLS[3][3]]
y2 = [dataLS[4][0],dataLS[4][1],dataLS[4][2],dataLS[4][3]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.set_xlabel('Query Label Set Size',fontsize=22)
ax.set_ylabel('Speedup',fontsize=22)
ax.legend(['Positive Queries', 'Negative Queries'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig5i_gplus_speedup_lsize.eps', format='eps',bbox_inches='tight')

dataDB = pd.read_csv('DBOutput.txt', index_col = None, header = None)

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [1,2,3,4,5]
y1 = [dataDB[2][0],dataDB[2][1],dataDB[2][2],dataDB[2][3],dataDB[2][4]]
y2 = [dataDB[2][5],dataDB[2][6],dataDB[2][7],dataDB[2][8],dataDB[2][9]]
y3 = [dataDB[2][10],dataDB[2][11],dataDB[2][12],dataDB[2][13],dataDB[2][14]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.plot(x,y3,marker = 'v',linewidth=4.0,markersize= 12)
ax.set_xlabel('Density Bin',fontsize=22)
ax.set_ylabel('Recall',fontsize=22)
ax.legend(['GPlus', 'DBLP', 'Freebase'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig6a_recall_db.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [1,2,3,4,5]
y1 = [dataDB[3][5],dataDB[3][6],dataDB[3][7],dataDB[3][8],dataDB[3][9]]
y2 = [dataDB[4][5],dataDB[4][6],dataDB[4][7],dataDB[4][8],dataDB[4][9]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.set_xlabel('Density Bin',fontsize=22)
ax.set_ylabel('Speedup',fontsize=22)
ax.legend(['Positive Queries', 'Negative Queries'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig6b_dblp_speedup_db.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [1,2,3,4,5]
y1 = [dataDB[3][10],dataDB[3][11],dataDB[3][12],dataDB[3][13],dataDB[3][14]]
y2 = [dataDB[4][10],dataDB[4][11],dataDB[4][12],dataDB[4][13],dataDB[4][14]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.set_xlabel('Density Bin',fontsize=22)
ax.set_ylabel('Speedup',fontsize=22)
ax.legend(['Positive Queries', 'Negative Queries'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig6c_freebase_speedup_db.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [1,2,3,4,5]
y1 = [dataDB[3][0],dataDB[3][1],dataDB[3][2],dataDB[3][3],dataDB[3][4]]
y2 = [dataDB[4][0],dataDB[4][1],dataDB[4][2],dataDB[4][3],dataDB[4][4]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.set_xlabel('Density Bin',fontsize=22)
ax.set_ylabel('Speedup',fontsize=22)
ax.legend(['Positive Queries', 'Negative Queries'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig6d_gplus_speedup_db.eps', format='eps',bbox_inches='tight')


dataNS = pd.read_csv('NSizeOutput.txt', index_col = None, header = None)

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [25,50,75,100]
y1 = [dataNS[3][4],dataNS[3][5],dataNS[3][6],dataNS[3][7]]
y2 = [dataNS[4][4],dataNS[4][5],dataNS[4][6],dataNS[4][7]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.set_xlabel('Network Size (in \% of total)',fontsize=22)
ax.set_ylabel('Time',fontsize=22)
ax.legend(['Positive Queries', 'Negative Queries'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig6e_dblp_time_nsize.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [25,50,75,100]
y1 = [dataNS[3][8],dataNS[3][9],dataNS[3][10],dataNS[3][11]]
y2 = [dataNS[4][8],dataNS[4][9],dataNS[4][10],dataNS[4][11]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.set_xlabel('Network Size (in \% of total)',fontsize=22)
ax.set_ylabel('Time',fontsize=22)
ax.legend(['Positive Queries', 'Negative Queries'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig6f_freebase_time_nsize.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [25,50,75,100]
y1 = [dataNS[3][0],dataNS[3][1],dataNS[3][2],dataNS[3][3]]
y2 = [dataNS[4][0],dataNS[4][1],dataNS[4][2],dataNS[4][3]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.set_xlabel('Network Size (in \% of total)',fontsize=22)
ax.set_ylabel('Time',fontsize=22)
ax.legend(['Positive Queries', 'Negative Queries'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig6g_gplus_time_nsize.eps', format='eps',bbox_inches='tight')



dataParams = pd.read_csv('paramsOutput.txt', index_col = None, header = None)

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [0.25,0.5,0.75,1,1.25,1.5,1.75]
i = 0
y1 = [dataParams[2][i],dataParams[2][i+1],dataParams[2][i+2],dataParams[2][i+3],dataParams[2][i+4],dataParams[2][i+5],dataParams[2][i+6]]
i+=7
y2 = [dataParams[2][i],dataParams[2][i+1],dataParams[2][i+2],dataParams[2][i+3],dataParams[2][i+4],dataParams[2][i+5],dataParams[2][i+6]]
i+=7
y3 = [dataParams[2][i],dataParams[2][i+1],dataParams[2][i+2],dataParams[2][i+3],dataParams[2][i+4],dataParams[2][i+5],dataParams[2][i+6]]
i+=7
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.plot(x,y3,marker = 'v',linewidth=4.0,markersize= 12)
ax.set_xlabel('K',fontsize=22)
ax.set_ylabel('Recall',fontsize=22)
ax.legend(['DBLP', 'Freebase'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig7e_recall_nw.eps', format='eps',bbox_inches='tight')


fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [0.25,0.5,0.75,1,1.25,1.5,1.75]
y1 = [dataParams[2][i],dataParams[2][i+1],dataParams[2][i+2],dataParams[2][i+3],dataParams[2][i+4],dataParams[2][i+5],dataParams[2][i+6]]
i+=7
y2 = [dataParams[2][i],dataParams[2][i+1],dataParams[2][i+2],dataParams[2][i+3],dataParams[2][i+4],dataParams[2][i+5],dataParams[2][i+6]]
i+=7
y3 = [dataParams[2][i],dataParams[2][i+1],dataParams[2][i+2],dataParams[2][i+3],dataParams[2][i+4],dataParams[2][i+5],dataParams[2][i+6]]
i+=7
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.plot(x,y3,marker = 'v',linewidth=4.0,markersize= 12)
ax.set_xlabel('K',fontsize=22)
ax.set_ylabel('Recall',fontsize=22)
ax.legend(['DBLP', 'Freebase'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig7g_recall_wl.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [0.25,0.5,0.75,1,1.25,1.5,1.75]
i = 0
y1 = [dataParams[3][i],dataParams[3][i+1],dataParams[3][i+2],dataParams[3][i+3],dataParams[3][i+4],dataParams[3][i+5],dataParams[3][i+6]]
y2 = [dataParams[4][i],dataParams[4][i+1],dataParams[4][i+2],dataParams[4][i+3],dataParams[4][i+4],dataParams[4][i+5],dataParams[4][i+6]]
i+=7
y3 = [dataParams[3][i],dataParams[3][i+1],dataParams[3][i+2],dataParams[3][i+3],dataParams[3][i+4],dataParams[3][i+5],dataParams[3][i+6]]
y4 = [dataParams[4][i],dataParams[4][i+1],dataParams[4][i+2],dataParams[4][i+3],dataParams[4][i+4],dataParams[4][i+5],dataParams[4][i+6]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.plot(x,y3,marker = '^',linewidth=4.0,markersize= 12)
ax.plot(x,y4,marker = '#',linewidth=4.0,markersize= 12)
ax.set_xlabel('K',fontsize=22)
ax.set_ylabel('Time (in s)',fontsize=22)
ax.legend(['DBLP Positive', 'DBLP Negative','Freebase Positive', 'Freebase Negative'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig7f_time_nw.eps', format='eps',bbox_inches='tight')

fig = plt.figure()
plt.rcParams.update({'font.size': 15})
ax = fig.add_subplot(111)
x = [0.25,0.5,0.75,1,1.25,1.5,1.75]
i+=7
y1 = [dataParams[3][i],dataParams[3][i+1],dataParams[3][i+2],dataParams[3][i+3],dataParams[3][i+4],dataParams[3][i+5],dataParams[3][i+6]]
y2 = [dataParams[4][i],dataParams[4][i+1],dataParams[4][i+2],dataParams[4][i+3],dataParams[4][i+4],dataParams[4][i+5],dataParams[4][i+6]]
i+=7
y3 = [dataParams[3][i],dataParams[3][i+1],dataParams[3][i+2],dataParams[3][i+3],dataParams[3][i+4],dataParams[3][i+5],dataParams[3][i+6]]
y4 = [dataParams[4][i],dataParams[4][i+1],dataParams[4][i+2],dataParams[4][i+3],dataParams[4][i+4],dataParams[4][i+5],dataParams[4][i+6]]
ax.plot(x,y1,marker = 'x',linewidth=4.0,markersize= 12)
ax.plot(x,y2,marker = 'o',linewidth=4.0,markersize= 12)
ax.plot(x,y3,marker = '^',linewidth=4.0,markersize= 12)
ax.plot(x,y4,marker = '#',linewidth=4.0,markersize= 12)
ax.set_xlabel('K',fontsize=22)
ax.set_ylabel('Time (in s)',fontsize=22)
ax.legend(['DBLP Positive', 'DBLP Negative','Freebase Positive', 'Freebase Negative'], loc='upper left', fontsize = 12)
plt.savefig('figures/fig7h_time_wl.eps', format='eps',bbox_inches='tight')
