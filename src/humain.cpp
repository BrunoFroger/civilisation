//-----------------------------------------
//
//          humain.cpp
//
//-----------------------------------------
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h> 

#include "../inc/humain.hpp"
#include "../inc/log.hpp"
#include "../inc/element.hpp"
#include "../inc/civilisation.hpp"


char listeCommandesHumain[NB_COMMANDES_HUMAIN][30] = {"mortPossible", "chercheConjoint", "naissancePossible", "achat"};
char listeVariablesHumain[NB_VARIABLE_HUMAIN][20] = {"sexe", "nom", "age", "statusMarital", "nbEnfants"};


//-----------------------------------------
//
//          Humain::Humain
//
//-----------------------------------------
Humain::Humain(){
    this->id = -1;
    this->sexe = -1;
    strcpy(this->nom , "");
    this->age = -1;
}

//-----------------------------------------
//
//          Humain::Humain
//
//-----------------------------------------
Humain::Humain(int id, int sexe, char *nom, int capitalInitial){
    /*
    //log(LOG_INFO, "Humain::initHumain : debut");
    */
   initHumain(id, sexe, nom, capitalInitial);
    //log(LOG_INFO, "Humain::initHumain : fin");
}

//-----------------------------------------
//
//          Humain::acheteProduit
//
//-----------------------------------------
void Humain::acheteProduit(Entreprise *entreprise, int quantite){
    log(LOG_INFO, "Humain::acheteProduit : %s achete %d produits a %s", this->nom, quantite, entreprise->getNomEntreprise());
    entreprise->creeCommande(this, quantite);
}

//-----------------------------------------
//
//          Humain::valideAchatProduit
//
//-----------------------------------------
void Humain::valideAchatProduit(Entreprise *entreprise, int montant){
    log(LOG_INFO, "Humain::valideAchatProduit : produits recu, on paye %d a %s", montant, entreprise->getNomEntreprise());
    compteBancaireHumain->virement(entreprise->compteBancaireEntreprise, montant);
}

//-----------------------------------------
//
//          Humain::ajouteParents
//
//-----------------------------------------
void Humain::ajouteParents(Humain *pere, Humain *mere){
    this->pere = pere;
    this->mere = mere;
}

//-----------------------------------------
//
//          Humain::ajouteEnfant
//
//-----------------------------------------
void Humain::ajouteEnfant(Humain *enfant){
    for (int i = 0 ; i < MAX_ENFANTS ; i++){
        if (enfants[i] == NULL){
            enfants[i] = enfant;
            nbEnfants++;
            return;
        }
    }
}

//-----------------------------------------
//
//          calculExpression
//
//-----------------------------------------
int Humain::calculExpression(char *data1, char op, char *data2){
    int val1;
    int val2;
    int res = false;
    log(LOG_DEBUG, "Humain::calculExpression => debut : calcul de <%s> <%c> <%s>\n", data1, op, data2);
    if (Humain::isVariable(data1)){
        val1 = getIntValue(data1);
        printf("data1 est une variable : <%s> => <%d>\n", data1, val1);
    } else {
        val1 = atoi(data1);
    }
    if (Humain::isVariable(data2)){
        val2 = getIntValue(data2);
        printf("data2 est une variable : <%s> => <%d>\n", data2, val2);
    } else {
        val2 = atoi(data2);
    }
    log(LOG_DEBUG, "Humain::calculExpression => apres evaluation : calcul de <%d> <%c> <%d>\n", val1, op, val2);
    switch(op){
        case '+' : 
            res = val1 + val2;
            break;
        case '-' : 
            res = val1 - val2;
            break;
        case '*' : 
            res = val1 * val2;
            break;
        case '/' : 
            res = val1 / val2;
            break;
    }
    log(LOG_DEBUG, "Humain::calculExpression => resultat : <%d> <%c> <%d> = <%d>\n", val1, op, val2, res);
    return res;
}

