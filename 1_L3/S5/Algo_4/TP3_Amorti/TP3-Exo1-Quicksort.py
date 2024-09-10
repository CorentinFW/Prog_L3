import matplotlib.pyplot as plt
from random import *
import time

###########################################

def TableauAuHasard(n):
    TabHasard=[]
    for i in range(n):
        r = randint(1,n*n)
        TabHasard.append(r)
    return TabHasard

def fusion(T1,T2):
    tab = []
    while not(not(T1) or not(T2)):
        if T1[0]> T2[0]:
            tab.append(T2[0])
            T2.pop(0)
        else :
            tab.append(T1[0])
            T1.pop(0)
    if not(T1):
        for j in T2:
            tab.append(j)
    else:
        for m in T1:
            tab.append(m)
    return tab
            

def TriFusion(n,T):
    if n == 1:
        return T
    else:
        return fusion( TriFusion(n//2,T[:len(T)//2]) , TriFusion(n-n//2,T[(len(T)//2):]) )

def TriBulles(n,T):
    for i in range(n-1,0,-1):
        for j in range(0,i):
            if T[j+1]<T[j]:
                T[j+1], T[j] = T[j], T[j+1]
    print(T)
    return T

def Quicksort(n,T):
    #
    #  A COMPLETER
    #
    return None    

#######Programme Principal########
print("COCO")
n = 10
TH = TableauAuHasard(n)
print(TriFusion(n,TH))
print(TriBulles(n,TH))
print("PLUS COCO")
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
    TFT = TriFusion(n, Tfusion)
    print("Apres tri fusion: ",TFT)

    Tquick=T.copy()
    print("Tableau de depart: ",Tquick)
    Quicksort(n, Tquick)
    print("Apres QuickSort",Tquick)
    
else:
    #Valeurs de n choisies    
    abscisses = [n for n in range(1,1000,10)]
    #Temps de calcul
    tps1 = []
    tps2 = []
    tps3 = []
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
    
    #Tracé
    plt.plot(abscisses, tps1, label="Tri bulles")
    plt.plot(abscisses, tps2, label="Tri Fusion")
    plt.plot(abscisses, tps3, label="Quicksort")
    plt.legend(loc="upper left")
    plt.show()
