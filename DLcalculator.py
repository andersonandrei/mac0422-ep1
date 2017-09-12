from random import randrange, uniform
import matplotlib.pyplot as plt
#import subprocess as sp
#import sys

qntMcSJF = 0
qntMcRR = 0
qntMcP = 0
for a in range(1,31):
    name = "pc2/trace" +str(2)+ "Out"+str(1)+"L"+str(a)
    file = open(name, 'r')
    fileLines = file.readlines()
    file.close()
    lastLine = fileLines[len(fileLines) -1]
    qntMcSJF += int(lastLine[0])

    name = "pc2/trace" +str(2)+ "Out"+str(2)+"L"+str(a)
    file = open(name, 'r')
    fileLines = file.readlines()
    file.close()
    lastLine = fileLines[len(fileLines) -1]
    qntMcRR += int(lastLine[0])
    
    
    name = "pc2/trace" +str(2)+ "Out"+str(3)+"L"+str(a)
    file = open(name, 'r')
    fileLines = file.readlines()
    file.close()
    lastLine = fileLines[len(fileLines) -1]
    qntMcP += int(lastLine[0])

print(qntMcSJF/30)
print(qntMcRR/30)
print(qntMcP/30)

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
    
