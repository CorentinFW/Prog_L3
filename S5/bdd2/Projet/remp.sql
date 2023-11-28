-- Insert 1
INSERT INTO RESTAURANT (IdResto, Adresse, CodePostal, Chaine)
VALUES (1, '123 Rue de la Paix', 75001, 'FastFoodCorp');

-- Insert 2
INSERT INTO RESTAURANT (IdResto, Adresse, CodePostal, Chaine)
VALUES (2, '456 Avenue des Gourmets', 75002, 'FineDiningCo');

-- Insert 3
INSERT INTO RESTAURANT (IdResto, Adresse, CodePostal, Chaine)
VALUES (3, '789 Boulevard Savoureux', 75003, 'CuisineExpress');

-- Insert 4
INSERT INTO RESTAURANT (IdResto, Adresse, CodePostal, Chaine)
VALUES (4, '101 Rue de la Gastronomie', 75004, 'TasteDelight');

-- Insert 5
INSERT INTO RESTAURANT (IdResto, Adresse, CodePostal, Chaine)
VALUES (5, '202 Avenue Culinaire', 75005, 'FlavorFusion');

-- Insert 6
INSERT INTO RESTAURANT (IdResto, Adresse, CodePostal, Chaine)
VALUES (6, '303 Rue Exquise', 75006, 'GourmetElegance');

-- Insert 7
INSERT INTO RESTAURANT (IdResto, Adresse, CodePostal, Chaine)
VALUES (7, '404 Boulevard Délicieux', 75007, 'SavoryBites');

-- Insert 8
INSERT INTO RESTAURANT (IdResto, Adresse, CodePostal, Chaine)
VALUES (8, '505 Avenue Epicurienne', 75008, 'EpicureDine');

-- Insert 9
INSERT INTO RESTAURANT (IdResto, Adresse, CodePostal, Chaine)
VALUES (9, '606 Rue Tasty', 75009, 'TastyFare');

-- Insert 10
INSERT INTO RESTAURANT (IdResto, Adresse, CodePostal, Chaine)
VALUES (10, '707 Boulevard Delicacy', 75010, 'DelightfulCuisine');

--

-- Insert 1
INSERT INTO PERSONNE (IdPersonne, Nom, Prenom)
VALUES (1, 'Dupont', 'Jean');

-- Insert 2
INSERT INTO PERSONNE (IdPersonne, Nom, Prenom)
VALUES (2, 'Martin', 'Sophie');

-- Insert 3
INSERT INTO PERSONNE (IdPersonne, Nom, Prenom)
VALUES (3, 'Lefevre', 'Pierre');

-- Insert 4
INSERT INTO PERSONNE (IdPersonne, Nom, Prenom)
VALUES (4, 'Dubois', 'Marie');

-- Insert 5
INSERT INTO PERSONNE (IdPersonne, Nom, Prenom)
VALUES (5, 'Leroy', 'Michel');

-- Insert 6
INSERT INTO PERSONNE (IdPersonne, Nom, Prenom)
VALUES (6, 'Moreau', 'Isabelle');

-- Insert 7
INSERT INTO PERSONNE (IdPersonne, Nom, Prenom)
VALUES (7, 'Roux', 'Paul');

-- Insert 8
INSERT INTO PERSONNE (IdPersonne, Nom, Prenom)
VALUES (8, 'Girard', 'Catherine');

-- Insert 9
INSERT INTO PERSONNE (IdPersonne, Nom, Prenom)
VALUES (9, 'Fournier', 'François');

-- Insert 10
INSERT INTO PERSONNE (IdPersonne, Nom, Prenom)
VALUES (10, 'Lopez', 'Caroline');


--

-- Insert 1
INSERT INTO CLIENT (IdClient, Telephone)
VALUES (1, '123-456-7890');

-- Insert 2
INSERT INTO CLIENT (IdClient, Telephone)
VALUES (2, '987-654-3210');

-- Insert 3
INSERT INTO CLIENT (IdClient, Telephone)
VALUES (3, '555-123-4567');

-- Insert 4
INSERT INTO CLIENT (IdClient, Telephone)
VALUES (4, '444-789-0123');

