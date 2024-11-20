import matplotlib.pyplot as plt
from random import *
import time

###########################################

def TableauAuHasard(n):
    TabHasard=[]
    for i in range(n):
        TabHasard.append(randint(1,n*n))
    return TabHasard
print(TableauAuHasard(5))


def TriFusion(n,T):
    if len(T)<=1:
        return T
    else:
        one = n//2
        return Fusion(TriFusion(one,T[0:one]),TriFusion(n-one,T[one:n]))

def Fusion(A,B):
    if len(A) == 0:
        return B
    elif len(B) == 0:
        return A
    elif A[0] <= B[0]:
        return [A[0]] + Fusion( A[1:] , B )
    else:
        return [B[0]] + Fusion( A , B[1:] )


T1 = [5,4,9,3,4]
print("Tri fusion par coco : ",TriFusion(5,T1))


def TriBulles(n,T):
    for i in range(len(T),0,-1):
        for j in range(i-1):
            if T[j] > T[j+1]:
                T[j] , T[j+1] = T[j+1] , T[j]
    return T

def Quicksort(n,T):
    if len(T) <= 1:
        return T
    x = randint(0,n-1)
    p = T[x]
    np = 0
    for i in range(n):
        if T[i] == p:
            np+=1
    T0=[]
    T1=[]
    for i in range(n):
        if T[i]< p:
            T0.append(T[i])
        elif T[i]>p:
            T1.append(T[i])
    T0 = Quicksort(len(T0),T0)
    T1 = Quicksort(len(T1),T1)
    return T0 + [p]*np +T1

#######Programme Principal########

choix=int(input("Taper 1 pour un test sur un exemple simple, 2 pour un comparatif TriFusion/TriBulles/Quicksort: "))
if choix==1:
    n=6
    T=TableauAuHasard(n)
    print("Tableau de depart: ",T)

    Tbulles=T.copy()
    TriBulles(n, Tbulles)
    print("Apres tri bulles: ",Tbulles)

    Tfusion=T.copy()
    print("Tableau de depart: ",Tfusion)
    Tfusion2 = TriFusion(n, Tfusion)
    print("Apres tri fusion: ",Tfusion2)

    Tquick=T.copy()
    print("Tableau de depart: ",Tquick)
    resu = Quicksort(n, Tquick)
    print("Apres QuickSort",resu)
    
else:
    #Valeurs de n choisies    
    abscisses = [n for n in range(1,1000,10)]
    #Temps de calcul
    tps1 = []
    tps2 = []
    tps3 = []
    tps4 = []
    for n in range(1,1000,10):
        T=TableauAuHasard(n)
        T1=T.copy()
        t=time.time()
        TriBulles(n, T1)
        tps1.append(time.time()-t)
        T2=T.copy()
        t=time.time()
        TriFusion(n, T2)
        tps2.append(time.time()-t)
        T3=T.copy()
        t=time.time()
        Quicksort(n, T3)
        tps3.append(time.time()-t)
        T4=T.copy()
        t=time.time()
        sorted(T4)
        tps4.append(time.time()-t)
    #Tracé
    plt.plot(abscisses, tps1, label="Tri bulles")
    plt.plot(abscisses, tps2, label="Tri Fusion")
    plt.plot(abscisses, tps3, label="Quicksort")
    plt.plot(abscisses, tps4, label="Sorted")
    plt.legend(loc="upper left")
    plt.show()
