//-----------------------------------------
//
//          humain.cpp
//
//-----------------------------------------
#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include "../inc/humain.hpp"
#include "../inc/log.hpp"
#include "../inc/element.hpp"


char listeCommandesHumain[NB_COMMANDES_HUMAIN][30] = {"mortPossible", "chercheConjoint", "naissancePossible"};
char listeVariablesHumain[NB_VARIABLE_HUMAIN][20] = {"sexe", "nom", "age", "statusMarital"};


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
    log(LOG_DEBUG, "Humain::evolution => evolution de %s", this->nom);
    this->age++;
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

    log(LOG_DEBUG, "TODO : a finir de developper");
    for (int i = 0 ; i < NB_VARIABLE_HUMAIN ; i++){
        tmp = listeVariablesHumain[i];
        if (strcmp(tmp, valeur) == 0) {
            return true;
        } else {
            log(LOG_ERROR, "commande <%s> inconnue", valeur);
        }
    }
    //if (strcmp(valeur, "sexe") == 0) return true;
    //if (strcmp(valeur, "nom") == 0) return true;
    //if (strcmp(valeur, "age") == 0) return true;
    //if (strcmp(valeur, "celibataire") == 0) return true;
    //printf("isVariable : return false \n");
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
//          calculExpression
//
//-----------------------------------------
int Humain::calculExpression(char *data1, char op, char *data2){
    int val1;
    int val2;
    int res = false;
    printf("Humain::calculExpression => debut : calcul de <%s> <%c> <%s>\n", data1, op, data2);
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
    printf("Humain::calculExpression => apres evaluation : calcul de <%d> <%c> <%d>\n", val1, op, val2);
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
    printf("Humain::calculExpression => resultat : <%d> <%c> <%d> = <%d>\n", val1, op, val2, res);
    return res;
}

//-----------------------------------------
//
//          Humain::testSiCommandeValide
//
//-----------------------------------------
bool Humain::testSiCommandeValide(char *valeur){
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
//          Humain::testSiListeCommandeValide
//
//-----------------------------------------
bool Humain::testSiListeCommandeValide(char *valeur){
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
            if (!testSiCommandeValide(buffer)){
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
    printf("Humain::mortPossible => TODO a finir\n");
    double rnd = rand() % 100;
    printf(" rnd = %3.0f\n", rnd);
    rnd *= age;
    printf(" rnd * age = %3.0f\n", rnd);
    if (rnd > 70){
        printf("mort de %s \n", nom);
        statusMarital = STATUS_MARITAL_DECES;
    }
}

//-----------------------------------------
//
//          Humain::chercheConjoint
//
//-----------------------------------------
void Humain::chercheConjoint(void){
    printf("Humain::ecole => TODO\n");
}

//-----------------------------------------
//
//          Humain::naissancePossible
//
//-----------------------------------------
void Humain::naissancePossible(void){
    printf("Humain::naissancePossible => TODO a finir\n");
    double rnd = rand();
    if ((age > 20) && (age < 50))
    if (rnd > 0.7){
        printf("naissance pour %s\n", nom);
    }
}

//-----------------------------------------
//
//          Humain::execCommande
//
//-----------------------------------------
bool Humain::execCommande(char *valeur){
    log(LOG_DEBUG,"Humain::execCommande <%s> : TODO", valeur);
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
