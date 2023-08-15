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
//          Entreprise::init
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
long Entreprise::getId(void){
    return id;
}

//-----------------------------------------
//
//          Humain::getNom
//
//-----------------------------------------
char *Entreprise::getNom(void){
    return nom;
}