-- Insert 5
INSERT INTO CLIENT (IdClient, Telephone)
VALUES (5, '777-555-1234');

-- Insert 6
INSERT INTO CLIENT (IdClient, Telephone)
VALUES (6, '888-222-3333');

-- Insert 7
INSERT INTO CLIENT (IdClient, Telephone)
VALUES (7, '111-333-5555');

-- Insert 8
INSERT INTO CLIENT (IdClient, Telephone)
VALUES (8, '666-999-0000');

-- Insert 9
INSERT INTO CLIENT (IdClient, Telephone)
VALUES (9, '222-444-6666');

-- Insert 10
INSERT INTO CLIENT (IdClient, Telephone)
VALUES (10, '333-111-7777');

--

-- Insert 1
INSERT INTO EMPLOYE (IdEmploye, RoleEmploye, IdResto)
VALUES (1, 'MANAGER', 1);

-- Insert 2
INSERT INTO EMPLOYE (IdEmploye, RoleEmploye, IdResto)
VALUES (2, 'SERVEUR', 2);

-- Insert 3
INSERT INTO EMPLOYE (IdEmploye, RoleEmploye, IdResto)
VALUES (3, 'PREPARATEUR', 3);

-- Insert 4
INSERT INTO EMPLOYE (IdEmploye, RoleEmploye, IdResto)
VALUES (4, 'CUISINIER', 4);

-- Insert 5
INSERT INTO EMPLOYE (IdEmploye, RoleEmploye, IdResto)
VALUES (5, 'DRIVE', 5);

-- Insert 6
INSERT INTO EMPLOYE (IdEmploye, RoleEmploye, IdResto)
VALUES (6, 'SERVEUR', 6);

-- Insert 7
INSERT INTO EMPLOYE (IdEmploye, RoleEmploye, IdResto)
VALUES (7, 'PREPARATEUR', 7);

-- Insert 8
INSERT INTO EMPLOYE (IdEmploye, RoleEmploye, IdResto)
VALUES (8, 'CUISINIER', 8);

-- Insert 9
INSERT INTO EMPLOYE (IdEmploye, RoleEmploye, IdResto)
VALUES (9, 'MANAGER', 9);

-- Insert 10
INSERT INTO EMPLOYE (IdEmploye, RoleEmploye, IdResto)
VALUES (10, 'DRIVE', 10);

--

-- Insert 1
INSERT INTO COMMANDE (IdCommande, TypePaiement, PrixTotal, TypeCommande, IdResto, DateCommande, IdClient)
VALUES (1, 'CARTE', 50, 'PRESENTIEL', 1, '2023-01-15', 1);

-- Insert 2
INSERT INTO COMMANDE (IdCommande, TypePaiement, PrixTotal, TypeCommande, IdResto, DateCommande, IdClient)
VALUES (2, 'LIQUIDE', 75, 'DRIVE', 2, '2023-02-20', 2);

-- Insert 3
INSERT INTO COMMANDE (IdCommande, TypePaiement, PrixTotal, TypeCommande, IdResto, DateCommande, IdClient)
VALUES (3, 'CARTE', 30, 'LIVRAISON', 3, '2023-03-10', 3);

-- Insert 4
INSERT INTO COMMANDE (IdCommande, TypePaiement, PrixTotal, TypeCommande, IdResto, DateCommande, IdClient)
VALUES (4, 'CHECK', 40, 'INTERNET', 4, '2023-04-05', 4);

-- Insert 5
INSERT INTO COMMANDE (IdCommande, TypePaiement, PrixTotal, TypeCommande, IdResto, DateCommande, IdClient)
VALUES (5, 'CARTE', 60, 'PRESENTIEL', 5, '2023-05-12', 5);

-- Insert 6
INSERT INTO COMMANDE (IdCommande, TypePaiement, PrixTotal, TypeCommande, IdResto, DateCommande, IdClient)
VALUES (6, 'LIQUIDE', 25, 'DRIVE', 6, '2023-06-18', 6);

-- Insert 7
INSERT INTO COMMANDE (IdCommande, TypePaiement, PrixTotal, TypeCommande, IdResto, DateCommande, IdClient)
VALUES (7, 'CARTE', 35, 'LIVRAISON', 7, '2023-07-22', 7);

