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
//          creeElementHumain
//
//-----------------------------------------
void Civilisation::creeElementHumain(int sexe, char *nom){
    log(LOG_DEBUG, "Civilisation::creeElementHumain(int sexe, char *nom) => (id=%d) %d, %s", courantElementId, sexe, nom);
    Element *tmpElement = this->elements[courantElementId];
    tmpElement->initHumain(courantElementId, sexe, nom);
    tmpElement->typeElement=TYPE_HUMAIN;
    incElementId();
    this->nbHumains++;
}

//-----------------------------------------
//
//          creeElementEntreprise
//
//-----------------------------------------
void Civilisation::creeElementEntreprise(int activite, char *nom){
    log(LOG_DEBUG, "Civilisation::creeElementEntreprise(int activite, char *nom) => (id=%d) %d, %s", courantElementId, activite, nom);
    Element *tmpElement = this->elements[courantElementId];
    tmpElement->initEntreprise(courantElementId, activite, nom);
    tmpElement->typeElement=TYPE_ENTREPRISE;
    tmpElement->setElementId(courantElementId);
    incElementId();
    this->nbEntreprises++;
}


//-----------------------------------------
//
//          listeElements
//
//-----------------------------------------
void Civilisation::listeElements(void){
    // afichage des elements
    printf("+--------+---------------------------+-----+\n");
    printf("|   id   |                       nom | type|\n");
    printf("+--------+---------------------------+-----+\n");
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        Element *ptr = elements[i];
        char tmpNom[25]="";
        switch(ptr->typeElement){
            case TYPE_HUMAIN:
                strcpy(tmpNom, ptr->getNomHumain());
                break;
            case TYPE_ENTREPRISE:
                strcpy(tmpNom, ptr->getNomEntreprise());
                break;
        }
        printf("| %5d  | %25s |  %d  |\n", 
            ptr->getElementId(),
            tmpNom, 
            ptr->typeElement);
    }
    printf("+--------+---------------------------+-----+\n");
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
    printf("+--------+---------------------------+-----+-------+-----+\n");
    printf("|   id   |                       nom | sexe|  age  |celib|\n");
    printf("+--------+---------------------------+-----+-------+-----+\n");
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        Element *ptr = elements[i];
        if (ptr->typeElement == TYPE_HUMAIN)
            if (ptr->getIdHumain() != -1){
                printf("| %5d  | %25s |  %d  | %5d |  %d  |\n", 
                    ptr->getIdHumain(),
                    ptr->getNomHumain(), 
                    ptr->getSexe(),
                    ptr->getAge(),
                    ptr->getCelibataire());
            }
    }
    printf("+--------+---------------------------+-----+-------+-----+\n");

    // affichage des entreprises 
    // TODO
    // afichage des individus
    printf("+-----------------------------------------------+\n");
    printf("|             population  %4d entreprises      |\n", getNbEntreprise());
    printf("+--------+---------------------------+----------+\n");
    printf("|   id   |                       nom | activité |\n");
    printf("+--------+---------------------------+----------+\n");
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        Element *ptr = elements[i];
        if (ptr->typeElement == TYPE_ENTREPRISE)
            printf("c'est une entreprise\n");
            if (ptr->getIdEntreprise() != -1){
                printf("| %5d  | %25s |   %5d  |\n", 
                    ptr->getIdEntreprise(),
                    ptr->getNomEntreprise(), 
                    ptr->getActivite());
            }
    }
    printf("+--------+---------------------------+----------+\n");

}

//-----------------------------------------
//
//          evolutionCivilisation
//
//-----------------------------------------
void Civilisation::evolutionCivilisation(void){
    log(LOG_DEBUG, "Civilisation::evolutionCivilisation => TODO");
}

//-----------------------------------------
//
//          killCivilisation
//
//-----------------------------------------
void Civilisation::killCivilisation(void){
    log(LOG_DEBUG, "Civilisation::killCivilisation => TODO");
}