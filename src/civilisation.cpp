//-----------------------------------------
//
//          civilisation.cpp
//
//-----------------------------------------

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "../inc/civilisation.hpp"
#include "../inc/log.hpp"
#include "../inc/element.hpp"


const Element elementVide = Element(-1, TYPE_INDEFINI);
Element *elements[MAX_ELEMENTS];

//-----------------------------------------
//
//          Civilisation::civilisation
//
//-----------------------------------------
Civilisation::Civilisation(){
    log(LOG_INFO, "===================================");
    log(LOG_INFO, "     C I V I L I S A T I O N ");
    log(LOG_INFO, "===================================");
    log(LOG_INFO, "Creation d'une civilisation");
    log(LOG_DEBUG, "Civilisation::Civilisation => debut");
    this->courantElementId = 0;
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        elements[i] = new Element(-1, TYPE_INDEFINI);
    }
    log(LOG_DEBUG, "Civilisation::Civilisation => fin");
    nbHommes = 0;
    nbFemmes = 0;
    nbHumains = 0;
    nbEntreprises = 0;
}

//-----------------------------------------
//
//          Civilisation::~civilisation
//
//-----------------------------------------
Civilisation::~Civilisation(){
    //log(LOG_INFO, "Civilisation::~Civilisation");
    /*for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        delete elements[i];
    }*/
}

//-----------------------------------------
//
//          Civilisation::Civilisation::getNbHumain
//
//-----------------------------------------
int Civilisation::getNbHumain(void){
    return this->nbHumains;
}

//-----------------------------------------
//
//          Civilisation::getNbEntreprise
//
//-----------------------------------------
int Civilisation::getNbEntreprise(void){
    return this->nbEntreprises;
}

//-----------------------------------------
//
//          Civilisation::newElementId
//
//-----------------------------------------
void Civilisation::incElementId(void){
    this->courantElementId++;
}

//-----------------------------------------
//
//          Civilisation::getCourantElementId
//
//-----------------------------------------
int Civilisation::getCourantElementId(void){
    return this->courantElementId;
}

//-----------------------------------------
//
//          Civilisation::getElement
//
//-----------------------------------------
Element *Civilisation::getElement(int index){
    return elements[index];
}

//-----------------------------------------
//
//          Civilisation::creeElementHumain
//
//-----------------------------------------
Element *Civilisation::creeElementHumain(int sexe, char *nom, int capitalInitial){
    log(LOG_INFO, "Civilisation::creeElementHumain(int sexe, char *nom) => (id=%d) %d, %s", courantElementId, sexe, nom);
    Element *tmpElement = elements[courantElementId];
    tmpElement->initHumain(courantElementId, sexe, nom, capitalInitial);
    tmpElement->setTypeElement(TYPE_HUMAIN);
    tmpElement->setElementId(courantElementId);
    incElementId();
    this->nbHumains++;
    if (sexe == HOMME){
        nbHommes++;
    } else {
        nbFemmes++;
    }
    return tmpElement;
}

//-----------------------------------------
//
//          Civilisation::creeElementEntreprise
//
//-----------------------------------------
Element *Civilisation::creeElementEntreprise(int activite, char *nom, int capital){
    log(LOG_INFO, "Civilisation::creeElementEntreprise(int activite, char *nom) => (id=%d) %d, %s", courantElementId, activite, nom);
    Element *tmpElement = elements[courantElementId];
    tmpElement->initEntreprise(courantElementId, activite, nom, capital);
    tmpElement->setTypeElement(TYPE_ENTREPRISE);
    tmpElement->setElementId(courantElementId);
    incElementId();
    this->nbEntreprises++;
    return tmpElement;
}

