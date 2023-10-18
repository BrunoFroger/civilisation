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
//          getNom
//
//-----------------------------------------
char *Element::getNom(void){
    if (getTypeElement() == TYPE_HUMAIN){
        return this->getNomHumain();
    } else if (getTypeElement() == TYPE_ENTREPRISE){
        return this->getNomEntreprise();
    }
    return (char *)"NC";
}

//-----------------------------------------
//
//          getCompteBancaire
//
//-----------------------------------------
CompteBancaire *Element::getCompteBancaire(void){
    if (getTypeElement() == TYPE_HUMAIN){
        return compteBancaireHumain;
    } else if (getTypeElement() == TYPE_ENTREPRISE){
        return compteBancaireEntreprise;
    }
    return NULL;
}

//-----------------------------------------
//
//          setElementId
//
//-----------------------------------------
void Element::setElementId(int id){
    this->idElement = id;
}

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
//          Element::evalueExpression
//
//-----------------------------------------
bool Element::evalueExpression(char *expression){
    if (typeElement == TYPE_HUMAIN){
        return evalueExpressionHumain(expression);
    } else if (typeElement == TYPE_ENTREPRISE){
        return evalueExpressionEntreprise(expression);
    } else {
        log(LOG_ERROR, "Element::evalueExpression => le type d'element est invalide");
    }
    return false;
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
            if (evalueExpression(resultatSi.expression)){
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