-- Insert 8
INSERT INTO COMMANDE (IdCommande, TypePaiement, PrixTotal, TypeCommande, IdResto, DateCommande, IdClient)
VALUES (8, 'CHECK', 55, 'INTERNET', 8, '2023-08-30', 8);

-- Insert 9
INSERT INTO COMMANDE (IdCommande, TypePaiement, PrixTotal, TypeCommande, IdResto, DateCommande, IdClient)
VALUES (9, 'CARTE', 70, 'PRESENTIEL', 9, '2023-09-10', 9);

-- Insert 10
INSERT INTO COMMANDE (IdCommande, TypePaiement, PrixTotal, TypeCommande, IdResto, DateCommande, IdClient)
VALUES (10, 'LIQUIDE', 45, 'DRIVE', 10, '2023-10-05', 10);

--

-- Insert 1
INSERT INTO MENU (IdMenu, Nom, Prix)
VALUES (1, 'Menu Classique', 20);

-- Insert 2
INSERT INTO MENU (IdMenu, Nom, Prix)
VALUES (2, 'Menu Gourmet', 30);

-- Insert 3
INSERT INTO MENU (IdMenu, Nom, Prix)
VALUES (3, 'Menu Végétarien', 25);

-- Insert 4
INSERT INTO MENU (IdMenu, Nom, Prix)
VALUES (4, 'Menu Enfant', 15);

-- Insert 5
INSERT INTO MENU (IdMenu, Nom, Prix)
VALUES (5, 'Menu Spécial', 35);

-- Insert 6
INSERT INTO MENU (IdMenu, Nom, Prix)
VALUES (6, 'Menu Santé', 28);

-- Insert 7
INSERT INTO MENU (IdMenu, Nom, Prix)
VALUES (7, 'Menu Exotique', 32);

-- Insert 8
INSERT INTO MENU (IdMenu, Nom, Prix)
VALUES (8, 'Menu Délice', 40);

-- Insert 9
INSERT INTO MENU (IdMenu, Nom, Prix)
VALUES (9, 'Menu Économique', 18);

-- Insert 10
INSERT INTO MENU (IdMenu, Nom, Prix)
VALUES (10, 'Menu Festif', 45);

--

-- Insert 1
INSERT INTO PRODUIT (IdProduit, Nom, TypeProduit, Prix)
VALUES (1, 'Steak Grillé', 'PLAT', 15);

-- Insert 2
INSERT INTO PRODUIT (IdProduit, Nom, TypeProduit, Prix)
VALUES (2, 'Frites Croustillantes', 'ACCOMPAGNEMENT', 5);

-- Insert 3
INSERT INTO PRODUIT (IdProduit, Nom, TypeProduit, Prix)
VALUES (3, 'Gâteau au Chocolat', 'DESSERT', 8);

-- Insert 4
INSERT INTO PRODUIT (IdProduit, Nom, TypeProduit, Prix)
VALUES (4, 'Soda Cola', 'BOISSON', 3);

-- Insert 5
INSERT INTO PRODUIT (IdProduit, Nom, TypeProduit, Prix)
VALUES (5, 'Salade Fraîche', 'PLAT', 10);

-- Insert 6
INSERT INTO PRODUIT (IdProduit, Nom, TypeProduit, Prix)
VALUES (6, 'Riz Parfumé', 'ACCOMPAGNEMENT', 4);

-- Insert 7
INSERT INTO PRODUIT (IdProduit, Nom, TypeProduit, Prix)
VALUES (7, 'Tarte aux Fruits', 'DESSERT', 12);

-- Insert 8
INSERT INTO PRODUIT (IdProduit, Nom, TypeProduit, Prix)
VALUES (8, 'Eau Minérale', 'BOISSON', 2);

-- Insert 9
INSERT INTO PRODUIT (IdProduit, Nom, TypeProduit, Prix)
VALUES (9, 'Poulet Grillé', 'PLAT', 18);

-- Insert 10
INSERT INTO PRODUIT (IdProduit, Nom, TypeProduit, Prix)
VALUES (10, 'Pommes de Terre au Four', 'ACCOMPAGNEMENT', 6);

