# Variables
CC = gcc
CFLAGS = -c
OBJ = calculC.o exo1.o
EXEC = Exo1

# Règle principale pour créer l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Règle pour exo1.o
exo1.o: exo1.c
	$(CC) $(CFLAGS) exo1.c

# Règle pour calculC.o (sans le fichier source .c, mais en utilisant .o directement)


# Nettoyage des fichiers objets et exécutables
clean:
	rm -f $(OBJ) $(EXEC)
