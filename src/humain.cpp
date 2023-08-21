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
    this->celibataire = true;
}

//-----------------------------------------
//
//          Humain::Humain
//
//-----------------------------------------
Humain::Humain(int id, int sexe, char *nom){
    /*
    log(LOG_INFO, "Humain::initHumain : debut");

    this->id = id;
    this->sexe = sexe;
    strcpy(this->nom ,nom);
    this->age = 0;
    this->celibataire = true;
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
    /*if (sexe == 0){
        log(LOG_INFO, (char *)"Creation d'un homme (%s) id=%ld", nom, id);
    } else if (sexe == 1){
        log(LOG_INFO, (char *)"Creation d'une femme (%s) id=%ld", nom, id);
    } else {
        log(LOG_INFO, (char *)"sexe indefini id = %d", id);
    }*/
    this->id = id;
    this->sexe = sexe;
    strcpy(this->nom ,nom);
    this->age = 0;
    this->celibataire = true;
    //log(LOG_INFO, "Humain::initHumain : fin");
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
//          Humain::getSexe
//
//-----------------------------------------
bool Humain::getCelibataire(void){
    return celibataire;
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
    if (strcmp(valeur, "sexe") == 0) return sexe;
    if (strcmp(valeur, "age") == 0) return age;
    if (strcmp(valeur, "celibataire") == 0) return celibataire;
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
//          Humain::testSiCommandeValide
//
//-----------------------------------------
bool Humain::testSiCommandeValide(char *valeur){
    //printf("test si commande '%s' valide\n", valeur);
    if (strcmp(valeur, "mort") == 0) return true;
    if (strcmp(valeur, "chercheConjoint") == 0) return true;
    if (strcmp(valeur, "ecole") == 0) return true;
    if (strcmp(valeur, "naissancePossible") == 0) return true;
    return false;
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
