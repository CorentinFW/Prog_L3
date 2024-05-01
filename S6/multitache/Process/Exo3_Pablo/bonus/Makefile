########################################
#~ définitions
########################################

BIN=bin/semInit bin/reservation bin/supprimeSem

# liste des fichiers sources
SRCS0=semInit.c
SRCS1=reservation.c
SRCS3=supprimeSem.c

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.c
	gcc -Wall -Iinclude -c $< -o $@

bin/semInit: $(SRCS2:%.c=obj/%.o) $(SRCS0:%.c=obj/%.o)
	gcc -o $@ $+

bin/reservation: $(SRCS1:%.c=obj/%.o)
	gcc -o $@ $+

bin/supprimeSem: $(SRCS3:%.c=obj/%.o)
	gcc -o $@ $+



clean:
	rm -f $(BIN) obj/*.o *~