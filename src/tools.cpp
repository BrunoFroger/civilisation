//-----------------------------------------
//
//          tools.cpp
//
//-----------------------------------------

#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>

#include "../inc/element.hpp"
#include "../inc/log.hpp"
#include "../inc/civilisation.hpp"
#include "../inc/humain.hpp"

extern Civilisation civilisation;

//-----------------------------------------
//
//          getSexeAleatoire
//
//-----------------------------------------
int getSexeAleatoire(void){
    log(LOG_DEBUG, "Tools.cpp getSexeAleatoire => debut (a affiner)");
    if (civilisation.getNbHommes() > civilisation.getNbFemmes())
        return FEMME;
    else
        return HOMME;
}

//-----------------------------------------
//
//          getPrenomAleatoire
//
//-----------------------------------------
char tmpPrenom[20];
int idxPrenom;
char *getPrenomAleatoire(int sexe){
    log(LOG_DEBUG, "Tools.cpp getPrenomAleatoire => debut (a affiner)");
    if (sexe == HOMME)
        sprintf(tmpPrenom, "albert_%d", idxPrenom);
    else
        sprintf(tmpPrenom, "alice_%d", idxPrenom);
    idxPrenom++;
    return tmpPrenom;
}

//-----------------------------------------
//
//           naissance
//
//-----------------------------------------
int naissance(Humain *pere, Humain *mere){
    log(LOG_INFO, "tools naissance => TODO");
    //Humain *enfant = NULL;
    Element *tmpElement;
    for (int i = 0 ; i < MAX_HUMAIN ; i++){
        tmpElement = civilisation.getElement(i);
        if (tmpElement->getElementId() == -1){
            if (tmpElement->getNbEnfants() < MAX_ENFANTS){
                int sexe = getSexeAleatoire();           // TODO genere aleatoirement HOMME ou FEMME
                char *prenom = getPrenomAleatoire(sexe);   // Generer prenom depuis liste a definir
                tmpElement = civilisation.creeElementHumain(sexe, prenom, 1000);
                log(LOG_INFO, "tools naissance => %s et %s ont %s comme enfant", pere->getNomHumain(), mere->getNomHumain(), tmpElement->getNomHumain());
                pere->ajouteEnfant(tmpElement);
                mere->ajouteEnfant(tmpElement);
                tmpElement->ajouteParents(pere, mere);
                return tmpElement->getElementId();
            }
        }
    }
    log(LOG_DEBUG, "tools naissance => le tableau des humains est plein");
    return -1;
}

//-----------------------------------------
//
//           mariage
//
//-----------------------------------------
bool mariage(Humain *homme, Humain *femme){
    log(LOG_DEBUG, "tools mariage => TODO");
    if ((homme != NULL && (femme != NULL))){
        homme->setConjoint(femme);
        femme->setConjoint(homme);
        return true;
    }
    return false;
}


//-----------------------------------------
//
//          remove_extra_spaces
//
//-----------------------------------------
void remove_extra_spaces(char* str) {
    int i, j;
    int len = strlen(str);
    for (i = 0, j = 0; i < len; i++) {
        //if (str[i] == '\n') str[i] =' ';
        if (str[i] != ' ' || (i > 0 && str[i - 1] != ' ')) {
            str[j++] = str[i];
        }
    }
    while (str[j - 1] == ' '){
        str[j - 1] = '\0';
        j--;
    }
    str[j] = '\0';
}

//-----------------------------------------
//
//          evaluationExpressionInt
//
//-----------------------------------------
bool evaluationExpressionInt(int data1, char *test, int data2){
    //printf("test '='\n");
    if (strcmp(test, "=") == 0){
        return (data1==data2);
    } 
    //printf("test '!='\n");
    if (strcmp(test, "!=") == 0){
        return !(data1==data2);
    }   
    if (strcmp(test, ">") == 0){
        return (data1>data2);
    } 
    if (strcmp(test, "<") == 0){
        return (data1<data2);
    } 
    if (strcmp(test, ">=") == 0){
        return (data1 >= data2);
    } 
    if (strcmp(test, "<=") == 0){
        return (data1 <= data2);
    } 
    //printf("aucun test valide\n");
    return false;
}

