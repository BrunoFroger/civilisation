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
    //log(LOG_DEBUG, "Element::Element(int id (%d), int type(%d))", id, type);
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
    // test si expression vide
    if (strlen(expression) == 0){
        log(LOG_DEBUG, "Element::executeExpression => expression vide, on retourne true");
        return true;
    } 
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
//          Element::testSiListeCommandeValide
//
//-----------------------------------------
bool Element::testSiListeCommandeValide(char *valeur){
    if (typeElement == TYPE_HUMAIN){
        return testSiListeCommandeValideHumain(valeur);
    } else if (typeElement == TYPE_ENTREPRISE){
        return testSiListeCommandeValideEntreprise(valeur);
    }
    return false;
}

//-----------------------------------------
//
//          Element::execScript
//
//-----------------------------------------
bool Element::execScript(char *filename){
    FILE *fic;
    char ligne[500];
    char script[5000] = "";
    char *tmp;

    log(LOG_DEBUG, "Element::execScript => debut avec fichier <%s>", filename);
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
    fclose(fic);
    remove_extra_spaces(script);
    log(LOG_DEBUG, "script a analyser : \n----------------------\n'%s'\n----------------------", script);
    return evalueListeInstructions(script);
}

//-----------------------------------------
//
//          Element::decomposeScript
//
//-----------------------------------------
bool Element::decomposeScript(char *ListeInstructionOrigine, char *instruction, char *listeInstructionsRestante){
    log(LOG_DEBUG, "Element::decomposeScript => debut");
    remove_extra_spaces(ListeInstructionOrigine);
    log(LOG_DEBUG, "Element::decomposeScript => Decomposition du script <%s>", ListeInstructionOrigine);
    char instructionLocale[1000] = "";
    char listeInstructionRestanteLocale[5000] = "";
    char *tmp = ListeInstructionOrigine;
    char mot[100] = "";
    int index = 0;
    if (strlen(ListeInstructionOrigine) > 0){
        // extraction premier mot
        while ((tmp[index] != ' ') && (tmp[index] != '\n')){
            mot[index] = tmp[index];
            index++;
            mot[index] = '\0';
        }
        log(LOG_DEBUG, "mot trouve : <%s>", mot);
        if (testSiInstructionComplexe(mot)){
            // on a trouvé une instruction compexe
            log(LOG_DEBUG, "Element::decomposeScript => traitement d'une instruction complexe (%s)", mot);
            if (strncmp(mot, "si", 2) == 0){
                if (!extraireSi(ListeInstructionOrigine, instructionLocale, listeInstructionRestanteLocale)){
                    return false;
                }
                // traitement du si
                structSi resultat;
                if (!decomposeSi(instructionLocale, &resultat)) return false;
                //if (!evalueListeInstructions(listeInstructionRestanteLocale)) return false;
                evalueListeInstructions(listeInstructionRestanteLocale);
                log(LOG_DEBUG, "Element::decomposeScript => fin de decomposition du 'si' ");
                //return true;
            } else if(strncmp(mot, "set", 3) == 0){
                log(LOG_DEBUG, "Element::decomposeScript => .......    T O D O    ........ => decomposition du 'set' a developper");
                if (!decomposeSet(ListeInstructionOrigine, listeInstructionRestanteLocale)) return false;
                //if (!evalueListeInstructions(listeInstructionRestanteLocale)) return false;
                evalueListeInstructions(listeInstructionRestanteLocale);
                log(LOG_DEBUG, "Element::decomposeScript => fin de decomposition du 'set' ");
                //return false;
            } else {
                log(LOG_ERROR, "ERREUR : instruction complexe pas encore traitee .... (%s)", mot);
                return false;
            }
        } else {
            strcpy(instructionLocale, mot);
            //strcpy(listeInstructionsRestante, &tmp[index]);
        }
        // c'est une instruction simple
        remove_extra_spaces(instructionLocale);
        remove_extra_spaces(listeInstructionsRestante);
        log(LOG_DEBUG, "Element::decomposeScript => instruction à traiter = <%s>", instructionLocale);
        log(LOG_DEBUG, "Element::decomposeScript => liste instr restante  = <%s>", listeInstructionsRestante);
    } else {
        log(LOG_DEBUG, "Element::decomposeScript => la liste a evaluer est vide, on return true");
    }
    strcpy(instruction, instructionLocale);
    strcpy(listeInstructionsRestante, listeInstructionRestanteLocale);
    log(LOG_DEBUG, "Element::decomposeScript => fin, on return true : instruction = <%s>, reste = <%s>", instruction, listeInstructionsRestante);
    return true;
}

//-----------------------------------------
//
//          Element::decomposeSet
//
//-----------------------------------------
bool Element::decomposeSet(char *ligne, char *ListeInstructionRestante){
    char buffer[500] = "";
    char *tmp = ligne;
    int cptSeparateur = 0;
    log(LOG_DEBUG, "Element::decomposeSet => -----------------------------");
    log(LOG_DEBUG, "Element::decomposeSet => debut <%s>", ligne);
    int i = 0;
    while(cptSeparateur < 3){
        if (tmp[0] == ' '){
            cptSeparateur++;
        } 
        buffer[i++] = tmp[0];
        buffer[i] = '\0';
        tmp++;
    }
    remove_extra_spaces(buffer);
    log(LOG_DEBUG, "Element::decomposeSet => execution de setVariable(%s)", buffer);
    strcpy(ListeInstructionRestante, tmp);
    log(LOG_DEBUG, "Element::decomposeSet => listeInstruction restante = '%s'", ListeInstructionRestante);
    return setVariable(buffer);
    //return false;
}

