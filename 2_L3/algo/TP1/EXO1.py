from random import * 
from matplotlib import pyplot as plt 
from math import *
#1 avec randint randrange
def entiersAleatoires(n,a,b):
    Alea = []
    for i in range(n):
        Alea.append(randint(a,b))
    return Alea

def entiersAleatoires2(n,a,b):
    Alea = []
    for i in range(n):
        Alea.append(randrange(a,b))#exclu b (range)
    return Alea

# L1 = entiersAleatoires(1000,0,100)
# L2 = entiersAleatoires2(1000,0,100)

# plt.hist(L1,bins =100) 
# plt.hist(L2,bins = 100)
# plt.show() 

# L3 = entiersAleatoires(1000,1,10)
# L4 = entiersAleatoires2(1000,1,10)

# plt.hist(L1,bins =100) 
# plt.hist(L2,bins =from math import *
def flottantsAleatoires(n):
    L = []
    for i in range(n):
        L.append(round(random(),2))
    return L

def flottantsAleatoires2(n,a,b):
    L = []
    for i in range(n):
        L.append(round(uniform(a,b),2))
    return L

L5 = flottantsAleatoires(1000)
L6 = flottantsAleatoires2(1000,-3,10)

# plt.plot(L5)
# plt.plot(L6)
# plt.show()

#3 gros disque la 

def pointsDisque(n):
    L = []
    while(n > 0):
        x = uniform(-1,1)
        y = uniform(-1,1)
        if (x**2) + (y**2) <= 1:
            L.append((x,y))
            n = n-1
    return L

def pointsDisque2(n):
    L = []
    while(n>0):
        x = uniform(-1,1)
        y= 10000000
        while(x**2+y**2>1):
            y= uniform(-1,1)
        L.append((x,y))
        n = n-1
    return L

def pointsDisque3(n):
    L=[]
    while(n>0):
        t = uniform(0,2*pi)
        if t != 2*pi:
            r = random()
            x = r*cos(t) 
            y = r*sin(t)
            if (x**2 + y**2 <= 1):
                L.append((x,y))
                n = n-1
    return L


def affichagePoints(L):
    X = [ x for x , y in L ] # on recupere les abscisses ...
    Y = [ y for x , y in L ] # ... et les ordonnees
    plt.scatter(X , Y , s = 1) # taille des points minimale
    plt.axis('square') # meme echelle en abscisse et ordonnee
    plt.show()

# L7 = pointsDisque(10000)
L8 = pointsDisque2(10000)
# L9 = pointsDisque3(10000)
# affichagePoints(L7)
affichagePoints(L8)
# affichagePoints(L9)

#le disque 1 on teste un peu partout, le 2 on ne bougr pas x et enfin le 3 grace au pi on cible directement le centre

#4 getrandbits

def aleatoireModulo(n):
    k = n.bit_length()
    x = getrandbits(k)
    return x%n


def aleatoireRejet(n):
    k = n.bit_length()
    x = getrandbits(k)
    while(x>n):
        x = getrandbits(k)
    return x

L10 = list(aleatoireModulo(100) for i in range(10000))
L11 = list(aleatoireRejet(100) for i in range(10000))
# plt.hist(L10)
# plt.hist(L11)
# plt.show()