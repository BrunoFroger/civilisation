//-----------------------------------------
//
//          element.cpp
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include "../inc/element.hpp"
#include "../inc/log.hpp"

#define MAX_HUMAIN  3

Humain *ptrHumain;

//-----------------------------------------
//
//          ~Element
//
//-----------------------------------------
Element::~Element(){
    //log(LOG_DEBUG, "Element::~Element()");
    //delete ptrHumain;
}

//-----------------------------------------
//
//          Element
//
//-----------------------------------------
Element::Element(){
    //log(LOG_DEBUG, "Element::Element()");
    int id = -1;
    int type = TYPE_INDEFINI;
    Element(id, type);
}

//-----------------------------------------
//
//          Element
//
//-----------------------------------------
Element::Element(int id, int type){
    //log(LOG_DEBUG, "Element::Element(int id, int type)");
    this->idElement = id;
    this->typeElement = type;
    switch (type){
        case TYPE_HUMAIN:
            log(LOG_DEBUG, "Element::Element => construction d'un Humain");
            break;
        case TYPE_ENTREPRISE:
            log(LOG_DEBUG, "Element::Element => construction d'une entreprise");
            break;
        default:
        log(LOG_ERROR, "Element::Element => construction type d'element inconnu %d", type);
            break;
    }
}

//-----------------------------------------
//
//          decomposeIf
//
//-----------------------------------------
int Element::getElementId(void){
    return this->idElement;
}

//-----------------------------------------
//
//          decomposeIf
//
//-----------------------------------------
void Element::setElementId(int id){
    this->idElement = id;
}

//-----------------------------------------
//
//          decomposeIf
//
//-----------------------------------------
bool Element::decomposeSi(FILE *fic, char *ligne, structIf *resultat){

    int i = 0;
    char *tmp;
    char buffer[200];
    //printf("Element::decomposeSi => debut\n");

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
        }
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
        //printf("ListeCommandeSiFaux = '%s'\n", resultat->ListeCommandeSiFaux);
        //printf("Element::decomposeSi => fin 220\n");
        return true;
    }
}

//-----------------------------------------
//
//          evaluationExpressionInt
//
//-----------------------------------------
bool Element::evaluationExpressionInt(int data1, char *test, int data2){
    //printf("test '='\n");
    if (strcmp(test, "=") == 0) return (data1==data2);
    //printf("test '!='\n");
    if (strcmp(test, "!=") == 0) return !(data1==data2);
    if (strcmp(test, ">") == 0) return (data1>data2);
    if (strcmp(test, "<") == 0) return (data1<data2);
    if (strcmp(test, ">=") == 0) return (data1 >= data2);
    if (strcmp(test, "<=") == 0) return (data1 <= data2);
    //printf("aucun test valide\n");
    return false;
}

//-----------------------------------------
//
//          evaluationExpressionChar
//
//-----------------------------------------
bool Element::evaluationExpressionChar(char *data1, char *test, char *data2){
    //printf("test '='\n");
    if (strcmp(test, "=") == 0) return (strcmp((const char*)data1, (const char*)data2) == 0);
    //printf("test '!='\n");
    if (strcmp(test, "!=") == 0) return !(strcmp((const char*)data1, (const char*)data2) == 0);
    if (strcmp(test, ">") == 0) return (strcmp((const char*)data1, (const char*)data2) > 0);
    if (strcmp(test, "<") == 0) return (strcmp((const char*)data1, (const char*)data2) < 0);
    if (strcmp(test, ">=") == 0) return (strcmp((const char*)data1, (const char*)data2) >= 0);
    if (strcmp(test, "<=") == 0) return (strcmp((const char*)data1, (const char*)data2) <= 0);
    //printf("aucun test valide\n");
    return false;
}

