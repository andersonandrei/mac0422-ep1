from random import randrange, uniform
#import subprocess as sp
#import sys


for a in range(1,31):
    name = "../traces/traceS"+str(a)
    file = open(name, 'w')
    for i in range(0,5):
        t = (uniform(0, 5)) #faixa de inteiro
        dt = (uniform(0, 5)) #faixa de ponto flutuante
        deadline = t+ dt +(uniform(0, 5))
        file.writelines("" + str(t) + " " + str(dt) + " " + str(deadline) + " p" + str(i) + "\n")
    file.close()

    name = "../traces/traceM"+str(a)
    file = open(name, 'w')
    for i in range(0,10):
        t = (uniform(0, 5)) #faixa de inteiro
        dt = (uniform(0, 5)) #faixa de ponto flutuante
        deadline = t+ dt +(uniform(0, 5))
        file.writelines("" + str(t) + " " + str(dt) + " " + str(deadline) + " p" + str(i) + "\n")
    file.close()

    name = "../traces/traceL"+str(a)
    file = open(name, 'w')
    for i in range(0,15):
        t = (uniform(0, 5)) #faixa de inteiro
        dt = (uniform(0, 5)) #faixa de ponto flutuante
        deadline = t+ dt +(uniform(0, 5))
        file.writelines("" + str(t) + " " + str(dt) + " " + str(deadline) + " p" + str(i) + "\n")
    file.close()

#    fileExec = open(name, 'r')
#    linha = fileExec.readline()
#    valores = linha.split(' ')
#    sp.run(["./bin/ep1", str(1), name, name+"_output"])
#    #sp.run(["./bin/ep1", str(id), trace_fl, result_fl])
#    fileExec.close()
    