//-----------------------------------------
//
//          Element::decomposeSi
//
//-----------------------------------------
bool Element::decomposeSi(char *ligne, structSi *resultat){

    int i = 0;
    char *tmp;
    char buffer[200];
    log(LOG_DEBUG, "Element::decomposeSi => -----------------------------");
    log(LOG_DEBUG, "Element::decomposeSi => decomposeSi => debut <%s>", ligne);

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
            log(LOG_DEBUG, "Element::decomposeSi => expression          => '%s'", resultat->expression);
            log(LOG_DEBUG, "Element::decomposeSi => ListeCommandeSiVrai => '%s'", resultat->ListeCommandeSiVrai);
            log(LOG_DEBUG, "Element::decomposeSi => ListeCommandeSiFaux => '%s'", resultat->ListeCommandeSiFaux);
            log(LOG_DEBUG, "Element::decomposeSi => fin du si sans sinon");
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
        log(LOG_DEBUG, "Element::decomposeSi => expression          => '%s'", resultat->expression);
        log(LOG_DEBUG, "Element::decomposeSi => ListeCommandeSiVrai => '%s'", resultat->ListeCommandeSiVrai);
        log(LOG_DEBUG, "Element::decomposeSi => ListeCommandeSiFaux => '%s'", resultat->ListeCommandeSiFaux);
        log(LOG_DEBUG, "Element::decomposeSi => fin du si avec sinon");
    }
    return true;
}

//-----------------------------------------
//
//          Element::evalueListeInstructions
//
//-----------------------------------------
bool Element::evalueListeInstructions(char *listeInstructions){
    bool res = false;
    log(LOG_DEBUG, "Element::evalueListeInstructions => debut du traitement de '%s'  .......     TODO   .....", listeInstructions);
    // tester si c'est une instruction simple, 
    // si oui, l'executer 
    // sinon, la decomposer et relancer cette fonction avec la liste restante
    char scriptRestant[2000];
    char instruction[1000];
    // test si liste vide, si oui, fin normale => return true
    if (strlen(listeInstructions) == 0){
        log(LOG_DEBUG, "Element::evalueListeInstructions => la liste a evaluer est vide, on return true");
        return true;
    } 
    //do {
        log(LOG_DEBUG, "Element::evalueListeInstructions =>  '%s'", listeInstructions);
        strcpy(instruction, (char *)"");
        strcpy(scriptRestant, (char *)"");
        printf("Element::evalueListeInstructions =>  entree dans decompose script\n");
        res = decomposeScript(listeInstructions, instruction, scriptRestant);
        printf("Element::evalueListeInstructions =>  sortie de decompose script\n");
        if (!res){
            log(LOG_DEBUG, "Element::evalueListeInstructions => erreur dans decomposeScript");
            return false;
        }
        log(LOG_DEBUG, "Element::evalueListeInstructions => decomposeScript OK, on essaye d'evaluer l'instruction extraite <%s>", instruction);
        if (!executeExpression(instruction)){
            log(LOG_DEBUG, "Element::evalueListeInstructions => erreur dans executeExpression");
            return false;
        } else{
            log(LOG_DEBUG, "Element::evalueListeInstructions => Element::evalueListeInstructions => on a reussi a evaluer l'expression <%s> on evalue la liste restante <%s> ", instruction, scriptRestant);
            //if (!evalueListeInstructions(scriptRestant)){
            //    return false;
            //}
            if (strlen(scriptRestant) > 0){
                evalueListeInstructions(scriptRestant);
            }
        } 
        //res = (strcmp(scriptRestant, "") == 0);
        //printf("fin evalueListeInstructions => appuyer sur enter test scriptRestant vide '' : (strcmp('%s', '') = %d) \n", scriptRestant, res);getchar();
    //} while (res);
    log(LOG_DEBUG, "Element::evalueListeInstructions => fin du traitement de '%s'  .......     TODO   .....", listeInstructions);
    return true;
}

//-----------------------------------------
//
//          Humain::isVariable
//
//-----------------------------------------
bool Element::isVariable(char *valeur){
    //printf("isvariable : test de la variable %s\n", valeur);
    // en fonction du type on verifie si c'est une variable specifique du type
    if (typeElement == TYPE_HUMAIN){
        Humain *tmpHumain = this;
        if (tmpHumain->isVariable(valeur)) return true;
    } else if(typeElement == TYPE_ENTREPRISE){
        Entreprise *tmpEntreprise = this;
        if(tmpEntreprise->isVariable(valeur)) return true;
    }

    // sinon test si c'est une variable generique de script
    if (getVariable(valeur) != NULL) return true;

    return false;
}