//-----------------------------------------
//
//          Civilisation::listeElements
//
//-----------------------------------------
void Civilisation::listeElement(int id){
    Element *ptr = elements[id];
    switch(ptr->getTypeElement()){
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
//          Civilisation::listeCivilisation
//
//-----------------------------------------
void Civilisation::listeCivilisation(void){
    // afichage des individus
    char tmp[50];
    printf("+---------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                      population  %4d individus                                                |\n", getNbHumain());
    printf("+--------+---------------------------+-----+-----+-----+-----+-----+-------+------+------------+-----------------+\n");
    printf("|   id   |                       nom | sexe| conj| enf | pere| mere|  age  |status|    capital |         epargne |\n");
    printf("+--------+---------------------------+-----+-----+-----+-----+-----+-------+------+------------+-----------------+\n");
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        Element *ptr = elements[i];
        if (ptr->getTypeElement() == TYPE_HUMAIN){
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
                case STATUS_MARITAL_DECES: 
                    strcpy(tmp, "DECE");
                    break;
                default: 
                    strcpy(tmp, "-NC-");
                    break;
            }
            printf("| %5d  | %25s |  %c  | %3d | %3d | %3d | %3d | %5d | %4s | %10d | %15d |\n", 
                ptr->getIdHumain(),
                ptr->getNomHumain(), 
                ptr->getSexeChar(),
                ptr->getConjoint(),
                ptr->getNbEnfants(),
                ptr->getPere(),
                ptr->getMere(),
                ptr->getAge(),
                tmp,
                ptr->compteBancaireHumain->getSolde(),
                ptr->compteBancaireHumain->getEpargne());
        }
    }
    printf("+--------+---------------------------+-----+-----+-----+-----+-----+-------+------+------------+-----------------+\n");

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
        if (ptr->getTypeElement() == TYPE_ENTREPRISE){
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
//          Civilisation::evolutionCivilisation
//
//-----------------------------------------
void Civilisation::evolutionCivilisation(void){
    Element *ptr;
    log(LOG_INFO, "===================================");
    log(LOG_INFO, "");
    log(LOG_INFO, "Civilisation::evolutionCivilisation");
    log(LOG_INFO, "");
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
         ptr = elements[i];
         switch(ptr->getTypeElement()){
            case TYPE_HUMAIN:
                log(LOG_INFO, "===================================");
                ptr->evolutionHumain();
                ptr->execScript();
                break;
            case TYPE_ENTREPRISE:
                log(LOG_INFO, "===================================");
                ptr->evolutionEntreprise();
                ptr->execScript();
                break;
            default:
                break;
         }
    }
    log(LOG_INFO, "===================================");
}

//-----------------------------------------
//
//          Civilisation::killCivilisation
//
//-----------------------------------------
void Civilisation::killCivilisation(void){
    log(LOG_DEBUG, "Civilisation::killCivilisation => TODO");
}

//-----------------------------------------
//
//          Civilisation::tableauDeBord
//
//-----------------------------------------
void Civilisation::tableauDeBord(void){
    //log(LOG_DEBUG, "Civilisation::tableauDeBord => TODO");
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
        //printf("Civilisation::tableauDeBord => analyse de l'élément %d\n", i);
        element = getElement(i);
        if (element->getTypeElement() == TYPE_HUMAIN){
            _nbHumains++;
            if (element->getSexe() == HOMME) _nbHommes++;
            if (element->getSexe() == FEMME) _nbFemmes++;
            if (element->getStatusMarital() == STATUS_MARITAL_CELIB) _nbCelibs++;
            if (element->getStatusMarital() == STATUS_MARITAL_MARIE) _nbMaries++;
            if (element->getStatusMarital() == STATUS_MARITAL_VEUF) _nbVeufs++;
            if (element->getStatusMarital() == STATUS_MARITAL_DIVOR) _nbDivorces++;
            _totalActifs += element->compteBancaireHumain->getSolde();
            _totalEpargne += element->compteBancaireHumain->getEpargne();
        } else if (element->getTypeElement() == TYPE_ENTREPRISE) {
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
        } else {
            _nbElementsIndefinis++;
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

//-----------------------------------------
//
//          Civilisation::listeCommandesEtVariables
//
//-----------------------------------------
void Civilisation::listeCommandesEtVariables(void){
    char tmp[5000] = "";
    strcat(tmp, Humain::listeVariables());
    strcat(tmp, Entreprise::listeVariables());
    printf("%s\n", tmp);
}

//-----------------------------------------
//
//          Civilisation::getConjoint
//
//-----------------------------------------
Humain *Civilisation::getConjoint(int sexeDemande){
    for (int i = 0 ; i < MAX_HUMAIN ; i++){
        Element *tmpElement = elements[i];
        if (tmpElement->getTypeElement() == TYPE_HUMAIN){
            if ((tmpElement->getStatusMarital() == STATUS_MARITAL_CELIB) ||
                (tmpElement->getStatusMarital() == STATUS_MARITAL_VEUF) ||
                (tmpElement->getStatusMarital() == STATUS_MARITAL_DIVOR)){
                if (tmpElement->getSexe() == sexeDemande) return tmpElement;
            }
        }
    }
    return NULL;
}

//-----------------------------------------
//
//          Civilisation::getSalarie
//
//-----------------------------------------
Humain *Civilisation::getSalarie(void){
    for (int i = 0 ; i < MAX_HUMAIN ; i++){
        Element *tmpElement = elements[i];
        if (tmpElement->getTypeElement() == TYPE_HUMAIN){
            if (tmpElement->getEmployeur() == NULL){
                    return tmpElement;
            }
        }
    }
    return NULL;
}

//-----------------------------------------
//
//          Civilisation::getNbHommes
//
//-----------------------------------------
int Civilisation::getNbHommes(void){
    return nbHommes;
}

//-----------------------------------------
//
//          Civilisation::getNbFemmes
//
//-----------------------------------------
int Civilisation::getNbFemmes(void){
    return nbFemmes;
}

//-----------------------------------------
//
//          Civilisation::chargeConfiguration
//
//-----------------------------------------
void Civilisation::chargeConfiguration(char *configFilename){
    char ligne[200];
    FILE *ficConfig = fopen(configFilename, "r");
    if (ficConfig == NULL){
        log(LOG_ERROR, "le fichier de configuration %s n'existe pas", configFilename);
        log(LOG_ERROR, "chargement de la configuration par defaut");
        creeElementHumain(HOMME, (char *)"adam", 1000);
        creeElementHumain(FEMME, (char *)"eve", 1000);
        creeElementEntreprise(ACTIVITE_COMMERCE, (char *)"auBonPain", 10000);
    } else {
        log(LOG_INFO, "Chargement du fichier de configuration de la civilisation (%s)", configFilename);
        while (!feof(ficConfig)){
            strcpy(ligne, "");
            fgets(ligne, 200, ficConfig);
            ligne[strlen(ligne) - 1] = '\0';
            remove_extra_spaces(ligne);
            if (strlen(ligne) == 0) continue;
            if (ligne[0] == '#') continue;
            //log(LOG_DEBUG, "Civilisation::chargeConfiguration => ligne lue = '%s'", ligne);
            int type, capital, i = 0, j = 0;
            char nom[40] = "";
            char tmp[40] = "";
            while((ligne[i] != ',' ) && (i < strlen(ligne))) i++;   // suppression 1er mot de la ligne
            i++;
            while((ligne[i] != ',' ) && (i < strlen(ligne))) tmp[j++] = ligne[i++]; // recuperation du type
            tmp[j] = '\0';
            j=0;
            type = atoi(tmp);
            log(LOG_DEBUG, "type = '%s' -> '%d'", tmp, type);

            while((ligne[i] != ',' )  && (i < strlen(ligne))){
                printf("%d : %c\n", i, ligne[i]);
                i++;
            } 
            i++;
                printf("%d : %c\n", i, ligne[i]);
            while((ligne[i] != ',' ) && (i < strlen(ligne))) nom[j++] = ligne[i++];
            nom[j] = '\0';
            j=0;
            i++;
            remove_extra_spaces(nom);
            log(LOG_DEBUG, "nom = '%s'", nom);

            strcmp(tmp, "");
            while((ligne[i] != ',' ) && (i < strlen(ligne))) tmp[j++] = ligne[i++];
            tmp[j] = '\0';
            j=0;
            capital = atoi(tmp);
            log(LOG_DEBUG, "capital = '%s' -> '%d'", tmp, capital);

            if (strncmp(ligne, "humain", 5) == 0){
                log(LOG_INFO, "creation d'un humain sexe = %d, nom = %s, capital = %d", type, nom, capital);
                creeElementHumain(type, nom, capital);
            } else if (strncmp(ligne, "entreprise", 10) == 0){
                log(LOG_INFO, "creation d'une entreprise sexe = %d, nom = %s, capital = %d", type, nom, capital);
                creeElementEntreprise(type, nom, capital);
            }
        }
    }
}