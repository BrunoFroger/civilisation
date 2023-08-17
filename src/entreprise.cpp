//-----------------------------------------
//
//          entreprise.hpp
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>

#include "../inc/entreprise.hpp"

//-----------------------------------------
//
//          Entreprise::initHumain
//
//-----------------------------------------
void Entreprise::initEntreprise(long id, const char *nom){
    this->id = id;
    strcpy(this->nom ,nom);
    //log(LOG_INFO, "Humain::initHumain : fin");
}

//-----------------------------------------
//
//          Humain::getId
//
//-----------------------------------------
long Entreprise::getIdEntreprise(void){
    return id;
}

//-----------------------------------------
//
//          Humain::getNom
//
//-----------------------------------------
char *Entreprise::getNomEntreprise(void){
    return nom;
}
