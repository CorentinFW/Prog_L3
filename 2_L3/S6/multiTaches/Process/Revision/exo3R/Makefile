########################################
#~ définitions
########################################

BIN= bin/init  bin/P1 bin/P2 bin/P3 bin/reinit bin/destruct

# liste des fichiers sources
SRCS0=init.c
SRCS1=P1.c
SRCS2=P2.c
SRCS3=P3.c
SRCS4=reinit.c
SRCS5=destruct.c

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.c
	g++ -Wall -Iinclude -c $< -o $@

bin/init: $(SRCS0:%.c=obj/%.o)
	g++ -o $@ $+

bin/reinit: $(SRCS4:%.c=obj/%.o)
	g++ -o $@ $+

bin/destruct: $(SRCS5:%.c=obj/%.o)
	g++ -o $@ $+

bin/P1: $(SRCS1:%.c=obj/%.o)
	g++ -o $@ $+

bin/P2: $(SRCS2:%.c=obj/%.o)
	g++ -o $@ $+

bin/P3: $(SRCS3:%.c=obj/%.o)
	g++ -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~
