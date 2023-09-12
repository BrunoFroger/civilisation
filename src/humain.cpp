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


char listeCommandesHumain[NB_COMMANDES_HUMAIN][30] = {"mortPossible", "chercheConjoint", "naissancePossible"};
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
    this->idEmployeur = -1;
}

//-----------------------------------------
//
//          Humain::evolution
//
//-----------------------------------------
void Humain::evolutionHumain(void){
    if (statusMarital != STATUS_MARITAL_DECES){
        log(LOG_INFO, "Humain::evolution => evolution de %s", this->nom);
        this->age++;
    }
}

//-----------------------------------------
//
//          Humain::getId
//
//-----------------------------------------
int Humain::getIdHumain(void){
    return id;
}

//-----------------------------------------
//
//          Humain::getNom
//
//-----------------------------------------
char *Humain::getNomHumain(void){
    return nom;
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
//          Humain::getSexe
//
//-----------------------------------------
int Humain::getSexe(void){
    return sexe;
}

//-----------------------------------------
//
//          Humain::getSexe
//
//-----------------------------------------
char Humain::getSexeChar(void){
    if (sexe == HOMME) return 'H';
    if (sexe == HOMME) return 'F';
    return 'X';
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
//          Humain::getAge
//
//-----------------------------------------
int Humain::getAge(void){
    return age;
}

//-----------------------------------------
//
//          Humain::getCelibataire
//
//-----------------------------------------
int Humain::getStatusMarital(void){
    return statusMarital;
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
//          Humain::getIntValue
//
//-----------------------------------------
int Humain::getIntValue(char *valeur){
    if (strcmp(valeur, "sexe") == 0){
        printf("Humain::getIntValue : variable %s = %d\n", valeur, sexe);
        return sexe;
    }
    if (strcmp(valeur, "age") == 0){
        printf("Humain::getIntValue : variable %s = %d\n", valeur, age);
        return age;
    }
    if (strcmp(valeur, "statusMarital") == 0){
        printf("Humain::getIntValue : variable %s = %d\n", valeur, statusMarital);
        return statusMarital;
    }
    printf("Humain::getIntValue : pas trouve d'équivalence pour %s\n", valeur);
    return -1;
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

//-----------------------------------------
//
//          Humain::mortPossible
//
//-----------------------------------------
void Humain::mortPossible(void){
    log(LOG_DEBUG,"Humain::mortPossible => TODO a tester");
    srand (time(NULL));
    if (age > 15){
        double rnd = rand() % age;
        log(LOG_DEBUG,"Humain::mortPossible =>  rnd = %3.0f\n", rnd);
        log(LOG_DEBUG,"Humain::mortPossible =>  age = %3d\n", age);
        log(LOG_DEBUG,"Humain::mortPossible =>  0.7 * age = %3.0f\n", (age * 0.7));
        if (rnd > (age * 0.7)){
            printf("mort de %s \n", nom);
            statusMarital = STATUS_MARITAL_DECES;
        }
        // transfert du capital aux heritiers
        // conjoints en premier et enfants ensuite
        // sinon perdu
        if (compteBancaireHumain->getEpargne() > 0) compteBancaireHumain->restitueEpargne(compteBancaireHumain->getEpargne());
        if (compteBancaireHumain->getSolde() > 0){
            if (conjoint != NULL){
                compteBancaireHumain->virement(conjoint->compteBancaireHumain, compteBancaireHumain->getSolde());
                return;
            }
            if (nbEnfants > 0){
                int nbHeritiers = 0;
                for (int i = 0 ; i < MAX_ENFANTS ; i++){
                    if (enfants[i] != NULL) nbHeritiers++;
                }
                int heritage = compteBancaireHumain->getSolde() / nbEnfants;
                for (int i = 0 ; i < MAX_ENFANTS ; i++){
                    if (enfants[i] != NULL){
                        compteBancaireHumain->virement(enfants[i]->compteBancaireHumain, heritage);
                    }
                }
            }
        }
    }
}

//-----------------------------------------
//
//          Humain::setConjoint
//
//-----------------------------------------
void Humain::setConjoint(Humain *pretendant){
    printf("Humain::setConjoint => TODO\n");
    conjoint = pretendant;
    
}

//-----------------------------------------
//
//          Humain::chercheConjoint
//
//-----------------------------------------
void Humain::chercheConjoint(void){
    printf("Humain::chercheConjoint => TODO\n");
    if ((statusMarital != STATUS_MARITAL_DECES) && (statusMarital != STATUS_MARITAL_DECES)){
        log(LOG_DEBUG, "Humain::chercheConjoint => recherche conjoint possible => à developper");
    }
    
}

//-----------------------------------------
//
//          Humain::naissancePossible
//
//-----------------------------------------
bool Humain::naissancePossible(void){
    printf("Humain::naissancePossible => TODO a tester\n");
    srand (time(NULL));
    double rnd = rand();
    if (statusMarital != STATUS_MARITAL_MARIE) return false;
    if ((age > 20) && (age < 50))
    if (rnd > 0.7){
        if (nbEnfants <= MAX_ENFANTS){
            printf("naissance pour %s\n", nom);
            return true;
        }
    }
    return false;
}

//-----------------------------------------
//
//          Humain::execCommandeHumain
//
//-----------------------------------------
bool Humain::execCommandeHumain(char *valeur){
    log(LOG_DEBUG,"Humain::execCommandeHumain <%s> : TODO", valeur);
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
char tmp[5000];
char *Humain::listeVariables(void){
    strcpy(tmp, "");
    strcat(tmp,"liste des variables Humain : ");
    for (int i = 0 ; i < NB_VARIABLE_HUMAIN ; i++){
        strcat(tmp, listeVariablesHumain[i]);
        strcat(tmp,", ");
    }
    strcat(tmp, "\n");

    strcat(tmp,"liste des commandes Humain : ");
    for (int i = 0 ; i < NB_COMMANDES_HUMAIN ; i++){
        strcat(tmp, listeCommandesHumain[i]);
        strcat(tmp,", ");
    }
    strcat(tmp, "\n");
    return tmp;
}