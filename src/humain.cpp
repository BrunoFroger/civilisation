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
#include "../inc/tools.hpp"

//-----------------------------------------
//
//          Humain::Humain
//
//-----------------------------------------
void Humain::init(long id, int sexe, const char *nom){
    //log(LOG_INFO, "Humain::init : debut");
    /*if (sexe == 0){
        log(LOG_INFO, (char *)"Creation d'un homme (%s) id=%ld", nom, id);
    } else if (sexe == 1){
        log(LOG_INFO, (char *)"Creation d'une femme (%s) id=%ld", nom, id);
    } else {
        log(LOG_INFO, (char *)"sexe indefini id = %d", id);
    }*/
    this->id = id;
    this->sexe = sexe;
    strcpy(this->nom ,nom);
    this->age = 0;
    this->celibataire = true;
    //log(LOG_INFO, "Humain::init : fin");
}

//-----------------------------------------
//
//          Humain::evolution
//
//-----------------------------------------
void Humain::evolution(void){
    log(LOG_INFO, "evolution de %s", this->nom);
    this->age++;
    execScript();
}

//-----------------------------------------
//
//          Humain::getId
//
//-----------------------------------------
long Humain::getId(void){
    return id;
}

//-----------------------------------------
//
//          Humain::getNom
//
//-----------------------------------------
char *Humain::getNom(void){
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
//          Humain::getSexe
//
//-----------------------------------------
int Humain::getAge(void){
    return age;
}

//-----------------------------------------
//
//          Humain::getSexe
//
//-----------------------------------------
bool Humain::getCelibataire(void){
    return celibataire;
}

//-----------------------------------------
//
//          Humain::isVariable
//
//-----------------------------------------
bool Humain::isVariable(char *valeur){
    //printf("isvariable : test de la variable %s\n", valeur);
    if (strcmp(valeur, "sexe") == 0) return true;
    if (strcmp(valeur, "nom") == 0) return true;
    if (strcmp(valeur, "age") == 0) return true;
    if (strcmp(valeur, "celibataire") == 0) return true;
    //printf("isVariable : return false \n");
    return false;
}

//-----------------------------------------
//
//          Humain::getIntValue
//
//-----------------------------------------
int Humain::getIntValue(char *valeur){
    if (strcmp(valeur, "sexe") == 0) return sexe;
    if (strcmp(valeur, "celibataire") == 0) return celibataire;
    return -1;
}

//-----------------------------------------
//
//          Humain::getLongValue
//
//-----------------------------------------
long Humain::getLongValue(char *valeur){
    if (strcmp(valeur, "age") == 0) return age;
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
//          Humain::testCommandeSiVraiValide
//
//-----------------------------------------
bool Humain::testCommandeSiVraiValide(char *valeur){
    if (strcmp(valeur, "mort") == 0) return true;
    if (strcmp(valeur, "chercheConjoint") == 0) return true;
    return false;
}

//-----------------------------------------
//
//          Humain::execScript
//
//-----------------------------------------
bool Humain::execScript(void){
    FILE *fic;
    int numLigne=0;
    char ligne[100];
    const char filename[30] = "scripts/humain.scr";

    fic = fopen(filename, "r");
    if (fic == NULL){
        log(LOG_ERROR, "Humain::execScript => impossible d'ouvrir le fichier script ");
        return false;
    }
    //printf("lecture du fichier '%s'\n", filename);
    while (!feof(fic)){
        fgets(ligne, 100, fic);
        numLigne++;
        ligne[strlen(ligne) - 1] = '\0';
        char *tmp = &ligne[0];
        while (tmp[0] == ' ') tmp++;
        //printf("ligne a analyser = '%s'\n", tmp);
        if (tmp[0] == '#') continue;    // commentaire on passe

        if (strlen(tmp) == 0) continue;    // ligne vide on passe
        
        //printf("ligne a analyser = '%s'\n", tmp);
        if (strncmp(tmp, "si", 2) == 0){
            //printf("Analyse d'une ligne contenant un 'si'\n");
            structIf resultat;
            if (!decomposeSi(tmp, &resultat)){
                log(LOG_ERROR, "erreur de syntaxe dans le fichier '%s' a la ligne %d (%s)\n", filename, numLigne, tmp);
                return false;
            } else {
                // traitement de la ligne si
                if (!testCommandeSiVraiValide(resultat.commandeSiVrai)){
                    log(LOG_ERROR, "instruction '%s' inconnue\n", resultat.commandeSiVrai);
                    return false;
                }
                int val1, val2;
                if (isVariable(resultat.dataOrigine)){
                    val1 = getIntValue(resultat.dataOrigine);
                } else {
                    val1 = atoi(resultat.dataOrigine);
                }
                if (isVariable(resultat.dataReference)){
                    val2 = getIntValue(resultat.dataReference);
                } else {
                    val2 = atoi(resultat.dataReference);
                }
                evaluation(val1, resultat.operateurTest, val2);
            } 
        } else {
            log(LOG_ERROR, "instruction inconnue dans la ligne '%s'\n", ligne);
            return false;
        }
    }
    //printf("\n");
    return true;
}