--

-- Insert 1
INSERT INTO S_OCCUPE_DE (IdCommande, IdEmploye)
VALUES (1, 1);

-- Insert 2
INSERT INTO S_OCCUPE_DE (IdCommande, IdEmploye)
VALUES (2, 2);

-- Insert 3
INSERT INTO S_OCCUPE_DE (IdCommande, IdEmploye)
VALUES (3, 3);

-- Insert 4
INSERT INTO S_OCCUPE_DE (IdCommande, IdEmploye)
VALUES (4, 4);

-- Insert 5
INSERT INTO S_OCCUPE_DE (IdCommande, IdEmploye)
VALUES (5, 5);

-- Insert 6
INSERT INTO S_OCCUPE_DE (IdCommande, IdEmploye)
VALUES (6, 6);

-- Insert 7
INSERT INTO S_OCCUPE_DE (IdCommande, IdEmploye)
VALUES (7, 7);

-- Insert 8
INSERT INTO S_OCCUPE_DE (IdCommande, IdEmploye)
VALUES (8, 8);

-- Insert 9
INSERT INTO S_OCCUPE_DE (IdCommande, IdEmploye)
VALUES (9, 9);

-- Insert 10
INSERT INTO S_OCCUPE_DE (IdCommande, IdEmploye)
VALUES (10, 10);


--

-- Insert 1
INSERT INTO DISPOSE_MENU (IdMenu, IdResto)
VALUES (1, 1);

-- Insert 2
INSERT INTO DISPOSE_MENU (IdMenu, IdResto)
VALUES (2, 2);

-- Insert 3
INSERT INTO DISPOSE_MENU (IdMenu, IdResto)
VALUES (3, 3);

-- Insert 4
INSERT INTO DISPOSE_MENU (IdMenu, IdResto)
VALUES (4, 4);

-- Insert 5
INSERT INTO DISPOSE_MENU (IdMenu, IdResto)
VALUES (5, 5);

-- Insert 6
INSERT INTO DISPOSE_MENU (IdMenu, IdResto)
VALUES (6, 6);

-- Insert 7
INSERT INTO DISPOSE_MENU (IdMenu, IdResto)
VALUES (7, 7);

-- Insert 8
INSERT INTO DISPOSE_MENU (IdMenu, IdResto)
VALUES (8, 8);

-- Insert 9
INSERT INTO DISPOSE_MENU (IdMenu, IdResto)
VALUES (9, 9);

-- Insert 10
INSERT INTO DISPOSE_MENU (IdMenu, IdResto)
VALUES (10, 10);


--

-- Insert 1
INSERT INTO DISPOSE_PRODUIT (IdResto, IdProduit,Quantite)
VALUES (1, 1, 50);

-- Insert 2
INSERT INTO DISPOSE_PRODUIT (IdResto, IdProduit,Quantite)
VALUES (2, 2, 50);

-- Insert 3
INSERT INTO DISPOSE_PRODUIT (IdResto, IdProduit,Quantite)
VALUES (3, 3, 50);

-- Insert 4
INSERT INTO DISPOSE_PRODUIT (IdResto, IdProduit,Quantite)
VALUES (4, 4, 50);

-- Insert 5
INSERT INTO DISPOSE_PRODUIT (IdResto, IdProduit,Quantite)
VALUES (5, 5, 50);

-- Insert 6
INSERT INTO DISPOSE_PRODUIT (IdResto, IdProduit,Quantite)
VALUES (6, 6, 50);

-- Insert 7
INSERT INTO DISPOSE_PRODUIT (IdResto, IdProduit,Quantite)
VALUES (7, 7, 50);

-- Insert 8
INSERT INTO DISPOSE_PRODUIT (IdResto, IdProduit,Quantite)
VALUES (8, 8, 50);

-- Insert 9
INSERT INTO DISPOSE_PRODUIT (IdResto, IdProduit,Quantite)
VALUES (9, 9, 50);

-- Insert 10
INSERT INTO DISPOSE_PRODUIT (IdResto, IdProduit,Quantite)
VALUES (10, 10, 50);

--

-- Insert 1
INSERT INTO CONTIENT (IdProduit, IdMenu)
VALUES (1, 1);

