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
    char tmp[50];
    printf("+----------------------------------------------------------------------------------------+\n");
    printf("|             population  %4d individus                                                 |\n", getNbHumain());
    printf("+--------+---------------------------+-----+-------+------+------------+-----------------+\n");
    printf("|   id   |                       nom | sexe|  age  |status|    capital |         epargne |\n");
    printf("+--------+---------------------------+-----+-------+------+------------+-----------------+\n");
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        Element *ptr = elements[i];
        if (ptr->typeElement == TYPE_HUMAIN){
            switch(ptr->getStatusMarital()){
                case STATUS_MARITAL_CELIB: 
                    strcpy(tmp, "CELI");
                    break;
                case STATUS_MARITAL_MARIE: 
                    strcpy(tmp, "MARI");
                    break;
                case STATUS_MARITAL_VEUF: 
                    strcpy(tmp, "VEUF");
                    break;
                case STATUS_MARITAL_DIVOR: 
                    strcpy(tmp, "DIVO");
                    break;
            }
            printf("| %5d  | %25s |  %d  | %5d | %4s | %10d | %15d |\n", 
                ptr->getIdHumain(),
                ptr->getNomHumain(), 
                ptr->getSexe(),
                ptr->getAge(),
                tmp,
                ptr->compteBancaireHumain->getSolde(),
                ptr->compteBancaireHumain->getEpargne());
        }
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
    Element *element;
    int _nbHumains = 0;
    int _nbElements =  this->nbEntreprises + this->nbHumains;
    int _nbElementsIndefinis = 0;
    int _nbHommes = 0;
    int _nbFemmes = 0;
    int _nbCelibs = 0;
    int _nbMaries = 0;
    int _nbVeufs = 0;
    int _nbDivorces = 0;
    int _nbEntreprises = 0;
    int _nbCommerces = 0;
    int _nbIndustries = 0;
    int _nbAutresEntreprises = 0;
    int _totalActifs = 0;
    int _totalEpargne = 0;
    for (int i = 0 ; i < getCourantElementId() ; i++){
        printf("Civilisation::tableauDeBord => analyse de l'élément %d\n", i);
        element = getElement(i);
        if (element->typeElement == TYPE_HUMAIN){
            _nbHumains++;
            if (element->getSexe() == HOMME) _nbHommes++;
            if (element->getSexe() == FEMME) _nbFemmes++;
            if (element->getStatusMarital() == STATUS_MARITAL_CELIB) _nbCelibs++;
            if (element->getStatusMarital() == STATUS_MARITAL_MARIE) _nbMaries++;
            if (element->getStatusMarital() == STATUS_MARITAL_VEUF) _nbVeufs++;
            if (element->getStatusMarital() == STATUS_MARITAL_DIVOR) _nbDivorces++;
            _totalActifs += element->compteBancaireHumain->getSolde();
            _totalEpargne += element->compteBancaireHumain->getEpargne();
        } else if (element->typeElement == TYPE_ENTREPRISE) {
            _nbEntreprises++;
            _totalActifs += element->compteBancaireEntreprise->getSolde();
            _totalEpargne += element->compteBancaireEntreprise->getEpargne();
            switch(element->getActivite()){
                case ACTIVITE_COMMERCE:
                    _nbCommerces++;
                    break;
                case ACTIVITE_INDUSTRIE:
                    _nbIndustries++;
                    break;
                default:
                    _nbAutresEntreprises++;
                    break;
            }
        }
    }

    printf("+-------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                       T A B L E A U   D E   B O R D                                         |\n");
    printf("+-------------------------------------------------------------------------------------------------------------+\n");
    printf("|  constantes   MAX Elements = %5d   MAX Humains = %5d                                                    |\n", MAX_ELEMENTS, MAX_HUMAIN);
    printf("|               nombres d'éléménts = %5d                                                                    |\n", _nbElements);
    printf("|               types Elements = INDEFINI/HUMAIN/ENTREPRISE                                                   |\n");
    printf("|               types Humain = HOMME/FEMME/INDUSTRIE                                                          |\n");
    printf("|               types status marital = CELIBATAIRE/MARIE/VEUF/DIVORCE                                         |\n");
    printf("|               types Entreprises = INCONNUE/COMMERCE/INDUSTRIE                                               |\n");
    printf("+-----------------------------------++-----------------------------------++-----------------------------------+\n");
    printf("|               humains             ||            entreprises            ||          comptes banquaires       |\n");
    //printf("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n"); 
    printf("+-----------------+-----------------++-----------------+-----------------++-----------------+-----------------+\n");
    printf("| %15s | %15d || %15s | %15d || %15s | %15d |\n","nombre", _nbHumains, "nombre", _nbEntreprises, "nombre", _nbElements);
    printf("| %15s | %15d || %15s | %15d || %15s | %15d |\n","nb hommes", _nbHommes, "nb commerces", _nbCommerces, "total actifs", _totalActifs);
    printf("| %15s | %15d || %15s | %15d || %15s | %15d |\n","nb femmes", _nbFemmes, "nb industries", _nbIndustries, "total epargne", _totalEpargne);
    printf("| %15s | %15d || %15s | %15d || %15s | %15s |\n","nb celib", _nbCelibs, "nb autres", _nbAutresEntreprises, "", "");
    printf("| %15s | %15d || %15s | %15d || %15s | %15s |\n","nb marie", _nbMaries, "max employes", MAX_EMPLOYES, "", "");
    printf("| %15s | %15d || %15s | %15s || %15s | %15s |\n","nb divorce", _nbDivorces, "", "", "", "");
    printf("| %15s | %15d || %15s | %15s || %15s | %15s |\n","nb veuf", _nbVeufs, "", "", "", "");
    printf("+-----------------+-----------------++-----------------+-----------------++-----------------+-----------------+\n");
}
