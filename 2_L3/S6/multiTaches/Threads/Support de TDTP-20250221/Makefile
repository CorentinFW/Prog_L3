# Variables
CC = gcc
CFLAGS = -Wall
OBJ = calculC.o exo1.o
EXEC = Exo1
# Executables à générer
BIN=bin/client  bin/serveur bin/exo1

# liste des fichiers sources 
SRCS0=client.c
SRCS1=serveur.c
SRCS2=common.c
SRCS3=exo1.c

OBJFOURNIS1=calculC.o

default: $(BIN)

# Règle principale pour créer l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Règle pour exo1.o
bin/exo1: $(SRCS3:%.c=obj/%.o)
	$(CC) $(CFLAGS) -o $@ $+ $(OBJFOURNIS1)

obj/%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

bin/client: $(SRCS0:%.c=obj/%.o) $(SRCS2:%.c=obj/%.o) 
	$(CC) $(CFLAGS) -o $@ $+

bin/serveur: $(SRCS1:%.c=obj/%.o) $(SRCS2:%.c=obj/%.o) 
	$(CC) $(CFLAGS) -o $@ $+

# Nettoyage des fichiers objets et exécutables
clean:	
	rm -f $(BIN) obj/*.o *~
