from random import * 
from matplotlib import pyplot as plt 
from math import *
from time import *

# 1 
def eltMajDet(L):
    for i in range(len(L)):
        cpt = 0
        for j in range(len(L)):
            if L[j] == L[i]:
                cpt += 1
        if cpt >= len(L)/2:
            return L[i]
    print("erreur")



def eltMajProba(L):
    while(True):
        x = choice(L)
        cpt = 0
        for i in range(len(L)):
            if L[i] == x:
                cpt += 1
        if cpt >= len(L)/2:
            return x



def TabAlea(n,a,b,k):
    L=[]
    m = randint(a,b)
    for i in range(k):
        L.append(m)
    for i in range(n-k):
        if m == a:
            res = randint(a+1,b)
        if m == b :
            res = randint (a,b-1)
        if m>a and m<b:
            res = choice([randint(a,m-1),randint(m+1,b)])
        L.append(res)
    shuffle(L)
    return L

def TabDeb(n,a,b,k):
    L=[]
    m = randint(a,b)
    print("MAj = ", m)
    R = [m]
    for i in range(k-1):
        L.append(m)
    for i in range(n-k):
        if m == a:
            res = randint(a+1,b)
        if m == b :
            res = randint (a,b-1)
        if m>a and m<b:
            res = choice([randint(a,m-1),randint(m+1,b)])
        L.append(res)
    shuffle(L)
    for i in L:
        R.append(i)
    return R

def TabFin(n,a,b,k):
    L=[]
    m = randint(a,b)
    
    for i in range(n-k):
        if m == a:
            res = randint(a+1,b)
        if m == b :
            res = randint (a,b-1)
        if m>a and m<b:
            res = choice([randint(a,m-1),randint(m+1,b)])
        L.append(res)
    for i in range(k):
        L.append(m)
    return L

#phase de test de temps
n = randint(1000,10000)
a = randint(1,10)
b= randint(11,20)
k= randint(n//2,n-1)
#test 1 
debut=time()
eltMajDet(TabAlea(n,a,b,k))
print(time()-debut)
debut=time()
eltMajProba(TabAlea(n,a,b,k))
print(time()-debut)
#test 2
debut=time()
eltMajDet(TabDeb(n,a,b,k))
print(time()-debut)
debut=time()
eltMajProba(TabDeb(n,a,b,k))
print(time()-debut)
#test 3 
debut=time()
eltMajDet(TabFin(n,a,b,k))
print(time()-debut)
debut=time()
eltMajProba(TabFin(n,a,b,k))
print(time()-debut)

#Fin de la phase de test 

#2 

def contientEltMajMTirage(T, m):
    L = []
    for i in range(m):
        L.append(choice(T))
    for i in L:
        cpt = 0
        for j in T:
            if j == i:
                cpt += 1
        if cpt>= len(T):
            return i
print(contientEltMajMTirage([1,2,3,4,5,8,5,5,5,5,5,5,5,5,5],5))

