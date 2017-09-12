from random import randrange, uniform
import matplotlib.pyplot as plt
#import subprocess as sp
#import sys

mcSJF = []
mcRR = []
mcP = []
qntMcSJF = 0
qntMcRR = 0
qntMcP = 0
for a in range(1,31):
    name = "pc1/traceOut"+str(1)+"S"+str(a)
    file = open(name, 'r')
    fileLines = file.readlines()
    file.close()
    lastLine = fileLines[len(fileLines) -1]
    qntMcSJF += float(lastLine[0])
    mcSJF.append(float(lastLine[0]))

    name = "pc1/traceOut"+str(2)+"S"+str(a)
    file = open(name, 'r')
    fileLines = file.readlines()
    file.close()
    lastLine = fileLines[len(fileLines) -1]
    qntMcRR += float(lastLine[0])
    mcRR.append(float(lastLine[0]))
    
    
    name = "pc1/traceOut"+str(3)+"S"+str(a)
    file = open(name, 'r')
    fileLines = file.readlines()
    file.close()
    lastLine = fileLines[len(fileLines) -1]
    qntMcP += float(lastLine[0])
    mcP.append(float(lastLine[0]))

print(qntMcSJF/30)
print(mcSJF)
print(qntMcRR/30)
print(mcRR)
print(qntMcP/30)
print(mcP)

#infoL = [qntMcSJF, qntMcRR, qntMcP]
#plt.bar(infoL, [1,2,3])
#plt.title("Large files - Mudança de contexto")
#plt.show()
    

#    fileExec = open(name, 'r')
#    linha = fileExec.readline()
#    valores = linha.split(' ')
#    sp.run(["./bin/ep1", str(1), name, name+"_output"])
#    #sp.run(["./bin/ep1", str(id), trace_fl, result_fl])
#    fileExec.close()
    
