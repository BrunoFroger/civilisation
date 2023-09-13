//-----------------------------------------
//
//          element.cpp
//
//-----------------------------------------

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "../inc/element.hpp"
#include "../inc/log.hpp"
#include "../inc/tools.hpp"

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
    //printf("initialisation element %d, %d\n", id, type);
    log(LOG_DEBUG, "Element::Element(int id, int type)");
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
            if (id != -1){
                log(LOG_ERROR, "Element::Element => construction type d'element inconnu %d", type);
            }
            break;
    }
}

//-----------------------------------------
//
//          getTypeElement
//
//-----------------------------------------
int Element::getTypeElement(void){
    return this->typeElement;
}

//-----------------------------------------
//
//          setTypeElement
//
//-----------------------------------------
void Element::setTypeElement(int type){
    this->typeElement = type;
}

//-----------------------------------------
//
//          getElementId
//
//-----------------------------------------
int Element::getElementId(void){
    return this->idElement;
}

//-----------------------------------------
//
//          setElementId
//
//-----------------------------------------
void Element::setElementId(int id){
    this->idElement = id;
}
/*
//-----------------------------------------
//
//          decomposeIf
//
//-----------------------------------------
bool Element::decomposeSi(FILE *fic, char *ligne, structSi *resultat){

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
}*/

//-----------------------------------------
//
//          decomposeExpression
//
//-----------------------------------------
/*bool Element::decomposeExpression(char *expression, structExpression *resultat){
    log(LOG_DEBUG, "decompose expression => debut\n");
    log(LOG_DEBUG, "decompose expression => expression initiale : '%s'\n", expression);
    remove_extra_spaces(expression);
    log(LOG_DEBUG, "decompose expression => expression apres suppression des blancs : '%s'\n", expression);
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
        log(LOG_DEBUG, "tentative d'evaluation d'item1 : '%s'\n", resultat->item1);
        if (isVariable(resultat->item1)){
            log(LOG_DEBUG, "item1 est bien une variable connue\n");
            char buff[10];
            log(LOG_DEBUG, "valeur de item1 :'%d'\n", getIntValue(resultat->item1));
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
    log(LOG_DEBUG, "resultat de la decomposition : '%s' '%s' '%s'\n", resultat->item1, resultat->opTest, resultat->item2);
    log(LOG_DEBUG, "decompose expression => fin\n");
    return true;
}*/

//-----------------------------------------
//
//          Element::execScript
//
//-----------------------------------------
bool Element::execScript(void){
    bool result = false;
    log(LOG_DEBUG, "Element::execScript => debut");
    switch(typeElement){
        case TYPE_HUMAIN:
            result = execScript((char *)"scripts/humain.scr");
            break;
        case TYPE_ENTREPRISE:
            result = execScript((char *)"scripts/entreprise.scr");
            break;
        default:
            result = false;
            break;
    }
    return result;
}