//-----------------------------------------
//
//          Humain::chercheConjoint
//
//-----------------------------------------
bool Humain::chercheConjoint(void){
    //log(LOG_INFO,"Humain::chercheConjoint => TODO");
    if ((statusMarital != STATUS_MARITAL_DECES) && 
        (statusMarital != STATUS_MARITAL_MARIE)){
        //log(LOG_INFO, "Humain::chercheConjoint => recherche conjoint possible => à developper");
        Humain *conjoint, *homme, *femme;
        if (sexe == HOMME){
            homme = this;
            conjoint = Civilisation::getConjoint(FEMME);
            femme = conjoint;
        } 
        else{
            conjoint = Civilisation::getConjoint(HOMME);
            homme = conjoint;
            femme = this;
        } 
        if (conjoint != NULL){
            log(LOG_INFO,"Humain::chercheConjoint => %s trouve %s comme conjoint ", this->nom, conjoint->getNomHumain());
            mariage(homme, femme);
            return true;
        } 
    }
    return false;
}

//-----------------------------------------
//
//          Humain::evolution
//
//-----------------------------------------
void Humain::evolutionHumain(void){
    if (statusMarital != STATUS_MARITAL_DECES){
        this->age++;
        log(LOG_INFO, "Humain::evolution => evolution de '%s' : age = %d", this->nom, this->age);
    }
}

//-----------------------------------------
//
//          Humain::getAge
//
//-----------------------------------------
int Humain::getAge(void){
    return age;
}

//-----------------------------------------
//
//          Humain::getCharValue
//
//-----------------------------------------
char *Humain::getCharValue(char *valeur){
    if (strcmp(valeur, "nom") == 0) return nom;
    return NULL;
}

//-----------------------------------------
//
//          Humain::getEmployeur
//
//-----------------------------------------
Entreprise *Humain::getEmployeur(void){
    return employeur;
}

//-----------------------------------------
//
//          Humain::getIdHumain
//
//-----------------------------------------
int Humain::getIdHumain(void){
    return id;
}

//-----------------------------------------
//
//          Humain::getIntValue
//
//-----------------------------------------
int Humain::getIntValue(char *valeur){
    if (strcmp(valeur, "sexe") == 0){
        //printf("Humain::getIntValue : variable %s = %d\n", valeur, sexe);
        return sexe;
    }
    if (strcmp(valeur, "age") == 0){
        //printf("Humain::getIntValue : variable %s = %d\n", valeur, age);
        return age;
    }
    if (strcmp(valeur, "statusMarital") == 0){
        //printf("Humain::getIntValue : variable %s = %d\n", valeur, statusMarital);
        return statusMarital;
    }
    printf("Humain::getIntValue : pas trouve d'équivalence pour %s\n", valeur);
    return -1;
}

//-----------------------------------------
//
//          Humain::getPere
//
//-----------------------------------------
int Humain::getPere(void){
    //log(LOG_DEBUG,"Humain::getPere : TODO");
    if (pere == NULL) return -1;
    return pere->getIdHumain();
}

//-----------------------------------------
//
//          Humain::getMere
//
//-----------------------------------------
int Humain::getMere(void){
    if (mere == NULL) return -1;
    return mere->getIdHumain();
}

//-----------------------------------------
//
//          Humain::getConjoint
//
//-----------------------------------------
int Humain::getConjoint(void){
    if (conjoint == NULL) return -1;
    return conjoint->getIdHumain();
}

//-----------------------------------------
//
//          Humain::getNbEnfants
//
//-----------------------------------------
int Humain::getNbEnfants(void){
    return nbEnfants;
}

//-----------------------------------------
//
//          Humain::getNomHumain
//
//-----------------------------------------
char *Humain::getNomHumain(void){
    return nom;
}

//-----------------------------------------
//
//          Humain::getSexe
//
//-----------------------------------------
int Humain::getSexe(void){
    return sexe;
}

//-----------------------------------------
//
//          Humain::getSexeChar
//
//-----------------------------------------
char Humain::getSexeChar(void){
    if (sexe == HOMME) return 'H';
    if (sexe == FEMME) return 'F';
    return 'X';
}

//-----------------------------------------
//
//          Humain::getStatusMarital
//
//-----------------------------------------
int Humain::getStatusMarital(void){
    return statusMarital;
}

