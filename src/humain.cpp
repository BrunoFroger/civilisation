//-----------------------------------------
//
//          humain.cpp
//
//-----------------------------------------
#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include "../inc/humain.hpp"
#include "../inc/log.hpp"
#include "../inc/element.hpp"

#define NB_COMMANDES_VALIDES    4
char listeCommandes[20][20]= {"mort", "chercheConjoint", "ecole", "naissancePossible"};

//-----------------------------------------
//
//          Humain::Humain
//
//-----------------------------------------
Humain::Humain(){
    this->id = -1;
    this->sexe = -1;
    strcpy(this->nom , "");
    this->age = -1;
    this->statusMarital = STATUS_MARITAL_CELIB;
    this->compteBancaireHumain = new CompteBancaire();
}

//-----------------------------------------
//
//          Humain::Humain
//
//-----------------------------------------
Humain::Humain(int id, int sexe, char *nom){
    /*
    //log(LOG_INFO, "Humain::initHumain : debut");
    */
   initHumain(id, sexe, nom);
    //log(LOG_INFO, "Humain::initHumain : fin");
}

//-----------------------------------------
//
//          Humain::initHumain
//
//-----------------------------------------
void Humain::initHumain(int id, int sexe, char *nom){
    log(LOG_DEBUG, "Humain::initHumain : debut");
    this->id = id;
    this->sexe = sexe;
    strcpy(this->nom ,nom);
    this->age = 0;
    this->statusMarital = STATUS_MARITAL_CELIB;
}

//-----------------------------------------
//
//          Humain::evolution
//
//-----------------------------------------
void Humain::evolutionHumain(void){
    log(LOG_DEBUG, "Humain::evolution => evolution de %s", this->nom);
    this->age++;
}

//-----------------------------------------
//
//          Humain::getId
//
//-----------------------------------------
int Humain::getIdHumain(void){
    return id;
}

//-----------------------------------------
//
//          Humain::getNom
//
//-----------------------------------------
char *Humain::getNomHumain(void){
    return nom;
}

//-----------------------------------------
//
//          Humain::setNom
//
//-----------------------------------------
void Humain::setNom(char *nom){
    strcpy(this->nom, nom);
}

//-----------------------------------------
//
//          Humain::getSexe
//
//-----------------------------------------
int Humain::getSexe(void){
    return sexe;
}

//-----------------------------------------
//
//          Humain::setSexe
//
//-----------------------------------------
void Humain::setSexe(int sexe){
    this->sexe = sexe;
}

//-----------------------------------------
//
//          Humain::getAge
//
//-----------------------------------------
int Humain::getAge(void){
    return age;
}

//-----------------------------------------
//
//          Humain::getCelibataire
//
//-----------------------------------------
int Humain::getStatusMarital(void){
    return statusMarital;
}

//-----------------------------------------
//
//          Humain::isVariable
//
//-----------------------------------------
bool Humain::isVariable(char *valeur){
    //printf("isvariable : test de la variable %s\n", valeur);
    if (strcmp(valeur, "sexe") == 0) return true;
    if (strcmp(valeur, "nom") == 0) return true;
    if (strcmp(valeur, "age") == 0) return true;
    if (strcmp(valeur, "celibataire") == 0) return true;
    //printf("isVariable : return false \n");
    return false;
}

//-----------------------------------------
//
//          Humain::getIntValue
//
//-----------------------------------------
int Humain::getIntValue(char *valeur){
    if (strcmp(valeur, "sexe") == 0){
        printf("Humain::getIntValue : variable %s = %d\n", valeur, sexe);
        return sexe;
    }
    if (strcmp(valeur, "age") == 0){
        printf("Humain::getIntValue : variable %s = %d\n", valeur, age);
        return age;
    }
    if (strcmp(valeur, "statusMarital") == 0){
        printf("Humain::getIntValue : variable %s = %d\n", valeur, statusMarital);
        return statusMarital;
    }
    printf("Humain::getIntValue : pas trouve d'équivalence pour %s\n", valeur);
    return -1;
}

//-----------------------------------------
//
//          Humain::getCharValue
//
//-----------------------------------------
char *Humain::getCharValue(char *valeur){
    if (strcmp(valeur, "nom") == 0) return nom;
    return NULL;
}

//-----------------------------------------
//
//          calculExpression
//
//-----------------------------------------
int Humain::calculExpression(char *data1, char op, char *data2){
    int val1;
    int val2;
    int res = false;
    printf("Humain::calculExpression => debut : calcul de <%s> <%c> <%s>\n", data1, op, data2);
    if (Humain::isVariable(data1)){
        val1 = getIntValue(data1);
        printf("data1 est une variable : <%s> => <%d>\n", data1, val1);
    } else {
        val1 = atoi(data1);
    }
    if (Humain::isVariable(data2)){
        val2 = getIntValue(data2);
        printf("data2 est une variable : <%s> => <%d>\n", data2, val2);
    } else {
        val2 = atoi(data2);
    }
    printf("Humain::calculExpression => apres evaluation : calcul de <%d> <%c> <%d>\n", val1, op, val2);
    switch(op){
        case '+' : 
            res = val1 + val2;
            break;
        case '-' : 
            res = val1 - val2;
            break;
        case '*' : 
            res = val1 * val2;
            break;
        case '/' : 
            res = val1 / val2;
            break;
    }
    printf("Humain::calculExpression => resultat : <%d> <%c> <%d> = <%d>\n", val1, op, val2, res);
    return res;
}

//-----------------------------------------
//
//          Humain::testSiCommandeValide
//
//-----------------------------------------
bool Humain::testSiCommandeValide(char *valeur){
    //printf("test si commande '%s' valide\n", valeur);
    for (int i = 0 ; i < NB_COMMANDES_VALIDES ; i++){
        if (strcmp(valeur, listeCommandes[i]) == 0) return true;
    }
    return false;
    /*
    if (strcmp(valeur, "mort") == 0) return true;
    if (strcmp(valeur, "chercheConjoint") == 0) return true;
    if (strcmp(valeur, "ecole") == 0) return true;
    if (strcmp(valeur, "naissancePossible") == 0) return true;
    return false;*/
}

//-----------------------------------------
//
//          Humain::testSiListeCommandeValide
//
//-----------------------------------------
bool Humain::testSiListeCommandeValide(char *valeur){
    char *tmp;
    tmp = &valeur[0];
    char buffer[50];
    int i;
    while (tmp[0] != '\0'){
        i=0;
        strcpy(buffer,"");
        while (*tmp == ' ') tmp++;  // suppression des blancs au debut
        if (strlen(tmp) == 0) return true;
        while (*tmp != ' '){
            buffer[i++] = *tmp++;
            buffer[i] = '\0';
        }
        if (strlen(buffer) != 0){
            if (!testSiCommandeValide(buffer)){
                log(LOG_ERROR, "commande %s inconnue", buffer);
                return false;
            }
        }
    }
    return true;
}

//-----------------------------------------
//
//          Humain::execCommande
//
//-----------------------------------------
bool Humain::execCommande(char *valeur){
    log(LOG_DEBUG,"Humain::execCommande : TODO");
    return false;
}

//-----------------------------------------
//
//          Humain::listeHumain
//
//-----------------------------------------
void Humain::listeHumain(void){
    log(LOG_DEBUG,"Humain::listeHumain : TODO");
}
