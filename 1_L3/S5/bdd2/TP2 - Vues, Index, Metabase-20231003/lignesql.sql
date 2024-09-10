
alter TABLE ABONNE add DAT_AB  date;
alter table ABONNE add TYPE_AB varchar(20) check(TYPE_AB in ('ADULTE','ENFANT'));
alter table ABONNE add CAT_AB varchar(20) check(CAT_AB in ('REGULIER','OCCASIONNEL','A PROBLEME','EXCLU'));
alter table ABONNE modify NOM varchar(20);
create table AUTEUR (
	NUM_AUTEUR int primary key,
	NOM varchar(20) ,
	PRENOM varchar(20),
	NATIONALITE varchar(25)
);
create table A_ECRIT(
	NUM_AUTEUR int references AUTEUR(NUM_AUTEUR),
	ISBN VARCHAR(15),
	primary key (NUM_AUTEUR,ISBN)	
);
