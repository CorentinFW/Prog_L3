########################################
#~ définitions
########################################

BIN=bin/semInit  bin/supprimeSemc 

# liste des fichiers sources
SRCS0=semInit.c
SRCS1=supprimeSem.c


default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.cc
	gcc -Wall -Iinclude -c $< -o $@

bin/semInit: $(SRCS2:%.c=obj/%.o) $(SRCS0:%.c=obj/%.o)
	gcc -o $@ $+

bin/supprimeSemc: $(SRCS1:%.c=obj/%.o)
	gcc -o $@ $+

bin/suppr: $(SRCS3:%.c=obj/%.o)
	gcc -o $@ $+



clean:
	rm -f $(BIN) obj/*.o *~