//-----------------------------------------
//
//          Humain::initHumain
//
//-----------------------------------------
void Humain::initHumain(int id, int sexe, char *nom, int capitalInitial){
    log(LOG_DEBUG, "Humain::initHumain : debut");
    this->id = id;
    this->sexe = sexe;
    strcpy(this->nom ,nom);
    this->age = 0;
    this->statusMarital = STATUS_MARITAL_CELIB;
    this->compteBancaireHumain = new CompteBancaire(capitalInitial);
    this->employeur = NULL;
    this->pere = NULL;
    this->mere = NULL;
}

//-----------------------------------------
//
//          Humain::isVariable
//
//-----------------------------------------
bool Humain::isVariable(char *valeur){
    //printf("isvariable : test de la variable %s\n", valeur);
    char *tmp;

    //log(LOG_DEBUG, "TODO : a finir de developper");
    for (int i = 0 ; i < NB_VARIABLE_HUMAIN ; i++){
        tmp = listeVariablesHumain[i];
        if (strcmp(tmp, valeur) == 0) {
            return true;
        } else {
            //log(LOG_ERROR, "commande <%s> inconnue", valeur);
        }
    }
    return false;
}

//-----------------------------------------
//
//          evalueExpression
//
//-----------------------------------------
bool Humain::evalueExpressionHumain(char *expression){
    int val1;
    int val2;
    //bool res = false;
    char data1[30], op[5], data2[30];
    int i = 0, j = 0;
    log(LOG_DEBUG, "Humain::evalueExpressionHumain => debut : calcul de '%s'", expression);

    // decomposition de l'expression
    while ((expression[i] != ' ') && (i < strlen(expression))){
        data1[j++] = expression[i++];
        data1[j] = '\0';
    } 
    j=0;
    if (i >= strlen(expression)) return false;
    while((expression[i] == ' ') && (i < strlen(expression))) i++;
    while ((expression[i] != ' ') && (i < strlen(expression))){
        putchar(expression[i]);
        op[j++] = expression[i++];
        op[j] = '\0';
    } 
    j=0;
    if (i >= strlen(expression)) return false;
    while((expression[i] == ' ') && (i < strlen(expression))) i++;
    while ((expression[i] != ' ') && (i < strlen(expression))){
        data2[j++] = expression[i++];
        data2[j] = '\0';
    } 
    log(LOG_DEBUG, "Humain::evalueExpressionHumain => resultat decomposition : '%s' '%s' '%s'", data1, op, data2);

    if (Humain::isVariable(data1)){
        val1 = getIntValue(data1);
        log(LOG_DEBUG, "Humain::evalueExpressionHumain => data1 est une variable : '%s' => '%d'\n", data1, val1);
    } else {
        val1 = atoi(data1);
    }
    if (Humain::isVariable(data2)){
        val2 = getIntValue(data2);
        log(LOG_DEBUG, "Humain::evalueExpressionHumain => data2 est une variable : '%s' => '%d'\n", data2, val2);
    } else {
        val2 = atoi(data2);
    }
    log(LOG_DEBUG, "Humain::evalueExpressionHumain => apres evaluation : calcul de '%d' '%s' '%d'\n", val1, op, val2);
    return evaluationExpressionInt(val1, op, val2);
    //return res;
}

//-----------------------------------------
//
//          Humain::execCommandeHumain
//
//-----------------------------------------
bool Humain::execCommandeHumain(char *valeur){
    log(LOG_INFO,"Humain::execCommandeHumain <%s> : TODO", valeur);
    for (int i = 0 ; i < NB_COMMANDES_HUMAIN ; i++){
        if (strcmp(listeCommandesHumain[i], valeur) == 0){
            switch(i){ 
                case 0: // mortPossible
                    mortPossible();
                    return true;
                    break;
                case 1: // chercheConjoint
                    chercheConjoint();
                    return true;
                    break;
                case 2: // naissancePossible
                    naissancePossible();
                    return true;
                    break;
            }
            break;
        } 
    }
    log(LOG_ERROR, "commande <%s> inconnue", valeur);

    return false;
}