//-----------------------------------------
//
//          evaluationExpressionChar
//
//-----------------------------------------
bool evaluationExpressionChar(char *data1, char *test, char *data2){
    //printf("test '='\n");
    if (strcmp(test, "=") == 0){
        return (strcmp((const char*)data1, (const char*)data2) == 0);
    } 
    //printf("test '!='\n");
    if (strcmp(test, "!=") == 0){
        return !(strcmp((const char*)data1, (const char*)data2) == 0);
    } 
    if (strcmp(test, ">") == 0){
        return (strcmp((const char*)data1, (const char*)data2) > 0);
    } 
    if (strcmp(test, "<") == 0){
        return (strcmp((const char*)data1, (const char*)data2) < 0);
    } 
    if (strcmp(test, ">=") == 0){
        return (strcmp((const char*)data1, (const char*)data2) >= 0);
    } 
    if (strcmp(test, "<=") == 0){
        return (strcmp((const char*)data1, (const char*)data2) <= 0);
    } 
    //printf("aucun test valide\n");
    return false;
}

//-----------------------------------------
//
//          decomposeIf
//
//-----------------------------------------
bool decomposeSi(char *ligne, structSi *resultat){

    int i = 0;
    char *tmp;
    char buffer[200];
    log(LOG_DEBUG, "Tools.cpp => -----------------------------");
    log(LOG_DEBUG, "Tools.cpp => decomposeSi => debut");

    strcpy(resultat->expression,"");
    strcpy(resultat->ListeCommandeSiVrai,"");
    strcpy(resultat->ListeCommandeSiFaux,"");
    if (strncmp(ligne, "si", 2) != 0){
        return false;
    } else {
        if ( ligne[strlen(ligne) - 1] == '\n'){ // suppr RC en fin de ligne
            //printf("ligne avec retour chariot on le supprime\n");
            ligne[strlen(ligne) - 1] = '\0';
        }
        tmp = &ligne[2];
        /*
        // recherche si 'finsi' dans la ligne, sinon, on concatene avec les lignes suivantes
        while (strstr(ligne, "finsi") == NULL){
            // le finsi n'est pas sur la ligne courante, on lit les suivantes et on concatene la chaine 
            char ligneSupp[50];
            fgets(ligneSupp, 50, fic);
            if (feof(fic)){
                log(LOG_ERROR, "finsi non trouve");
                return false;
            }
            ligneSupp[strlen(ligneSupp) - 1] = '\0';
            strcat(ligne, " ");
            strcat(ligne, ligneSupp);
            //printf("ligne supplementaire lue : '%s'\n", ligne);
        }*/
        //printf("ligne complete de si a traiter : '%s'\n", ligne);

        // recuperation de l'expresion
        i=0;
        while (*tmp == ' ') tmp++;  // suppression des blancs avant chaque item
        while (strncmp(tmp, "alors", 5) != 0){
            if (tmp[0] == '\0') {
                log(LOG_ERROR, "manque alors dans l'instruction si '%s'", tmp);
                return false;
            }
            resultat->expression[i++] = *tmp++;
            resultat->expression[i] = '\0';
        }
        //printf("expression = '%s'\n", resultat->expression);

        // recherche du alors
        i = 0;
        while (*tmp == ' ') tmp++;  // suppression des blancs avant chaque item
        while (*tmp != ' '){
            buffer[i++] = *tmp++;
            buffer[i] = '\0';
        }
        //printf("recherche alors = '%s'\n", buffer);
        if (strcmp(buffer, "alors") != 0){
            log(LOG_ERROR,"manque alors dans instruction si '%s'", buffer);
            return false;
        }

        // recherche du sinon ou finsi (construction liste de commande si vrai)
        i = 0;
        while (*tmp == ' ') tmp++;  // suppression des blancs avant chaque item
        //printf("tmp avant recherche liste commandes si vrai = '%s'\n", tmp);
        while ((strncmp(tmp, "sinon", 4) != 0) && (strncmp(tmp, "finsi", 5) != 0)){
            if (tmp[0] == '\0'){
                // on est arrive en fin de chaine sans avoir trouve sinon ou finsi
                log(LOG_ERROR, "finsi non trouve");
                //printf("Element::decomposeSi => fin 184\n");
                return false;
            }
                resultat->ListeCommandeSiVrai[i++] = *tmp++;
                resultat->ListeCommandeSiVrai[i] = '\0';
        }
        //printf("listeCommandeSiVrai = '%s'\n", resultat->ListeCommandeSiVrai);
        if (strncmp(tmp, "finsi", 5) == 0){
            // fin de traitement du si
            remove_extra_spaces(resultat->expression);
            remove_extra_spaces(resultat->ListeCommandeSiVrai);
            remove_extra_spaces(resultat->ListeCommandeSiFaux);
            log(LOG_DEBUG, "Tools.cpp => expression          = '%s'", resultat->expression);
            log(LOG_DEBUG, "Tools.cpp => ListeCommandeSiVrai = '%s'", resultat->ListeCommandeSiVrai);
            log(LOG_DEBUG, "Tools.cpp => ListeCommandeSiFaux = '%s'", resultat->ListeCommandeSiFaux);
            log(LOG_DEBUG, "Tools.cpp => fin 181\n");
            return true;
        }

        // recherche du sinon
        i = 0;
        while (*tmp == ' ') tmp++;  // suppression des blancs avant chaque item
        while (*tmp != ' '){
            buffer[i++] = *tmp++;
            buffer[i] = '\0';
        }
        //printf("recherche sinon = '%s'\n", buffer);
        if (strcmp(buffer, "sinon") != 0){
            log(LOG_ERROR,"manque sinon dans instruction si");
            return false;
        }
        // on continue avec les commandes si faux
        i = 0;
        while (*tmp == ' ') tmp++;  // suppression des blancs avant chaque item
        while (strncmp(tmp, "finsi", 5) != 0){
            if (tmp[0] == '\0'){
                // on est arrive en fin de chaine sans avoir trouve finsi
                log(LOG_ERROR, "...finsi non trouve");
                //printf("Element::decomposeSi => fin 214\n");
                return false;
            }
            resultat->ListeCommandeSiFaux[i++] = *tmp++;
            resultat->ListeCommandeSiFaux[i] = '\0';
        }
        remove_extra_spaces(resultat->expression);
        remove_extra_spaces(resultat->ListeCommandeSiVrai);
        remove_extra_spaces(resultat->ListeCommandeSiFaux);
        log(LOG_DEBUG, "Tools.cpp => expression          = '%s'", resultat->expression);
        log(LOG_DEBUG, "Tools.cpp => ListeCommandeSiVrai = '%s'", resultat->ListeCommandeSiVrai);
        log(LOG_DEBUG, "Tools.cpp => ListeCommandeSiFaux = '%s'", resultat->ListeCommandeSiFaux);
        log(LOG_DEBUG, "Tools.cpp => fin 214\n");
        return true;
    }
}