-- Insert 2
INSERT INTO CONTIENT (IdProduit, IdMenu)
VALUES (2, 2);

-- Insert 3
INSERT INTO CONTIENT (IdProduit, IdMenu)
VALUES (3, 3);

-- Insert 4
INSERT INTO CONTIENT (IdProduit, IdMenu)
VALUES (4, 4);

-- Insert 5
INSERT INTO CONTIENT (IdProduit, IdMenu)
VALUES (5, 5);

-- Insert 6
INSERT INTO CONTIENT (IdProduit, IdMenu)
VALUES (6, 6);

-- Insert 7
INSERT INTO CONTIENT (IdProduit, IdMenu)
VALUES (7, 7);

-- Insert 8
INSERT INTO CONTIENT (IdProduit, IdMenu)
VALUES (8, 8);

-- Insert 9
INSERT INTO CONTIENT (IdProduit, IdMenu)
VALUES (9, 9);

-- Insert 10
INSERT INTO CONTIENT (IdProduit, IdMenu)
VALUES (10, 10);

--

-- Insert 1
INSERT INTO EST_DANS_PRODUIT (IdCommande, IdProduit,QuantiteP)
VALUES (1, 1, 2);

-- Insert 2
INSERT INTO EST_DANS_PRODUIT (IdCommande, IdProduit,QuantiteP)
VALUES (2, 2, 1);

-- Insert 3
INSERT INTO EST_DANS_PRODUIT (IdCommande, IdProduit,QuantiteP)
VALUES (3, 3, 1);

-- Insert 4
INSERT INTO EST_DANS_PRODUIT (IdCommande, IdProduit,QuantiteP)
VALUES (4, 4, 5);

-- Insert 5
INSERT INTO EST_DANS_PRODUIT (IdCommande, IdProduit,QuantiteP)
VALUES (5, 5, 2);

-- Insert 6
INSERT INTO EST_DANS_PRODUIT (IdCommande, IdProduit,QuantiteP)
VALUES (6, 6, 4);

-- Insert 7
INSERT INTO EST_DANS_PRODUIT (IdCommande, IdProduit,QuantiteP)
VALUES (7, 7, 2);

-- Insert 8
INSERT INTO EST_DANS_PRODUIT (IdCommande, IdProduit,QuantiteP)
VALUES (8, 8, 7);

-- Insert 9
INSERT INTO EST_DANS_PRODUIT (IdCommande, IdProduit,QuantiteP)
VALUES (9, 9, 1);

-- Insert 10
INSERT INTO EST_DANS_PRODUIT (IdCommande, IdProduit,QuantiteP)
VALUES (10, 10, 1);


--

-- Insert 1
INSERT INTO EST_DANS_MENU (IdCommande, IdMenu, QuantiteM)
VALUES (1, 1, 2);

-- Insert 2
INSERT INTO EST_DANS_MENU (IdCommande, IdMenu, QuantiteM)
VALUES (2, 2, 2);

-- Insert 3
INSERT INTO EST_DANS_MENU (IdCommande, IdMenu, QuantiteM)
VALUES (3, 3, 2);

-- Insert 4
INSERT INTO EST_DANS_MENU (IdCommande, IdMenu, QuantiteM)
VALUES (4, 4, 2);

-- Insert 5
INSERT INTO EST_DANS_MENU (IdCommande, IdMenu, QuantiteM)
VALUES (5, 5, 2);

-- Insert 6
INSERT INTO EST_DANS_MENU (IdCommande, IdMenu, QuantiteM)
VALUES (6, 6, 2);

-- Insert 7
INSERT INTO EST_DANS_MENU (IdCommande, IdMenu, QuantiteM)
VALUES (7, 7, 2);

-- Insert 8
INSERT INTO EST_DANS_MENU (IdCommande, IdMenu, QuantiteM)
VALUES (8, 8, 2);

-- Insert 9
INSERT INTO EST_DANS_MENU (IdCommande, IdMenu, QuantiteM)
VALUES (9, 9, 2);

-- Insert 10
INSERT INTO EST_DANS_MENU (IdCommande, IdMenu, QuantiteM)
VALUES (10, 10, 2);
