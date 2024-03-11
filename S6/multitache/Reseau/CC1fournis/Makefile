########################################
#~ définitions
########################################


BIN=bin/acompleter

SRCS1=acompleter.c

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.c
	gcc -Wall -Iinclude -c $< -o $@


bin/acompleter: obj/biblio.o $(SRCS1:%.c=obj/%.o)
	gcc -o $@ $+

clean:
	rm -f $(BIN) *~
