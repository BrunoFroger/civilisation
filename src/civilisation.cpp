//-----------------------------------------
//
//          civilisation.cpp
//
//-----------------------------------------

#include <stdio.h>

#include "../inc/civilisation.hpp"
#include "../inc/log.hpp"
#include "../inc/element.hpp"


Element elementVide = Element(-1, TYPE_INDEFINI);

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
        this->elements[i] = elementVide;
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
//          newElementId
//
//-----------------------------------------
void Civilisation::incElementId(void){
    this->courantElementId++;
}

//-----------------------------------------
//
//          creeElementHumain
//
//-----------------------------------------
void Civilisation::creeElementHumain(int sexe, char *nom){
    Element *tmpElement = &(this->elements[courantElementId]);
    tmpElement->initHumain(courantElementId, sexe, nom);
    incElementId();
    this->nbHumains++;
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
        Element *ptr = &elements[i];
        if (ptr->typeElement == TYPE_HUMAIN)
            if (ptr->getId() != -1){
                printf("| %5ld  | %25s |  %d  | %5d |  %d  |\n", 
                    ptr->getId(),
                    ptr->getNom(), 
                    ptr->getSexe(),
                    ptr->getAge(),
                    ptr->getCelibataire());
            }
    }
    printf("+--------+---------------------------+-----+-------+-----+\n");
}

//-----------------------------------------
//
//          evolutionCivilisation
//
//-----------------------------------------
void Civilisation::evolutionCivilisation(void){
    // TODO
}