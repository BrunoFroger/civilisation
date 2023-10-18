//-----------------------------------------
//
//          compteBancaire.cpp
//
//-----------------------------------------

#include <cstdio>
#include <cstring>

#include "../inc/compteBancaire.hpp"
#include "../inc/log.hpp"
#include "../inc/element.hpp"

int idCompteBancaire = 0;

//-----------------------------------------
//
//          CompteBancaire
//
//-----------------------------------------
CompteBancaire::CompteBancaire(Element *titulaire, int capitalInitial){
    initCompteBancaire(titulaire, capitalInitial);
    id = idCompteBancaire++;
    //log(LOG_DEBUG, "creation compte bancaire N° : %d", id);
}

//-----------------------------------------
//
//          CompteBancaire
//
//-----------------------------------------
CompteBancaire::CompteBancaire(Element *tutulaire){
    CompteBancaire(titulaire, 0);
}

//-----------------------------------------
//
//          initCompteBancaire
//
//-----------------------------------------
void CompteBancaire::initCompteBancaire(Element *titulaire, int capitalInitial){
    solde = capitalInitial;
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
//          getId
//
//-----------------------------------------
int CompteBancaire::getId(){
    return id;
}

//-----------------------------------------
//
//          credite
//
//-----------------------------------------
bool CompteBancaire::credite(int valeur){
    if (valeur < 0){
        log(LOG_ERROR, "credite : impossible de crediter une valeur negative");
        return false;
    } 
    solde += valeur;
    //log(LOG_DEBUG, "compte %d : credit de %d OK", id, valeur);
    return true;
}

//-----------------------------------------
//
//          credite
//
//-----------------------------------------
bool CompteBancaire::debite(int valeur){
    if ((solde - valeur) < 0){
        log(LOG_ERROR, "debite : solde insufisant pour effectuer le virement");
        return false;
    } 
    solde -= valeur;
    //log(LOG_DEBUG, "compte %d : debit de %d OK", id, valeur);
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
    if (valeur < 0 ){
        log(LOG_ERROR, "virement négatif interdit");
        return false;
    } 
    if ((solde - valeur) < 0){
        log(LOG_ERROR, "solde insufisant pour effectuer le virement");
        return false;
    } 
    if (destinataire != NULL){
        //log(LOG_DEBUG, "virement de %d de la part de %s (id=%d) vers %s (id=%d)", valeur,
        //            this->titulaire->getNom(), this->titulaire->getElementId(),
        //            destinataire->titulaire->getNom(), destinataire->titulaire->getElementId());
        bool res = debite(valeur);
        res &= destinataire->credite(valeur);
        //log(LOG_INFO, "virement de %d fait res = %d", valeur, res);
        return res;
    } else {
        log(LOG_ERROR, "Virement impossible, le compte destinataire n'existe pas");
        return false;
    }
    return true;
}