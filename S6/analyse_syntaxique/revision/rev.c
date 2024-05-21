int yylex();
void fo();void ar();void as();void su();

void fo(){
    if (jeton == '(') {
        jeton = yylex();
        arbres();
        if (jeton == ')') {
            jeton = yylex();
        }
    }
}
void ar(){
  if (jeton == LITCH) {
      Foret *nouvelArbre = new Foret(jeton, NULL);
      jeton = yylex(); 
      if (jeton == '(') {
          jeton = yylex();
          arbres();
          if (jeton == ')') {
              jeton = yylex();
          }
      }
  }
}
void as(){
    arbre();
    suite();
}
void su(){
    if (jeton == ',') {
        jeton = yylex();
        arbre();
        suite();
    }
}

int main(){
    if (jeton=='q'){
        exit(0);
    } else{
        foret();
        Foret->afficher()

    }

}