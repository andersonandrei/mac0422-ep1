from random import randrange, uniform
import matplotlib.pyplot as plt
import statistics as stat
import math as th

#import subprocess as sp
#import sys
dlSJF = []
dlRR = []
dlP = []
qntDlSJF = 0
qntDlRR = 0
qntDlP = 0
for a in range(1,31):
    nameTrace = "traces/trace" + "L"+ str(a)
    nameOutput = "pc2/trace" +str(2)+ "Out"+str(1)+"L"+str(a)
    trace = open(nameTrace, 'r')
    traceLines = trace.readlines()
    trace.close()
    output = open(nameOutput, 'r')
    outputLines = output.readlines()
    output.close()
    i = 0
    for linhas in outputLines:
        #tf-tr <= deadline
        if (i < len(outputLines)-1):
            linhas = linhas.split(' ')
            traces = traceLines[i]
            traces = traces.split(' ')
            #print(linhas[2])
            if ((float(linhas[1]) - float(linhas[2])) > float(traces[2])):
                dlSJF.append(1)
                qntDlSJF+=1
            else :
                dlSJF.append(0)
            i+=1


        
        
    nameTrace = "traces/trace" + "L"+ str(a)
    nameOutput = "pc2/trace" +str(2)+ "Out"+str(2)+"L"+str(a)
    trace = open(nameTrace, 'r')
    traceLines = trace.readlines()
    trace.close()
    output = open(nameOutput, 'r')
    outputLines = output.readlines()
    output.close()
    for linhas in outputLines:
        #tf-tr <= deadline
        if (i < len(outputLines)-1):
            linhas = linhas.split(' ')
            traces = traceLines[i]
            traces = traces.split(' ')
            #print(linhas[2])
            if ((float(linhas[1]) - float(linhas[2])) > float(traces[2])):
                dlSJF.append(0)
                qntDlRR+=1
            else :
                dlSJF.append(0)
            i+=1
    
    nameTrace = "traces/trace" + "L"+ str(a)
    nameOutput = "pc2/trace" +str(2)+ "Out"+str(3)+"L"+str(a)
    trace = open(nameTrace, 'r')
    traceLines = trace.readlines()
    trace.close()
    output = open(nameOutput, 'r')
    outputLines = output.readlines()
    output.close()
    for linhas in outputLines:
        #tf-tr <= deadline
        if (i < len(outputLines)-1):
            linhas = linhas.split(' ')
            traces = traceLines[i]
            traces = traces.split(' ')
            #print(linhas[2])
            if ((float(linhas[1]) - float(linhas[2])) > float(traces[2])):
                dlSJF.append(1)
                qntDlP+=1
            else :
                dlSJF.append(0)
            i+=1

print(qntDlSJF/30)
print(dlSJF)
print(qntDlRR/30)
print(dlRR)
print(qntDlP/30)
print(dlP)
    
