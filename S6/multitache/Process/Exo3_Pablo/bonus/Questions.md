Processus Utilisateur

  int idSem = identifiant du tableau de sémaphores;
  while (true){
    selection_ressources(...); // (1) permet de choisir les ressources
                               // via une saisie par exemple
    
    ... // (2) demande de réservation des ressources sélectionnées
    
    travail(...); // faire quelque chose
    
    ... // (3) // libérer les ressources sélectionnées
  }

Fin Utilisateur


# Questions

1. Combien de sémaphores sont nécessaires et quelles sont les valeurs initiales?

   > Il faut X sémaphores, une pour chaque ressource, initialisées à 1 et changées à 0 quand un utilisateur demande la ressource (les autres utilisateurs attendent que l'ensemble des ressources soient à 1 pour les prendre)


2. Quel serait le résultat de la sélection des ressources (étape (1))?

   > Un tableau est rempli avec des entiers correspondants aux différentes ressources demandées


3. Expliquer comment effectuer la réservation des ressources sélectionnées (étape (2)). Il n'est
pas demandé de fournir du code détaillé, mais il est important d'expliquer, par exemple,
comment votre solution utiliserait la fonction int semop(int idSem, struct sembuf *tabOp,
int nbOp) et de décrire les paramètres en entrée.

   > Exécuté de manière atomique (tout ou rien)
   > Blocage si au moins une des ressources demandées n'est pas dispo
   > Ensemble d'opérations P sur un ensemble de ressources
   > semop(idSem, struct sembuf *tabOp, nbRessourcesDemandees)
   > Avec struct sembuf tapOp[] = {{ressourceDemandee1, -1, 0}, ..., {ressourceDemandeeN, -1, 0}}


4. Faire de même pour la libération des ressources (étape (3))

   > Ensemble d'opérations V sur un ensemble de ressources
   > Pas forcément exécuté de manière atomique
   > semop(idSem, struct sembuf *tabOp, nbRessourcesDemandees)
   > Avec struct sembuf tapOp[] = {{ressourceDemandee1, +1, 0}, ..., {ressourceDemandeeN, +1, 0}}

