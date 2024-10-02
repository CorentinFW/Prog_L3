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
#abs() pour valeur absolue
def valide(F, A):
    for c in F:
        ok = False
        for l in c:
            if l*(A[abs(l)-1]) >0:
                ok = True
        if ok == False:
            return False
    return True
################################################################

def aff_suivante(A):
    i = len(A)-1
    while A[i] == 1 and i>=0:
        A[i] = -1
        i = i-1
    if i>= 0:
        A[i] = 1
    else:
        return None
    return A

def test_aff_suivante(n):
    A = []
    for i in range(n):
        A.append(-1)
    for i in range(2**n):
        A = aff_suivante(A)
        print(A)
        
    return None
        
#########################################################################

def sat_exhau(F, n):
    A = [-1] * n
    while A != None:
        if valide(F,A):
            return A
        else:
            A = aff_suivante(A)
    return "N'existe pas "

def elimination(F, n, b):
#    "Formule psi = F(x_1, …, x_{n-1}, b)"
    NF = []
    for i in F:
        SousNewF = []
        for j in i:
            if abs(j) == n:
                if (b == 1 and j >0) or (b== -1 and j< 0):
                    SousNewF = []
                    break
            else:
                SousNewF.append(j)
        if SousNewF != []:
            NF.append(SousNewF)
    return NF



    psi=[]
    return psi

# def sat_backtrack(F, n):
#     A = [1]*n
#     if F == []:
#         return True
#     elif F == [[]]:
#         return False
#     else:
#         ff = elimination(F,n,-1)
#         fv = elimination(F,n,1)
#         return sat_backtrack(ff,n-1) and sat_backtrack(fv,n-1)
#     return None

def sat_backtrack(F, n):
    A = [1]*n
    if F == []:
        return A
    for C in F:
        if not C :
            return False
        for b in [-1,1]: 
            ff = elimination(F,n,b)
            A = sat_backtrack(ff,n-1)
            if ff is not False:
                return A+[b] 
    return False
###############################################################################

print("-------------------------------------------------------")
Fichier="./cnf/quinn.cnf"
print("Formule du fichier: "+Fichier)
F,n=parseur(Fichier)
print("Récupérée sous forme de tableau: ",F)
print("Nombre de variables: ",n)
print("Formule SAT: ",affiche(F))
print("-------------------------------------------------------")
Fichier = "./cnf/simple_v3_c2.cnf"
F2 , n2 = parseur(Fichier)
print("exo valide : ")
print(valide(F2, [1,1,-1]))
print(valide(F2, [-1,-1,1]))
print("-------------------------------------------------------")
print(test_aff_suivante(4))
print("cocococococco-------------------------------------------------------")
print(sat_exhau(F2, n2))
print(sat_backtrack(F2, n2))
