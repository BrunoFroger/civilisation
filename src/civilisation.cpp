//-----------------------------------------
//
//          civilisation.cpp
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>

#include "../inc/civilisation.hpp"
#include "../inc/log.hpp"
#include "../inc/element.hpp"


const Element elementVide = Element(-1, TYPE_INDEFINI);

//-----------------------------------------
//
//          civilisation
//
//-----------------------------------------
Civilisation::Civilisation(){
    log(LOG_INFO, "===================================");
    log(LOG_INFO, "     C I V I L I S A T I O N ");
    log(LOG_INFO, "===================================");
    log(LOG_INFO, "Creation d'une civilisation");
    this->courantElementId = 0;
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        this->elements[i] = new Element(-1, TYPE_INDEFINI);
    }
}

//-----------------------------------------
//
//          ~civilisation
//
//-----------------------------------------
Civilisation::~Civilisation(){
    log(LOG_INFO, "Civilisation::~Civilisation");
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        delete this->elements[i];
    }
}

//-----------------------------------------
//
//          getNbHumain
//
//-----------------------------------------
int Civilisation::getNbHumain(void){
    return this->nbHumains;
}

//-----------------------------------------
//
//          getNbEntreprise
//
//-----------------------------------------
int Civilisation::getNbEntreprise(void){
    return this->nbEntreprises;
}

//-----------------------------------------
//
//          newElementId
//
//-----------------------------------------
void Civilisation::incElementId(void){
    this->courantElementId++;
}

//-----------------------------------------
//
//          getCourantElementId
//
//-----------------------------------------
int Civilisation::getCourantElementId(void){
    return this->courantElementId;
}

//-----------------------------------------
//
//          getElement
//
//-----------------------------------------
Element *Civilisation::getElement(int index){
    return this->elements[index];
}

//-----------------------------------------
//
//          creeElementHumain
//
//-----------------------------------------
void Civilisation::creeElementHumain(int sexe, char *nom){
    log(LOG_DEBUG, "Civilisation::creeElementHumain(int sexe, char *nom) => (id=%d) %d, %s", courantElementId, sexe, nom);
    Element *tmpElement = this->elements[courantElementId];
    tmpElement->initHumain(courantElementId, sexe, nom);
    tmpElement->typeElement=TYPE_HUMAIN;
    tmpElement->setElementId(courantElementId);
    incElementId();
    this->nbHumains++;
}

//-----------------------------------------
//
//          creeElementEntreprise
//
//-----------------------------------------
void Civilisation::creeElementEntreprise(int activite, char *nom, int capital){
    log(LOG_DEBUG, "Civilisation::creeElementEntreprise(int activite, char *nom) => (id=%d) %d, %s", courantElementId, activite, nom);
    Element *tmpElement = this->elements[courantElementId];
    tmpElement->initEntreprise(courantElementId, activite, nom, capital);
    tmpElement->typeElement=TYPE_ENTREPRISE;
    tmpElement->setElementId(courantElementId);
    tmpElement->compteBancaireEntreprise->credite(capital);
    incElementId();
    this->nbEntreprises++;
}


//-----------------------------------------
//
//          listeElements
//
//-----------------------------------------
void Civilisation::listeElement(int id){
    Element *ptr = elements[id];
    char tmpNom[25]="";
    switch(ptr->typeElement){
        case TYPE_HUMAIN:
            ptr->listeHumain();
            break;
        case TYPE_ENTREPRISE:
            ptr->listeEntreprise();
            break;
    }
}

//-----------------------------------------
//
//          listeCivilisation
//
//-----------------------------------------
void Civilisation::listeCivilisation(void){
    // afichage des individus
    printf("+--------------------------------------------------------+\n");
    printf("|             population  %4d individus                 |\n", getNbHumain());
    printf("+--------+---------------------------+-----+-------+-----+------------+-----------------+\n");
    printf("|   id   |                       nom | sexe|  age  |celib|    capital |         epargne |\n");
    printf("+--------+---------------------------+-----+-------+-----+------------+-----------------+\n");
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        Element *ptr = elements[i];
        if (ptr->typeElement == TYPE_HUMAIN)
            printf("| %5d  | %25s |  %d  | %5d |  %d  | %10d | %15d |\n", 
                ptr->getIdHumain(),
                ptr->getNomHumain(), 
                ptr->getSexe(),
                ptr->getAge(),
                ptr->getStatusMarital(),
                ptr->compteBancaireHumain->getSolde(),
                ptr->compteBancaireHumain->getEpargne());
    }
    printf("+--------+---------------------------+-----+-------+-----+------------+-----------------+\n");

    // affichage des entreprises 
    // TODO
    // afichage des individus
    printf("+------------------------------------------------------------------------------+\n");
    printf("|             population  %4d entreprises                                     |\n", getNbEntreprise());
    printf("+--------+---------------------------+----------+------------+-----------------+\n");
    printf("|   id   |                       nom | activité |    capital |         epargne |\n");
    printf("+--------+---------------------------+----------+------------+-----------------+\n");
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        Element *ptr = elements[i];
        if (ptr->typeElement == TYPE_ENTREPRISE){
            printf("| %5d  | %25s |   %5d  | %10d | %15d |\n", 
                ptr->getIdEntreprise(),
                ptr->getNomEntreprise(), 
                ptr->getActivite(),
                ptr->compteBancaireEntreprise->getSolde(),
                ptr->compteBancaireEntreprise->getEpargne());
        }
    }
    printf("+--------+---------------------------+----------+------------+-----------------+\n");

}

//-----------------------------------------
//
//          evolutionCivilisation
//
//-----------------------------------------
void Civilisation::evolutionCivilisation(void){
    Element *ptr;
    log(LOG_DEBUG, "===================================");
    log(LOG_DEBUG, "Civilisation::evolutionCivilisation");
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
         ptr = elements[i];
         switch(ptr->typeElement){
            case TYPE_HUMAIN:
                ptr->evolutionHumain();
                ptr->execScript();
                break;
            case TYPE_ENTREPRISE:
                ptr->evolutionEntreprise();
                ptr->execScript();
                break;
            default:
                break;
         }
    }
}

//-----------------------------------------
//
//          killCivilisation
//
//-----------------------------------------
void Civilisation::killCivilisation(void){
    log(LOG_DEBUG, "Civilisation::killCivilisation => TODO");
}

//-----------------------------------------
//
//          tableauDeBord
//
//-----------------------------------------
void Civilisation::tableauDeBord(void){
    log(LOG_DEBUG, "Civilisation::tableauDeBord => TODO");

}