//-----------------------------------------
//
//          Humain::listeHumain
//
//-----------------------------------------
void Humain::listeHumain(void){
    log(LOG_DEBUG,"Humain::listeHumain : TODO");
    char tmp[30];
    printf("+-------------------------------------------------+\n");
    printf("|  donnees humain (id = %5d)                    |\n", this->id);
    printf("+---------------+---------------------------------+\n");
    printf("| donnee        |     valeur                      |\n");
    printf("+---------------+---------------------------------+\n");
    printf("| nom           |     %25s   |\n", this->nom);
    if (this->sexe == HOMME) strcpy(tmp, "homme"); else strcpy(tmp, "femme");
    printf("| sexe          |     %25s   |\n", tmp);
    printf("| age           |               %15d   |\n", this->age);
    switch(statusMarital){
        case STATUS_MARITAL_CELIB:
            strcpy(tmp,"celibataire");
            break;
        case STATUS_MARITAL_DIVOR:
            strcpy(tmp,"divorce");
            break;
        case STATUS_MARITAL_MARIE:
            strcpy(tmp,"marie");
            break;
        case STATUS_MARITAL_VEUF:
            strcpy(tmp,"veuf");
            break;
        default:
            strcpy(tmp,"inconnu");
    }
    printf("| status marital|     %25s   |\n", tmp);
    printf("| cpt bancaire  |               %15d   |\n", this->compteBancaireHumain->getSolde());
    printf("| epargne       |               %15d   |\n", this->compteBancaireHumain->getEpargne());
    printf("+---------------+---------------------------------+\n");
}

//-----------------------------------------
//
//          Humain::listeVariables
//
//-----------------------------------------
char tmpDataHumain[5000];
char *Humain::listeVariables(void){
    strcpy(tmpDataHumain, "");
    strcat(tmpDataHumain,"liste des variables Humain : ");
    for (int i = 0 ; i < NB_VARIABLE_HUMAIN ; i++){
        strcat(tmpDataHumain, listeVariablesHumain[i]);
        strcat(tmpDataHumain,", ");
    }
    strcat(tmpDataHumain, "\n");

    strcat(tmpDataHumain,"liste des commandes Humain : ");
    for (int i = 0 ; i < NB_COMMANDES_HUMAIN ; i++){
        strcat(tmpDataHumain, listeCommandesHumain[i]);
        strcat(tmpDataHumain,", ");
    }
    strcat(tmpDataHumain, "\n");
    return tmpDataHumain;
}

//-----------------------------------------
//
//          Humain::mortPossible
//
//-----------------------------------------
void Humain::mortPossible(void){
    log(LOG_DEBUG,"Humain::mortPossible => TODO a tester");
    srand (time(NULL));
    int ageMoyenDeces = 75;
    if (age > 15){
        int rnd = int(rand() % 20);
        log(LOG_DEBUG,"Humain::mortPossible =>  rnd           = %3d", rnd);
        log(LOG_DEBUG,"Humain::mortPossible =>  age           = %3d", age);
        log(LOG_DEBUG,"Humain::mortPossible =>  age + rnd     = %3d", age + rnd);
        log(LOG_DEBUG,"Humain::mortPossible =>  ageMoyenDeces = %3d", ageMoyenDeces);
        if (age > (ageMoyenDeces + rnd)){
            log(LOG_INFO, "===========================");
            log(LOG_INFO, "     deces de %s ", nom);
            log(LOG_INFO, "===========================");
            statusMarital = STATUS_MARITAL_DECES;
            // transfert du capital aux heritiers
            // conjoints en premier et enfants ensuite
            // sinon perdu
            if (compteBancaireHumain->getEpargne() > 0) compteBancaireHumain->restitueEpargne(compteBancaireHumain->getEpargne());
            log(LOG_INFO, "transfert du capital %d aux heritiers", compteBancaireHumain->getSolde());
            int heritage = compteBancaireHumain->getSolde();
            if (heritage > 0){
                if (conjoint != NULL){
                    log(LOG_INFO, "transfert du capital de (%s) au son conjoint (%s) => %d", this->nom, this->conjoint->getNomHumain(), compteBancaireHumain->getSolde());
                    compteBancaireHumain->virement(conjoint->compteBancaireHumain, compteBancaireHumain->getSolde());
                    conjoint->setStatusMarital(STATUS_MARITAL_VEUF);
                    conjoint->setConjoint(NULL);
                    return;
                }
                if (nbEnfants > 0){
                    int nbHeritiers = 0;
                    for (int i = 0 ; i < MAX_ENFANTS ; i++){
                        if (enfants[i] != NULL) nbHeritiers++;
                    }
                    int partHeritage = compteBancaireHumain->getSolde() / nbEnfants;
                    log(LOG_INFO, "%d heritiers se partagent %d soit %d chacun", nbHeritiers, heritage, partHeritage);
                    for (int i = 0 ; i < MAX_ENFANTS ; i++){
                        if (enfants[i] != NULL){
                            log(LOG_INFO, "transfert de %d du capital a %s", partHeritage, enfants[i]->getNomHumain());
                            compteBancaireHumain->virement(enfants[i]->compteBancaireHumain, partHeritage);
                        }
                    }
                }
            }
        }
    }
}

