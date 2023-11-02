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
bool displayListeHumains = true;
bool displayListeEntreprises = true;
bool displayListeBanques = true;

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
    //this->courantElementId = 0;
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
//          Civilisation::getElement
//
//-----------------------------------------
Element *Civilisation::getElement(int index){
    return elements[index];
}

//-----------------------------------------
//
//          Civilisation::getEntrepriseByNom
//
//-----------------------------------------
Entreprise *Civilisation::getEntrepriseByNom(char *nom){
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        Element *element = elements[i];
        if (element->getTypeElement() == TYPE_ENTREPRISE){
            if (strcmp(element->getNomEntreprise(), nom) == 0){
                return element;
            }
        }
    }
    return NULL;
}

//-----------------------------------------
//
//          Civilisation::creeElementHumain
//
//-----------------------------------------
Element *Civilisation::creeElementHumain(int sexe, char *nom, int capitalInitial){
    //log(LOG_INFO, "Civilisation::creeElementHumain(int sexe, char *nom) => %d, %s", sexe, nom);
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        Element *tmpElement = elements[i];
        if (tmpElement->getElementId() == -1){
            if (nbHumains >= MAX_HUMAIN){
                log(LOG_ERROR, "Impossible de creer un nouvel Humain limite atteinte (%d)", MAX_HUMAIN);
                return NULL;
            }
            tmpElement->initHumain(i, sexe, nom, capitalInitial);
            tmpElement->setTypeElement(TYPE_HUMAIN);
            tmpElement->setElementId(i);
            //incElementId();
            this->nbHumains++;
            if (sexe == HOMME){
                nbHommes++;
            } else {
                nbFemmes++;
            }
            log(LOG_INFO, "Nouvel humain %s (%s) créé ", nom, tmpElement->getSexeString());
            return tmpElement;
        }
    }
    log(LOG_ERROR, "impossible de creer un humain (tous les elements sont pris) ! ");
    return NULL;
}