//-----------------------------------------
//
//          decomposeScript
//
//-----------------------------------------
bool decomposeScript(char *ListeInstructionOrigine, char *instruction, char *listeInstructionsRestante){
    log(LOG_DEBUG, "tools decomposeScript => debut");
    log(LOG_DEBUG, "tools decomposeScript => Decomposition du script <%s>", ListeInstructionOrigine);
    strcpy(instruction, (char *)"");
    strcpy(listeInstructionsRestante, (char *)"");
    if (strlen(ListeInstructionOrigine) > 0){
        int j = 0;
        // analyse si la liste d'origine commence par un mot clé d'une instruction complexe
        // multiligne possible
        if (strncmp(ListeInstructionOrigine, "si", 2) == 0){ // traitement d'un si 
            // recherche du finsi
            char *tmp = ListeInstructionOrigine;
            while (strncmp(&tmp[j], "finsi", 5) != 0){
                j++;
                if (j > strlen(tmp)){
                    log(LOG_ERROR, "finsi non trouvé dans %s", ListeInstructionOrigine);
                    return false;
                }
                //log(LOG_DEBUG, "TODO => Finir le dev");
            } 
            /*        
            printf("tools decomposeScript => traitement d'un si\n");
            char *tmp = ListeInstructionOrigine;
            while (strncmp(tmp, "finsi ", 6) != 0){
                if (tmp - ListeInstructionOrigine >= strlen(ListeInstructionOrigine)){
                    // on a pas trouvé le finsi
                    log(LOG_ERROR, "pas de finsi dans le script");
                    return false;
                }
                instruction[j++] = tmp[0];
                tmp++;
                instruction[j] = '\0';
            }*/
            strncat(instruction, tmp, j+5);
            if (strlen(tmp) > j+6){
                strcpy(listeInstructionsRestante, tmp+j+6);
            } else {
                strcpy(listeInstructionsRestante, "");
            }
        } else { // traitement d'un instruction simple finissant par une fin de ligne
            for (int i = 0 ; i < strlen(ListeInstructionOrigine) ; i++){
                // test si 
                while (ListeInstructionOrigine[i] != '\n'){
                    instruction[j++] = ListeInstructionOrigine[i++];
                    instruction[j] = '\0';
                }
                if (i < strlen(ListeInstructionOrigine)){
                    strcpy(listeInstructionsRestante, &ListeInstructionOrigine[i+1]);
                } else {
                    strcpy(listeInstructionsRestante, "");
                }
                break;
            }
        }
        //remove_extra_spaces(instruction);
        //remove_extra_spaces(listeInstructionsRestante);
        log(LOG_DEBUG, "tools decomposeScript => instruction à traiter = <%s>", instruction);
        log(LOG_DEBUG, "tools decomposeScript => liste instr restante  = <%s>", listeInstructionsRestante);
        return true;
    }
    return false;
}