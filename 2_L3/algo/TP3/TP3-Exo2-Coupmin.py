import matplotlib.pyplot as plt
from random import *
import time

###########################################

def GenereGraph(n,p):
    Contract =[]
    E = []
    for i in range(n):
        Contract.append(i)
    for i in range(n-1):
        for j in range(i+1,n-1):
            if random()<=p:
                E.append([i,j])
    return [E,Contract]


def ContractArete(E,Contract):
    choose = randint(0,len(E)-1)
    p = E[choose]
    E.remove(p)
    print("p = ",p)
    for i in range(len(Contract)):
        if Contract[i] == p[0]:
            Contract[i] = p[1]
    for i in range(len(E)):
        for j in range(len(E[i])):
            if E[i][j] == p[0]:
                E[i][j] = p[1]
    return[E,Contract]

def CoupMin(E,Contract):
    compteur = E
    n = len(Contract)-2
    for i in range(n):
        graph = ContractArete(E,Contract)
        E = graph[0]
        Contract = graph[1]
    return(E,Contract)
#################Test#######################
graph = GenereGraph(6,0.4)
print("graph de base ",graph)
print("une contraction = ",ContractArete(graph[0],graph[1]))
print("la coup minimale de graph = ",CoupMin(graph[0],graph[1]))