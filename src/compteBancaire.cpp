//-----------------------------------------
//
//          compteBancaire.cpp
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>

#include "../inc/compteBancaire.hpp"

//-----------------------------------------
//
//          CompteBancaire
//
//-----------------------------------------
CompteBancaire::CompteBancaire(int CapitalInitial){
    initCompteBancaire(CapitalInitial);
}

//-----------------------------------------
//
//          CompteBancaire
//
//-----------------------------------------
CompteBancaire::CompteBancaire(){
    CompteBancaire(0);
}

//-----------------------------------------
//
//          initCompteBancaire
//
//-----------------------------------------
void CompteBancaire::initCompteBancaire(int CapitalInitial){
    solde = CapitalInitial;
}

//-----------------------------------------
//
//          getSolde
//
//-----------------------------------------
int CompteBancaire::getSolde(){
    return solde;
}

//-----------------------------------------
//
//          getEpargne
//
//-----------------------------------------
int CompteBancaire::getEpargne(){
    return epargne;
}

//-----------------------------------------
//
//          credite
//
//-----------------------------------------
bool CompteBancaire::credite(int valeur){
    if (valeur < 0) return false;
    solde += valeur;
    return true;
}

//-----------------------------------------
//
//          credite
//
//-----------------------------------------
bool CompteBancaire::debite(int valeur){
    if ((solde - valeur) < 0) return false;
    solde -= valeur;
    return true;
}

//-----------------------------------------
//
//          sauveEpargne
//
//-----------------------------------------
bool CompteBancaire::sauveEpargne(int valeur){
    if ((solde - valeur) < 0) return false;
    solde -= valeur;
    epargne += valeur;
    return true;
}

//-----------------------------------------
//
//          restitueEpargne
//
//-----------------------------------------
bool CompteBancaire::restitueEpargne(int valeur){
    if ((epargne - valeur) < 0) return false;
    solde += valeur;
    epargne -= valeur;
    return true;
}

//-----------------------------------------
//
//          virement
//
//-----------------------------------------
bool CompteBancaire::virement(CompteBancaire *destinataire, int valeur){
    if (valeur < 0) return false;
    if ((solde - valeur) < 0) return false;
    debite(valeur);
    if (destinataire != NULL){
        destinataire->credite(valeur);
    }
    return true;
}