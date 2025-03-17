########################################
#~ définitions
########################################

# Executables à générer
YACC = bison
CC = gcc
# liste des fichiers sources 


########################################
#~ regles pour l'executable @echo debut $(LEX)-compil : calc.l
########################################

Bison : sourceBison.y arbin.c
	$(YACC) sourceBison.y
	$(CC) -g -Wall -o Bison arbin.c sourceBison.tab.c 

interlog : interlog.y arbin.c
	$(YACC) interlog.y 
	$(CC) -g -Wall -o Bison arbin.c interlog.tab.c 