//-----------------------------------------
//
//          Civilisation::creeElementEntreprise
//
//-----------------------------------------
Element *Civilisation::creeElementEntreprise(int activite, char *nom, int capital, Entreprise *maisonMere){
    log(LOG_INFO, "Nouvelle enreprise %s avec un capital de %d", nom, capital);
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        Element *tmpElement = elements[i];
        if (tmpElement->getElementId() == -1){
            if (nbEntreprises >= MAX_ENTREPRISES){
                log(LOG_ERROR, "Impossible de creer une nouvelle entreprise limite atteinte (%d)", MAX_ENTREPRISES);
                return NULL;
            }
            tmpElement->initEntreprise(i, activite, nom, capital, maisonMere);
            tmpElement->setTypeElement(TYPE_ENTREPRISE);
            tmpElement->setElementId(i);
            //incElementId();
            this->nbEntreprises++;
            return tmpElement;
        }
    }
    return NULL;
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
    char employeur[5];
    char ligne[200];
    FILE *fic = fopen("listeCivilisation.txt", "w");
    if (displayListeHumains){
        snprintf(ligne, 200, "+------------------------------------------------------------------------------------------------------------------------+\n");
        printf("%s", ligne); fputs(ligne, fic);
        snprintf(ligne, 200, "|                                               population  %4d individus                                               |\n", getNbHumain());
        printf("%s", ligne); fputs(ligne, fic);
        snprintf(ligne, 200, "+--------+---------------------------+-----+-----+-----+-----+-----+-------+------+-------+------------+-----------------+\n");
        printf("%s", ligne);
        snprintf(ligne, 200, "|   id   |                       nom | sexe| conj| enf | pere| mere|  age  |status|  empl |    capital |         epargne |\n");
        printf("%s", ligne); fputs(ligne, fic);
        snprintf(ligne, 200, "+--------+---------------------------+-----+-----+-----+-----+-----+-------+------+-------+------------+-----------------+\n");
        printf("%s", ligne); fputs(ligne, fic);
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
                if (ptr->getEmployeur() == NULL){
                    snprintf(employeur, 5, (char *)"NULL");
                } else {
                    snprintf(employeur, 5, "%d", ptr->getEmployeur()->getIdEntreprise());
                }
                snprintf(ligne, 200, "| %5d  | %25s |  %c  | %3d | %3d | %3d | %3d | %5d | %4s | %5s | %10d | %15d |\n", 
                    ptr->getIdHumain(),
                    ptr->getNomHumain(), 
                    ptr->getSexeChar(),
                    ptr->getConjoint(),
                    ptr->getNbEnfants(),
                    ptr->getPere(),
                    ptr->getMere(),
                    ptr->getAge(),
                    tmp,
                    employeur,
                    ptr->compteBancaireHumain->getSolde(),
                    ptr->compteBancaireHumain->getEpargne());
                printf("%s", ligne); fputs(ligne, fic);
            }
        }
        snprintf(ligne, 200, "+--------+---------------------------+-----+-----+-----+-----+-----+-------+------+-------+------------+-----------------+\n");
        printf("%s", ligne); fputs(ligne, fic);
    }

    // affichage des entreprises 
    if (displayListeEntreprises){
        snprintf(ligne, 200, "+-------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
        printf("%s", ligne); fputs(ligne, fic);
        snprintf(ligne, 200, "|                                                          population  %4d entreprises                                                                             |\n", getNbEntreprise());
        printf("%s", ligne); fputs(ligne, fic);
        snprintf(ligne, 200, "+--------+---------------------------+---------------------------+----------+----------+----------+----------+----------+------------+------------+-----------------+\n");
        printf("%s", ligne); fputs(ligne, fic);
        snprintf(ligne, 200, "|   id   |                       nom |            nom commercial | activité | nb cde   |  stock   | nb sal   | prod sal |   cap init |    capital |         epargne |\n");
        printf("%s", ligne); fputs(ligne, fic);
        snprintf(ligne, 200, "+--------+---------------------------+---------------------------+----------+----------+----------+----------+----------+------------+------------+-----------------+\n");
        printf("%s", ligne); fputs(ligne, fic);
        for (int i = 0 ; i < MAX_ELEMENTS ; i++){
            Element *ptr = elements[i];
            if (ptr->getTypeElement() == TYPE_ENTREPRISE){
                snprintf(ligne, 200, "| %5d  | %25s | %25s |   %5d  |   %5d  |   %5d  |   %5d  |   %5d  | %10d | %10d | %15d |\n", 
                    ptr->getIdEntreprise(),
                    ptr->getNomEntreprise(), 
                    ptr->getNomCommercialEntreprise(), 
                    ptr->getActivite(),
                    ptr->getNbCommandes(),
                    ptr->getStockProduit(),
                    ptr->getNbSalaries(),
                    ptr->getProductiviteSalarie(),
                    ptr->getCapitalInitial(),
                    ptr->compteBancaireEntreprise->getSolde(),
                    ptr->compteBancaireEntreprise->getEpargne());
                printf("%s", ligne); fputs(ligne, fic);
            }
        }
        snprintf(ligne, 200, "+--------+---------------------------+---------------------------+----------+----------+----------+----------+----------+------------+------------+-----------------+\n");
        printf("%s", ligne); fputs(ligne, fic);
    }

    // liste des comptes bancaire génériques
    if (displayListeBanques){
        snprintf(ligne, 200, "+-----------------------------------------------------------------------+\n");
        printf("%s", ligne); fputs(ligne, fic);
        snprintf(ligne, 200, "|                         comptes bancaires                             |\n");
        printf("%s", ligne); fputs(ligne, fic);
        snprintf(ligne, 200, "+---------------------------------+---------+-------------+-------------+\n");
        snprintf(ligne, 200, "|            titulaire du compte  |    id   |      solde  |    epargne  |\n");
        snprintf(ligne, 200, "+---------------------------------+---------+-------------+-------------+\n");
        printf("%s", ligne); fputs(ligne, fic);
        CompteBancaire *cptGeneriques[2] = {compteBancaireFournisseurNull, compteBancaireHeritageNull};
        char *nomCptGeneriques[2] = {(char *)"compte generique Fournisseurs", (char *)"compte generique Heritages"};
        for (int i = 0 ; i < 2 ; i++){
            CompteBancaire *compte = cptGeneriques[i];
            snprintf(ligne, 200, "|  %30s |  %5d  |  %10d |  %10d |\n", nomCptGeneriques[i], compte->getId(), compte->getSolde(), compte->getEpargne());
            printf("%s", ligne); fputs(ligne, fic);
        }
        for (int i = 0 ; i < MAX_ELEMENTS ; i++){
            Element *ptr = elements[i];
            if (ptr->getElementId() != -1){
                snprintf(ligne, 200, "|  %30s |  %5d  |  %10d |  %10d |\n",ptr->getNom(), ptr->getElementId(), ptr->getCompteBancaire()->getSolde(), ptr->getCompteBancaire()->getEpargne());
                printf("%s", ligne); fputs(ligne, fic);
            }
        }
        snprintf(ligne, 200, "+---------------------------------+---------+-------------+-------------+\n");
        printf("%s", ligne); fputs(ligne, fic);
    }

    // fermeture du fichier de status de la configuration affichee
    fclose(fic);
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
    char ligne[200];
    FILE *fic = fopen("tableauDeBord.txt", "w");
    for (int i = 0 ; i < MAX_ELEMENTS ; i++){
        //printf("Civilisation::tableauDeBord => analyse de l'élément %d\n", i);
        element = getElement(i);
        if (element->getElementId() == -1) continue;
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

    snprintf(ligne, 200, "+-------------------------------------------------------------------------------------------------------------+\n");
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "|                                       T A B L E A U   D E   B O R D                                         |\n");
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "+-------------------------------------------------------------------------------------------------------------+\n");
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "|  constantes   MAX Elements = %5d / MAX Humains = %5d / MAX Entreprises = %5d                          |\n", MAX_ELEMENTS, MAX_HUMAIN, MAX_ENTREPRISES);
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "|               types Elements = INDEFINI/HUMAIN/ENTREPRISE                                                   |\n");
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "|               types Humain = HOMME/FEMME                                                                    |\n");
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "|               types status marital = CELIBATAIRE/MARIE/VEUF/DIVORCE                                         |\n");
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "|               types Entreprises = INCONNUE/COMMERCE/INDUSTRIE                                               |\n");
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "|  variables    NB Elements  = %5d / NB Humains  = %5d / NB Entreprises  = %5d                          |\n", _nbElements, getNbHumain(), getNbEntreprise());
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "+-----------------------------------++-----------------------------------++-----------------------------------+\n");
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "|               humains             ||            entreprises            ||          comptes banquaires       |\n");
    //printf("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n"); 
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "+-----------------+-----------------++-----------------+-----------------++-----------------+-----------------+\n");
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "| %15s | %15d || %15s | %15d || %15s | %15d |\n","nombre", _nbHumains, "nombre", _nbEntreprises, "nombre", _nbElements);
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "| %15s | %15d || %15s | %15d || %15s | %15d |\n","nb hommes", _nbHommes, "nb commerces", _nbCommerces, "total actifs", _totalActifs);
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "| %15s | %15d || %15s | %15d || %15s | %15d |\n","nb femmes", _nbFemmes, "nb industries", _nbIndustries, "total epargne", _totalEpargne);
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "| %15s | %15d || %15s | %15d || %15s | %15s |\n","nb celib", _nbCelibs, "nb autres", _nbAutresEntreprises, "", "");
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "| %15s | %15d || %15s | %15d || %15s | %15s |\n","nb marie", _nbMaries, "max employes", MAX_EMPLOYES, "", "");
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "| %15s | %15d || %15s | %15s || %15s | %15s |\n","nb divorce", _nbDivorces, "", "", "", "");
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "| %15s | %15d || %15s | %15s || %15s | %15s |\n","nb veuf", _nbVeufs, "", "", "", "");
    printf("%s", ligne); fputs(ligne, fic);
    snprintf(ligne, 200, "+-----------------+-----------------++-----------------+-----------------++-----------------+-----------------+\n");
    printf("%s", ligne); fputs(ligne, fic);
    fclose(fic);
    
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
        creeElementEntreprise(ACTIVITE_COMMERCE, (char *)"auBonPain", 10000, NULL);
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

            while((ligne[i] != ',' )  && (i < strlen(ligne))){
                //printf("%d : %c\n", i, ligne[i]);
                i++;
            } 
            i++;
            while((ligne[i] != ',' ) && (i < strlen(ligne))) nom[j++] = ligne[i++];
            nom[j] = '\0';
            j=0;
            i++;
            remove_extra_spaces(nom);

            strcmp(tmp, "");
            while((ligne[i] != ',' ) && (i < strlen(ligne))) tmp[j++] = ligne[i++];
            tmp[j] = '\0';
            j=0;
            capital = atoi(tmp);

            if (strncmp(ligne, "humain", 5) == 0){
                //log(LOG_INFO, "creation d'un humain sexe = %d, nom = %s, capital = %d", type, nom, capital);
                creeElementHumain(type, nom, capital);
            } else if (strncmp(ligne, "entreprise", 10) == 0){
                //log(LOG_INFO, "creation d'une entreprise sexe = %d, nom = %s, capital = %d", type, nom, capital);
                creeElementEntreprise(type, nom, capital, NULL);
            }
        }
    }
}

//-----------------------------------------
//
//          Civilisation::chargeConfiguration
//
//-----------------------------------------
Entreprise *Civilisation::dupliqueEntreprise(Entreprise *maisonMere){
    log(LOG_INFO, "duplication de l'entreprise %s", maisonMere->getNomEntreprise());
    return creeElementEntreprise(maisonMere->getActivite(), maisonMere->getNomEntreprise(), 
                            maisonMere->getCapitalInitial(), maisonMere);
}