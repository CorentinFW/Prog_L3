from random import*
#from matplotlib import pyplot as plt 
from math import *
from time import *
#question 1 : 
def eltMajDet(T):
    for i in range(len(T)):
        count = 0
        for j in range(i,len(T)):
            if T[i] == T[j]:
                count+=1
        if count>= len(T)/2:
            return T[i]
    print("y a une erreur dans T , change de tab")

def eltMajProba(T):

    count = {}
    for i in range(len(T)):
        T2 = T
        x = choice(T2)
        if (x in count):
            count[x] =+1 
        else:
            count[x] = 1 
        T2.remove(x)
        if count[x] >= len(T)/2:
            return x
            
def tabAlea(n,a,b,k):
    T = []
    m = randint(a,b)
    for i in range(k):
        T.append(m)
    for i in range(n-k):
        T.append(randint(a,b))
    shuffle(T)
    return T

def tabDeb(n,a,b,k):
    T = []
    m = randint(a,b)
    for i in range(k-1):
        T.append(m)
    for i in range(n-k):
        T.append(randint(a,b))
    shuffle(T)
    print(T)
    T.remove(m)
    T.insert(0,m)
    print(T)
    return T

def tabFin(n,a,b,k):
    T = []
    m = randint(a,b)
    while len(T)<n-k:  
        t1 = randint(a,b)
        if t1 != m: 
            T.append(t1)
    shuffle(T)
    for i in range(k):
        T.append(m)
    return T


T = [1,2,3,4,2,2,2,7,2,8,2]
print(tabFin(11,1,10,6))