//-----------------------------------------
//
//          Element::executeExpression
//
//-----------------------------------------
bool Element::executeExpression(char *expression){
    log(LOG_DEBUG, "Element::executeExpression => TODO");
    log(LOG_DEBUG, "Element::executeExpression => traitement de '%s'", expression);
    // tests si expression simple ou complexe
    if (strncmp(expression, "si", 2) == 0){
        structSi resultatSi;
        log(LOG_DEBUG, "Element::executeExpression => traitement d'un 'si'");
        if (!decomposeSi(expression, &resultatSi)){
            log(LOG_ERROR, "instruction 'si' invalide <%s>", expression);
        } else {
            log(LOG_DEBUG, "Element::executeExpression => traitement de si <%s> alors <%s> sinon <%s> finsi", resultatSi.expression, resultatSi.ListeCommandeSiVrai, resultatSi.ListeCommandeSiFaux);
            if (evalueExpressionHumain(resultatSi.expression)){
                // execution des commandes si vrai
                log(LOG_DEBUG, "Element::executeExpression => execution des commandes si vrai");
                executeExpression(resultatSi.ListeCommandeSiVrai);
            } else {
                // execution des commandes si faux
                log(LOG_DEBUG, "Element::executeExpression => execution des commandes si faux");
                executeExpression(resultatSi.ListeCommandeSiFaux);
            }
        }
    } else {
        log(LOG_DEBUG, "Element::executeExpression => traitement d'une expression simple");
        switch(this->typeElement){
            case TYPE_HUMAIN:
                if (testSiCommandeValideHumain(expression)){
                    log(LOG_DEBUG, "Element::executeExpression => execute commande humain simple '%s'", expression);
                    execCommandeHumain(expression);
                }
                break;
            case TYPE_ENTREPRISE:
                if (testSiCommandeValideEntreprise(expression)){
                    log(LOG_DEBUG, "Element::executeExpression => execute commande entreprise simple '%s'", expression);
                    execCommandeEntreprise(expression);
                }
                break;
        }
    }
    log(LOG_DEBUG, "Element::executeExpression => fin '%s'", expression);
    return true;
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
    char script[5000] = "";
    char scriptRestant[5000] = "";
    char *tmp;

    fic = fopen(filename, "r");
    if (fic == NULL){
        log(LOG_ERROR, "Element::execScript => impossible d'ouvrir le fichier script <%s>", filename);
        return false;
    }
    log(LOG_DEBUG, "Element::execScript => execution du script '%s'", filename);
    strcpy(ligne, "");
    fgets(ligne, 100, fic);
    while (!feof(fic)){
        tmp = &ligne[0];
        //printf("traitement de la ligne %s", tmp);
        if (tmp[0] != '#') {
            while (tmp[0] == ' ') tmp++; // suppresssion des blancs au debut
            if (strlen(ligne) > 0){
                if (tmp[strlen(tmp) - 1] == '\n'){
                    tmp[strlen(tmp) - 1] = '\0';
                }   
            }
            strcat(script, " ");
            strcat(script, tmp);
        }
        strcpy(ligne, "");
        fgets(ligne, 100, fic);
    }
    remove_extra_spaces(script);
    log(LOG_DEBUG, "script a analyser : \n----------------------\n'%s'\n----------------------", script);
    tmp = &script[0];
    char expression[500];
    //structExpression expressionResultat;
    do {
        log(LOG_DEBUG, "---- decompose script -------\n");
        decomposeScript(script, expression, scriptRestant);
        executeExpression(expression);
        strcpy(script, scriptRestant);
    } while (strcmp(scriptRestant, "") != 0);
    fclose(fic);
    return true;

    //      code inutilisé
    // a voir si reutilisable

    if (tmp[0] != '#'){ // commentaire on passe
        if (strlen(tmp) != 0){  // ligne vide on passe
            //printf("ligne a analyser = '%s'\n", tmp);
            if (strncmp(tmp, "si", 2) == 0){
                //printf("Analyse d'une ligne contenant un 'si'\n");
                structSi resultat;
                if (!decomposeSi(tmp, &resultat)){
                    log(LOG_ERROR, "erreur de syntaxe dans le fichier '%s' a la ligne %d (%s)\n", filename, numLigne, tmp);
                    return false;
                } else {
                    // traitement de la ligne si
                    if (!testSiListeCommandeValideHumain(resultat.ListeCommandeSiVrai)){
                        log(LOG_ERROR, "instruction '%s' inconnue\n", resultat.ListeCommandeSiVrai);
                        return false;
                    }
                    if (!testSiListeCommandeValideHumain(resultat.ListeCommandeSiFaux)){
                        log(LOG_ERROR, "instruction '%s' inconnue\n", resultat.ListeCommandeSiFaux);
                        return false;
                    }
                    log(LOG_DEBUG, "decomposition de l'expression %s\n", resultat.expression);
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
    //printf("\n");
    return true;
}