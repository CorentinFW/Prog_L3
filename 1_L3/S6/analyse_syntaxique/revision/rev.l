
/*(,),',',litch = char*/

%{
extern double valeur;
extern int numcar;  
%}
%option noyywrap
%%
/*1 chiffre plusieur fois suivi de . suivi d'un chiffre plusieurs fois ou rien */

[a-z|A-Z|a-z0-9|A-Z0-9] {return 300;}
^( {return 301}/*1ER parenthese pas de saut ni tab*/
( {return 302}/*saut + tab*/
) {return 303}/*fin du mot*/
[),] {return 304}/* saut de ligne + revenir sur la tab*/
, {return 305}/*saut de ligne*/



/*fin*/
/*\t tabulation*/
%%