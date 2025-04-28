########################################
#~ définitions
########################################

BIN=bin/rdv  bin/semI bin/suppr

# liste des fichiers sources
SRCS0=rdv.c
SRCS1=semInit.c
SRCS3=supprimeSem.c

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.c
	g++ -Wall -Iinclude -c $< -o $@

bin/rdv: $(SRCS2:%.c=obj/%.o) $(SRCS0:%.c=obj/%.o)
	g++ -o $@ $+

bin/semI: $(SRCS1:%.c=obj/%.o)
	g++ -o $@ $+

bin/suppr: $(SRCS3:%.c=obj/%.o)
	g++ -o $@ $+



clean:
	rm -f $(BIN) obj/*.o *~
