//-----------------------------------------
//
//          entreprise.hpp
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>

#include "../inc/entreprise.hpp"
#include "../inc/log.hpp"

//-----------------------------------------
//
//          Entreprise::initEntreprise
//
//-----------------------------------------
void Entreprise::initEntreprise(int id, int activite, char *nom){
    log(LOG_DEBUG, "Entreprise::initEntreprise : debut");
    this->id = id;
    this->activite = activite;
    strcpy(this->nom ,nom);
}

//-----------------------------------------
//
//          Humain::getId
//
//-----------------------------------------
int Entreprise::getIdEntreprise(void){
    return id;
}

//-----------------------------------------
//
//          Humain::getActivite
//
//-----------------------------------------
int Entreprise::getActivite(void){
    return activite;
}

//-----------------------------------------
//
//          Humain::getNom
//
//-----------------------------------------
char *Entreprise::getNomEntreprise(void){
    return nom;
}

//-----------------------------------------
//
//          Humain::evolution
//
//-----------------------------------------
void Entreprise::evolutionEntreprise(void){
    log(LOG_DEBUG, "Entreprise::evolution => evolution de %s", this->nom);
    // TODO
}
