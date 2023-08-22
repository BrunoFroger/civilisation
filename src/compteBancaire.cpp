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
    solde = CapitalInitial;
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