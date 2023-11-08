def clause(s):
    L = s.split()
    return [int(v) for v in L[:-1]]

def parseur(nom):
    with open(nom) as f:
        F = []
        n = 0
        for ligne in f:
            if ligne[0] == 'c': continue
            if ligne[0] == 'p':
                L = ligne.split()
                n = int(L[-2])
            else: 
                F.append(clause(ligne))
    return F, n

def affiche(F):
    s=''
    for j in range(0,len(F)):
        C=F[j]
        s=s+'('
        for i in range(0,len(C)):
            if C[i]<0:
                s=s+'¬'
            s=s+'x'+str(abs(C[i]))
            if i==len(C)-1:
                s=s+')'
            else:    
                s=s+' ∨ '
        if j!=len(F)-1:
            s=s+' ∧ '
    return s

################################################################
'''
def valide(F, A):
    soluce = []
    for i in range(len(F)):
        for j in range(len(F)):
            if A[j]>0:
                soluce.append(1)
        if len(A)<j:
            soluce.append(0)
            return False
    return True
'''
def valide(F, A):
    soluce = []
    for i in range(len(F)):
        soluce.append(0)
    for i in range(len(F)):
        for j in range(len(F[i])):
            if A[j]>0:
                soluce[j] = 1
                break
        if soluce[j] != 1:
            return False
    return True

################################################################

def aff_suivante(A):
    i = len(A)-1
    while i >=0 and A[i] == 1:
        A[i] = -1
        i-=1
    if i == -1:
        return None
    A[i] = 1
    return A

def test_aff_suivante(n):
    A = []
    for i in range(n):
        A.append(-1)
    for i in range(2**n):
        print(aff_suivante(A))
        
#########################################################################

def sat_exhau(F, n):
    A = [-1] * n
    for i in range(2**n):
        if valide(F,A) == True:
            return A
        else:
            aff_suivante(A)
    return A

def elimination(F, n, b):
#    "Formule psi = F(x_1, …, x_{n-1}, b)"
    psi=[]

    for C in F:
        Cp = []
        sat = False
        for l in C:
            if l == n and l*b >0:
                sat = True
            elif l != n:
                Cp.append(1)
        if not(sat):
            psi.append(Cp)
    return psi

def sat_backtrack(F, n):
    # est dans le cours
    if not F :
        return [1 for i in range(n)]
    if ([] in F):
        return "insatisfiable"
    for b in [1,-1]:
        psi = elimination(F,n,b)
        V = sat_backtrack(F,n-1)
        if V != "insatisfiable":
            return A + b
    return None

###############################################################################

print("-------------------------------------------------------")
Fichier="./cnf/quinn.cnf"
print("Formule du fichier: "+Fichier)
F,n=parseur(Fichier)
print("Récupérée sous forme de tableau: ",F)
print("Nombre de variables: ",n)
print("Formule SAT: ",affiche(F))
print("-------------------------------------------------------")
print(valide(F, [1,1,-1]))
print(valide(F, [-1,-1,1]))
print("-------------------------------------------------------")
print(test_aff_suivante(4))
print("-------------------------------------------------------")
print("taille de n = ",n)
print(sat_exhau(F, n))
print(sat_backtrack(F, n))

