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

def valide(F, A):
    #
    # A COMPLETER       
    # 
   return True

################################################################

def aff_suivante(A):
    #
    # A COMPLETER       
    #i = 0
    return A

def test_aff_suivante(n):
    #
    # A COMPLETER       
    #
    return None
        
#########################################################################

def sat_exhau(F, n):
    A = [-1] * n
    #
    # A COMPLETER       
    #
    return A

def elimination(F, n, b):
#    "Formule psi = F(x_1, …, x_{n-1}, b)"
    #
    # A COMPLETER       
    #
    psi=[]
    return psi

def sat_backtrack(F, n):
    #
    # A COMPLETER       
    #
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
#print(valide(F, [1,1,-1]))
#print(valide(F, [-1,-1,1]))
#print("-------------------------------------------------------")
print(test_aff_suivante(4))
print("-------------------------------------------------------")
print(sat_exhau(F, n))
print(sat_backtrack(F, n))

