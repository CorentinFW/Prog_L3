from random import*
from matplotlib import pyplot as plt 
from math import *

#question 1 : 
def entierAléatoire(n,a,b):
    Liste = []
    for i in range(n):
        Liste.append(randint(a,b))
    return Liste

def entierAléatoire2(n,a,b):
    Liste = []
    for i in range(n):
        Liste.append(randrange(a,b))
    return Liste
# print(entierAléatoire2(10,3,45))
# plt.hist ( entierAléatoire2(1000,0,100) , bins =100) 
# plt.hist ( entierAléatoire(1000,0,100) , bins =100) 
# plt.show()
# plt.hist ( entierAléatoire2(1000,0,10) , bins =100) 
# plt.hist ( entierAléatoire(1000,0,10) , bins =100) 
# plt.show()

#question 2 :
def flottantsAleatoires(n):
    liste = []
    for i in range(n):
        liste.append(random())
    return liste

def flottantsAleatoires2(n,a,b):
    liste = []
    for i in range(n):
        liste.append(uniform(a,b))
    return liste
#print(flottantsAleatoires2(10,1,8))

# plt.plot(flottantsAleatoires(1000))
# plt.plot(flottantsAleatoires2(1000,-3,10))
# plt.show()

#Question 3 : 
def pointsDisque(n):
    liste = []
    while len(liste) <= n:
        x = uniform(-1,1)
        y = uniform(-1,1)
        if x**2 + y**2 <=1:
            liste.append([x,y])
    return liste

def pointsDisque2(n):#complexiter n**2 a ameliorer 
    liste = []
    for i in range(n):
        x = uniform(-1,1)
        y = uniform(-1,1)
        while x**2 + y**2 > 1:
            y = uniform(-1,1)
        liste.append([x,y])
    return liste

def pointsDisque3(n):
    liste = []
    for i in range(n):
        theta = uniform(0,2*pi)
        r = random()
        liste.append([r*cos(theta),r*sin(theta)])
    return liste

def affichagePoints(liste):
    X = [x for x,y in liste]
    Y = [y for x,y in liste]
    plt.scatter(X,Y,s = 1)
    plt.axis('square')
    plt.show()


# L = pointsDisque(10000)
# L2 = pointsDisque2(10000)
# L3 = pointsDisque3(10000)
# affichagePoints(L)
# affichagePoints(L2)
# affichagePoints(L3)

#question 4: 

def aleatoireModulo(N):
    k = N.bit_length()
    x = getrandbits(k)
    return x%N

def aleatoireRejet(N):
    x = getrandbits(N.bit_length())
    while x < N :
        x = getrandbits(N.bit_length())
    return x

tab1, tab2 = [], []
for i in range(10000):
    tab1.append(aleatoireModulo(randint(1,100)))
    tab2.append(aleatoireRejet(randint(1,100)))
plt.hist ( tab1, bins =100) 
plt.hist (tab2 , bins =100) 
plt.show()
print(aleatoireRejet(69))

