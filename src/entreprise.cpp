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
//          Entreprise::Entreprise
//
//-----------------------------------------
Entreprise::Entreprise(){
    this->compteBancaireEntreprise = new CompteBancaire();
}

//-----------------------------------------
//
//          Entreprise::~Entreprise
//
//-----------------------------------------
Entreprise::~Entreprise(){
    delete this->compteBancaireEntreprise;
}

//-----------------------------------------
//
//          Entreprise::initEntreprise
//
//-----------------------------------------
void Entreprise::initEntreprise(int id, int activite, char *nom, int capitalInitial){
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
    log(LOG_DEBUG, "Entreprise::evolution => TODO");
    // TODO
}
