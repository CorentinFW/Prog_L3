# Variables
CC = gcc
CFLAGS = -Wall
# Executables à générer
BIN=bin/serveur_MultiThreads

# liste des fichiers sources 
SRCS0=serveur_MultiThreads.c
default: $(BIN)

# Règle principale pour créer l'exécutable
obj/%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

# Règle pour exo1.o
bin/serveur_MultiThreads: $(SRCS0:%.c=obj/%.o)
	$(CC) $(CFLAGS) -o $@ $+ 
# Nettoyage des fichiers objets et exécutables

clean:	
	rm -f $(BIN) obj/*.o *~