//-----------------------------------------
//
//          Humain::naissancePossible
//
//-----------------------------------------
bool Humain::naissancePossible(void){
    log(LOG_INFO, "Humain::naissancePossible => TODO a tester");
    srand (time(NULL));
    double rnd = rand() * 1;
    if (statusMarital != STATUS_MARITAL_MARIE) return false;
    if ((age > 20) && (age < 50))
    if (rnd > 0.7){
        if (nbEnfants < MAX_ENFANTS){
            if (conjoint != NULL){
                log(LOG_INFO, "Humain::naissancePossible => naissance pour %s et %s", nom, conjoint->getNomHumain());
                if (sexe == HOMME){
                    naissance(this, conjoint);
                } else {
                    naissance(conjoint, this);
                }
                return true;
            }
        }
    }
    return false;
}

//-----------------------------------------
//
//          Humain::setConjoint
//
//-----------------------------------------
void Humain::setConjoint(Humain *pretendant){
    log(LOG_INFO, "Humain::setConjoint => TODO");
    conjoint = pretendant;
    statusMarital = STATUS_MARITAL_MARIE;
}

//-----------------------------------------
//
//          Humain::setEmployeur
//
//-----------------------------------------
void Humain::setEmployeur(Entreprise *entreprise){
    employeur = entreprise;
}

//-----------------------------------------
//
//          Humain::setNom
//
//-----------------------------------------
void Humain::setNom(char *nom){
    strcpy(this->nom, nom);
}

//-----------------------------------------
//
//          Humain::setSexe
//
//-----------------------------------------
void Humain::setSexe(int sexe){
    this->sexe = sexe;
}

//-----------------------------------------
//
//          Humain::setStatusMarital
//
//-----------------------------------------
void Humain::setStatusMarital(int status){
    statusMarital = status;
}

//-----------------------------------------
//
//          Humain::testSiCommandeValideHumain
//
//-----------------------------------------
bool Humain::testSiCommandeValideHumain(char *valeur){
    //printf("test si commande '%s' valide\n", valeur);
    for (int i = 0 ; i < NB_COMMANDES_HUMAIN ; i++){
        //printf("comparaison avec %s : ", listeCommandesHumain[i]);
        if (strcmp(valeur, listeCommandesHumain[i]) == 0) {
            //printf("OK\n");
            return true;
        } else {
            //printf("NOK\n");
        }
    }
    return false;
}

//-----------------------------------------
//
//          Humain::testSiListeCommandeValideHumain
//
//-----------------------------------------
bool Humain::testSiListeCommandeValideHumain(char *valeur){
    char *tmp;
    tmp = &valeur[0];
    char buffer[50];
    int i;
    while (tmp[0] != '\0'){
        i=0;
        strcpy(buffer,"");
        while (*tmp == ' ') tmp++;  // suppression des blancs au debut
        if (strlen(tmp) == 0) return true;
        while (*tmp != ' '){
            buffer[i++] = *tmp++;
            buffer[i] = '\0';
        }
        if (strlen(buffer) != 0){
            if (!testSiCommandeValideHumain(buffer)){
                log(LOG_ERROR, "commande %s inconnue", buffer);
                return false;
            }
        }
    }
    return true;
}