//-----------------------------------------
//
//          decomposeExpression
//
//-----------------------------------------
bool Element::decomposeExpression(char *expression, structExpression *resultat){
    printf("decompose expression => debut\n");
    printf("decompose expression => expression initiale : '%s'\n", expression);
    remove_extra_spaces(expression);
    printf("decompose expression => expression apres suppression des blancs : '%s'\n", expression);
    int i = 0;
    int j = 0;
    // traitement des sous expressions entre parentheses si necessaire
    if (expression[i] == '('){
        char sous_expression[100];
        j = 0;
        i++;
        // recuperation de ce qu'il y a entre parentheses pour le traiter séparement
        while (expression[i] != ')'){
            sous_expression[j++] = expression[i++];
            sous_expression[j] = '\0';
        }
        strcpy(resultat->item1, sous_expression);
        structExpression sous_resultat;
        decomposeExpression(sous_expression, &sous_resultat);
        char res[20];
        sprintf(res,"%d", calculExpression(sous_resultat.item1, sous_resultat.opTest[0], sous_resultat.item2));
        strcpy(resultat->item1, res);
        i++;
    } else {
    // il n'y a pas de parenthese au debut c'est l'item1
    j = 0;
        while (expression[i] == ' ') i++;
        while (expression[i] != ' '){
            resultat->item1[j++] = expression[i++];
            resultat->item1[j]  = '\0';
        }
        // TODO
        // evaluation de l'item
        printf("tentative d'evaluation d'item1 : '%s'\n", resultat->item1);
        if (isVariable(resultat->item1)){
            printf("item1 est bien une variable connue\n");
            char buff[10];
            printf("valeur de item1 :'%d'\n", getIntValue(resultat->item1));
            sprintf(buff, "%d", getIntValue(resultat->item1));
            strcpy(resultat->item1, buff);
        } 
    }
    

    // on passe a l'extraction de l'operateur
    j = 0;
    while (expression[i] == ' ') i++;
    while (expression[i] != ' '){
        resultat->opTest[j++] = expression[i++];
        resultat->opTest[j]  = '\0';
    }

    // traitement des sous expressions entre parentheses si necessaire
    while (expression[i] == ' ') i++;
    if (expression[i] == '('){
        char sous_expression[100];
        j = 0;
        i++;
        // recuperation de ce qu'il y a entre parentheses pour le traiter séparement
        while (expression[i] != ')'){
            sous_expression[j++] = expression[i++];
            sous_expression[j] = '\0';
        }
        strcpy(resultat->item2, sous_expression);
        structExpression sous_resultat;
        decomposeExpression(sous_expression, &sous_resultat);
        char res[20];
        sprintf(res,"%d", calculExpression(sous_resultat.item1, sous_resultat.opTest[0], sous_resultat.item2));
        strcpy(resultat->item2, res);
    } else {
    // il n'y a pas de parenthese au debut c'est l'item1
    j = 0;
        while (expression[i] == ' ') i++;
        while (expression[i] != ' '){
            resultat->item2[j++] = expression[i++];
            resultat->item2[j]  = '\0';
        }
        // TODO
        // evaluation de l'item
        printf("tentative d'evaluation d'item2 : '%s'\n", resultat->item2);
        if (isVariable(resultat->item2)){
            printf("item1 est bien une variable connue\n");
            char buff[10];
            printf("valeur de item2 :'%d'\n", getIntValue(resultat->item2));
            sprintf(buff, "%d", getIntValue(resultat->item2));
            strcpy(resultat->item2, buff);
        }
    }
    // TODO
    // evaluation de l'expression
    printf("resultat de la decomposition : '%s' '%s' '%s'\n", resultat->item1, resultat->opTest, resultat->item2);
    printf("decompose expression => fin\n");
    return true;
}

//-----------------------------------------
//
//          Element::execScript
//
//-----------------------------------------
bool Element::execScript(void){
    return execScript((char *)"scripts/humain.scr");
}

//-----------------------------------------
//
//          Element::execScript
//
//-----------------------------------------
bool Element::execScript(char *filename){
    FILE *fic;
    int numLigne=0;
    char ligne[500];

    fic = fopen(filename, "r");
    if (fic == NULL){
        log(LOG_ERROR, "Humain::execScript => impossible d'ouvrir le fichier script ");
        return false;
    }
    //printf("lecture du fichier '%s'\n", filename);
    strcpy(ligne, "");
    fgets(ligne, 100, fic);
    while (!feof(fic)){
        if (strlen(ligne) > 0) ligne[strlen(ligne) - 1] = '\0';
        char *tmp = &ligne[0];
        while (tmp[0] == ' ') tmp++;    // suppresssion des blancs au debut
        //printf("ligne a analyser = '%s'\n", tmp);
        if (tmp[0] != '#'){ // commentaire on passe
            if (strlen(tmp) != 0){  // ligne vide on passe
                //printf("ligne a analyser = '%s'\n", tmp);
                if (strncmp(tmp, "si", 2) == 0){
                    //printf("Analyse d'une ligne contenant un 'si'\n");
                    structIf resultat;
                    if (!Element::decomposeSi(fic, tmp, &resultat)){
                        log(LOG_ERROR, "erreur de syntaxe dans le fichier '%s' a la ligne %d (%s)\n", filename, numLigne, tmp);
                        return false;
                    } else {
                        // traitement de la ligne si
                        if (!testSiListeCommandeValide(resultat.ListeCommandeSiVrai)){
                            log(LOG_ERROR, "instruction '%s' inconnue\n", resultat.ListeCommandeSiVrai);
                            return false;
                        }
                        if (!testSiListeCommandeValide(resultat.ListeCommandeSiFaux)){
                            log(LOG_ERROR, "instruction '%s' inconnue\n", resultat.ListeCommandeSiFaux);
                            return false;
                        }
                        printf("decomposition de l'expression %s\n", resultat.expression);
                        /*
                        int val1, val2;
                        if (isVariable(resultat.expression1)){
                            val1 = getIntValue(resultat.expression1);
                        } else {
                            val1 = atoi(resultat.expression1);
                        }
                        if (isVariable(resultat.expression2)){
                            val2 = getIntValue(resultat.expression2);
                        } else {
                            val2 = atoi(resultat.expression2);
                        }
                        Element::evaluationExpressionInt(val1, resultat.operateur, val2);
                        */
                    } 
                } else {
                    log(LOG_ERROR, "instruction inconnue dans la ligne '%s'\n", ligne);
                    return false;
                }
            }
        }
        //printf("fin traitement de ligne\n");
        if (!feof(fic)){
            strcpy(ligne, "");
            //printf("Lecture nouvelle ligne\n");
            fgets(ligne, 500, fic);
            //printf("'%s'", ligne);
            numLigne++;
        }
    }
    //printf("\n");
    return true;
}

//-----------------------------------------
//
//          Element::calculExpression
//
//-----------------------------------------
int Element::calculExpression(char *data1, char op, char *data2){
    int val1;
    int val2;
    int res;
    if (isVariable(data1)){
        val1 = getIntValue(data1);
    } else {
        val1 = atoi(data1);
    }
    if (isVariable(data1)){
        val2 = getIntValue(data2);
    } else {
        val2 = atoi(data2);
    }
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
    return res;
}