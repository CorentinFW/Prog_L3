import matplotlib.pyplot as plt
from random import *
import time

def GenereGraph(n,p):
    E = []
    contract = []
    for i in range(n):
        contract.append(i)
    for i in range(n-1):
        for j in range(i+1,n-1):
            if random()<=p:
                E.append([i,j])
    return [E,contract]
print(GenereGraph(8,0.3))

def contractArrete(E,C):
    A = E[randint(0,len(E)-1)]
    print("avant remove",E)
    E.remove(A)
    print(E)
    for i in range(len(E)):
        
        for j in range(len(E[i])):
            if E[i][j] == A[0]:
                E[i][j]  = A[1]
    for m in range(len(C)):
        if C[m] == A[0]:
            C[m] = A[1]
    return [E,C]

def CoupMin(E,C):
    for i in range(len(E)-1):
        CA = contractArrete(E,C)
        E = CA[0]
        C = CA[1]
    print(E)
    print(C)
    CM = []
    for m in E[0]:
        CMSE =[]
        for i in range(len(C)):
            if m ==C[i]:
                CMSE.append(i)
        CM.append(CMSE)
    return CMSE



G = GenereGraph(8,0.3)
print("G = ",G)
print("CA = ",contractArrete(G[0],G[1]))
print(CoupMin(G[0],G[1]))  
