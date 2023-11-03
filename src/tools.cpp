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
#include "../inc/compteBancaire.hpp"
#include"../inc/tools.hpp"

#define TAILLE_PRENOM   30

extern Civilisation civilisation;
char fichierPrenomsMasculin[50] = "datas/liste_des_prenoms_masculin.txt";
char fichierPrenomsFeminin[50] = "datas/liste_des_prenoms_feminin.txt";

CompteBancaire *compteBancaireFournisseurNull = new CompteBancaire(NULL);
CompteBancaire *compteBancaireHeritageNull = new CompteBancaire(NULL);

#define NB_INSTRUCTION_COMPLEXES 5
char listeInstructionComplexe[NB_INSTRUCTION_COMPLEXES][20] = {"si", "set", "unset", "pour", "tantque"};

#define NB_VARIABLE_SCRIPT_HUM  10
typedef struct{
    char nom[50];
    char valeur[50];
} structVariable;
structVariable variablesDeScript[NB_VARIABLE_SCRIPT_HUM];

bool modeListeAuto = false;
bool modeTDBAuto = false;

char **tabPrenomMasculin = NULL;
char **tabPrenomFeminin = NULL;
bool tableauPrenomsOK = false;
int nbPrenomsMasculin = 0;
int nbPrenomsFeminin = 0;

//-----------------------------------------
//
//          initVariablesDeScript
//
//-----------------------------------------
void initVariablesDeScript(void){
    for (int i = 0 ; i < NB_VARIABLE_SCRIPT_HUM ; i++){
        strcpy(variablesDeScript[i].nom, "");
        strcpy(variablesDeScript[i].valeur, "");
    }
}

//-----------------------------------------
//
//          initGenerateurAleatoire
//
//-----------------------------------------
void initGenerateurAleatoire(void){
    srand (clock());
}

//-----------------------------------------
//
//          getSexeAleatoire
//
//-----------------------------------------
int getSexeAleatoire(void){
    //log(LOG_DEBUG, "Tools.cpp getSexeAleatoire => debut (a affiner)");
    srand (clock());
    int rnd = rand() % 100;
    
    bool res = civilisation.getNbHommes() > civilisation.getNbFemmes();

    res = (rnd > 50);
    //log(LOG_DEBUG, "valeur rnd = %d => res = %d", rnd, res);
    if (res)
        return FEMME;
    else
        return HOMME;
}

//-----------------------------------------
//
//          initTableauPrenomsMasculins
//
//-----------------------------------------
void initTableauPrenomsMasculins(void){
    FILE *fic;
    char prenom[TAILLE_PRENOM];
    int nbPrenoms = 0;
    char nomFichier[50] = "datas/liste_des_prenoms_masculin.txt";
    log(LOG_DEBUG, "Tools.cpp initTableauPrenomsMasculins => debut (TODO)");
    // lecture du fichier pour determiner la taille a allouer
    fic = fopen(nomFichier, "r");
    if (fic == NULL) {
        log(LOG_ERROR, "impossible d'ouvrir le fichier de prenom masculin");
        return;
    }
    log(LOG_DEBUG, "Tools.cpp initTableauPrenoms => lecture du fichier de prenoms masculin");
    while (!feof(fic)){
        if (fgets(prenom, TAILLE_PRENOM, fic) != NULL){
            prenom[strlen(prenom)-2] = '\0';
            nbPrenoms++;
        }
    }
    fclose(fic);
    log(LOG_DEBUG, "%d prenom masculins trouves", nbPrenoms);
    log(LOG_DEBUG, "Tools.cpp initTableauPrenoms => allocation dynamique du tableau de prenoms masculin");
    tabPrenomMasculin = (char **) malloc(nbPrenoms * sizeof(char *));
    for (int i = 0 ; i < nbPrenoms ; i++){
        tabPrenomMasculin[i] = (char *)malloc(TAILLE_PRENOM);
    }
    // remplissage du tableau
    log(LOG_DEBUG, "Tools.cpp initTableauPrenoms => remplissage du tableau de prenom masculin");
    nbPrenoms = 0;
    fic = fopen(nomFichier, "r");
    while (!feof(fic)){
        if (fgets(prenom, TAILLE_PRENOM, fic) != NULL){
            prenom[strlen(prenom)-2] = '\0';
            strcpy(tabPrenomMasculin[nbPrenoms], prenom);
            nbPrenoms++;
        }
    }
    fclose(fic);
    nbPrenomsMasculin = nbPrenoms;
}

//-----------------------------------------
//
//          initTableauPrenomsFeminins
//
//-----------------------------------------
void initTableauPrenomsFeminins(void){
    FILE *fic;
    char prenom[TAILLE_PRENOM];
    int nbPrenoms = 0;
    char nomFichier[50] = "datas/liste_des_prenoms_feminin.txt";
    log(LOG_DEBUG, "Tools.cpp initTableauPrenomsFeminins => debut (TODO)");
    // lecture du fichier pour determiner la taille a allouer
    fic = fopen(nomFichier, "r");
    if (fic == NULL) {
        log(LOG_ERROR, "impossible d'ouvrir le fichier de prenom feminin");
        return;
    }
    log(LOG_DEBUG, "Tools.cpp initTableauPrenoms => lecture du fichier de prenoms feminin");
    while (!feof(fic)){
        if (fgets(prenom, TAILLE_PRENOM, fic) != NULL){
            prenom[strlen(prenom)-2] = '\0';
            nbPrenoms++;
        }
    }
    fclose(fic);
    log(LOG_DEBUG, "%d prenom feminins trouves", nbPrenoms);
    log(LOG_DEBUG, "Tools.cpp initTableauPrenoms => allocation dynamique du tableau de prenoms feminin");
    tabPrenomFeminin = (char **) malloc(nbPrenoms * sizeof(char *));
    for (int i = 0 ; i < nbPrenoms ; i++){
        tabPrenomFeminin[i] = (char *)malloc(TAILLE_PRENOM);
    }
    // remplissage du tableau
    log(LOG_DEBUG, "Tools.cpp initTableauPrenoms => remplissage du tableau de prenom feminin");
    nbPrenoms = 0;
    fic = fopen(nomFichier, "r");
    while (!feof(fic)){
        if (fgets(prenom, TAILLE_PRENOM, fic) != NULL){
            if (strlen(prenom) != 0){
                prenom[strlen(prenom)-2] = '\0';
                //printf("%s\n", prenom);
                strcpy(tabPrenomFeminin[nbPrenoms], prenom);
                nbPrenoms++;
            }
        }
    }
    fclose(fic);
    nbPrenomsFeminin = nbPrenoms;
    log(LOG_DEBUG, "Tools.cpp initTableauPrenomsFeminins => fin (TODO)");
}

//-----------------------------------------
//
//          getPrenomAleatoire
//
//-----------------------------------------
char *tmpPrenom;
int idxPrenom;
char *getPrenomAleatoire(int sexe){
    //log(LOG_DEBUG, "Tools.cpp getPrenomAleatoire => debut (a affiner)");

    int nbPrenom;
    char **tabPrenoms;
    if (sexe == HOMME){
        nbPrenom = nbPrenomsMasculin;
        tabPrenoms = tabPrenomMasculin;
    } else {
        nbPrenom = nbPrenomsFeminin;
        tabPrenoms = tabPrenomFeminin;
    } 
    //srand (clock());
    int rnd = rand() % nbPrenom;
    //log(LOG_DEBUG, "Tools.cpp getPrenomAleatoire => nb prenom = %d / rnd = %d / prenom = %s", nbPrenom, rnd, tabPrenoms[rnd]);
    return (tabPrenoms[rnd]);
}

//-----------------------------------------
//
//           naissance
//
//-----------------------------------------
Element *naissance(Civilisation *civilisation, Humain *pere, Humain *mere){
    log(LOG_INFO, "tools naissance essai entre %s et %s => TODO", pere->getNomHumain(), mere->getNomHumain());
    Element *tmpElement;
    for (int i = 0 ; i < MAX_HUMAIN ; i++){
        //log(LOG_INFO, "tools naissance verification si l'élément %d est libre", i);
        tmpElement = civilisation->getElement(i);
        if (tmpElement->getElementId() == -1){
            //log(LOG_INFO, "tools naissance l'élément %d est libre", i);
            if ((pere->getNbEnfants() < MAX_ENFANTS) && (mere->getNbEnfants() < MAX_ENFANTS)){
                int sexe = getSexeAleatoire();           // TODO genere aleatoirement HOMME ou FEMME
                char *prenom = getPrenomAleatoire(sexe);   // Generer prenom depuis liste a definir
                tmpElement = civilisation->creeElementHumain(sexe, prenom, 1000);
                log(LOG_INFO, "tools naissance => %s et %s ont %s comme enfant", pere->getNomHumain(), mere->getNomHumain(), tmpElement->getNomHumain());
                pere->ajouteEnfant(tmpElement);
                mere->ajouteEnfant(tmpElement);
                tmpElement->ajouteParents(pere, mere);
                tmpElement->setElementId(i);
                log(LOG_DEBUG, "tools naissance => creation d'un enfant en position %d", tmpElement->getElementId());
                return tmpElement;
            } else {
                log(LOG_DEBUG, "tools naissance => les parents ont atteint le nombre maximal d'enfants (%d)", MAX_ENFANTS);
                return NULL;
            }
        }
    }
    log(LOG_DEBUG, "tools naissance => le tableau des humains est plein");
    return NULL;
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
    // suppression des doublons
    for (i = 0, j = 0; i < len; i++) {
        //if (str[i] == '\n') str[i] =' ';
        if (str[i] != ' ' || (i > 0 && str[i - 1] != ' ')) {
            str[j++] = str[i];
        }
    }
    // suppression des blancs en fin de ligne
    while (str[j - 1] == ' '){
        str[j - 1] = '\0';
        j--;
    }
    str[j] = '\0';
    // suppression des blancs en debut de ligne
    /*while (str[0] == ' '){
        for (int i = 0 ; i < strlen(str) ; i++){
            str[i] = str[+1];
        }
    }*/
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
//          testSiInstructionComplexe
//
//-----------------------------------------
bool testSiInstructionComplexe(char *instruction){
    //log(LOG_DEBUG, "tests si instruction <%s> complexe", instruction);
    char *commande;
    for (int i = 0 ; i < NB_INSTRUCTION_COMPLEXES ; i++){
        commande = listeInstructionComplexe[i];
        //log(LOG_DEBUG, "comparaison de <%s> avec <%s> de taille %d", instruction, commande, strlen(commande));
        if (strncmp(instruction, commande, strlen(commande)) == 0){
            //log(LOG_DEBUG, "<%s> est bien une instruction complexe", instruction);
            return true;
        } 
    }
    return false;
}

//-----------------------------------------
//
//          extraireSi
//
//-----------------------------------------
bool extraireSi(char *ListeInstructionOrigine, char *instruction, char *listeInstructionsRestante){
    log(LOG_DEBUG,"tools.extraireSi => extraction du si de la liste d'instructions <%s>", ListeInstructionOrigine);
    //char *tmp = ListeInstructionOrigine;
    int index = 0;
    int niveauSi = 0;
    //bool fin = false;
    strcpy(instruction, (char *)"");
    strcpy(listeInstructionsRestante, (char *)"");
    strcat(ListeInstructionOrigine, " ");   // pour le cas ou le script termine sur un finsi
    if (strncmp(ListeInstructionOrigine, "si ", 3) != 0){
        log(LOG_ERROR, "%s ne commence pas par si");
        return false;
    }
    bool insideSi = true;
    log(LOG_DEBUG,"tools.extraireSi => debut separation si du reste de la commande");
    strcpy(instruction, "si ");
    index += 3;
    //printf("tools.extraireSi => construction du si : <");
    for (int i = 3 ; i < strlen(ListeInstructionOrigine) ; i++){
        if (insideSi){
            //printf("on teste le caractere '%c'\n", ListeInstructionOrigine[i]);
            //printf("%c", ListeInstructionOrigine[i]);
            //tmp = &ListeInstructionOrigine[i];
            if (strncmp(&ListeInstructionOrigine[i], "si ", 3) == 0){
                niveauSi++;
                log(LOG_DEBUG, "c'est un si imbrique, on incremente le niveauSi : %d", niveauSi);
            }
            if (strncmp(&ListeInstructionOrigine[i], "finsi ", 6) == 0){
                log(LOG_DEBUG, "finsi detecte");
                // on a  trouve le finsi
                // on verifie qu'on est pas dans un si imbrique
                if (niveauSi > 0){
                    niveauSi--;
                    log(LOG_DEBUG, "c'est la fin d'un si imbrique, on decremente le niveauSi : %d", niveauSi);
                    strcat(instruction, "finsi ");
                    i += 5;
                    index += 6;
                    continue;
                } else {
                    // c'est le finSi de plus haut niveau
                    insideSi = false;
                }
                strcat(instruction, "finsi ");
                i += 5;
                index = 0;
                //printf(">\nconstruction du reste : <");
                continue;
            }
            //printf("%c", ListeInstructionOrigine[i]);
            instruction[index++] = ListeInstructionOrigine[i];
            instruction[index] = '\0';
        } else {
            listeInstructionsRestante[index++] = ListeInstructionOrigine[i];
            listeInstructionsRestante[index] = '\0';
        }
    }
    //printf(">\n");
    remove_extra_spaces(instruction);
    remove_extra_spaces(listeInstructionsRestante);
    log(LOG_DEBUG, "extraireSi => bloc Si = <%s> ; instructions restantes = <%s>", instruction, listeInstructionsRestante); 

    if (insideSi) return false;
    return true;
}

//-----------------------------------------
//
//          setAuto
//
//-----------------------------------------
void setAuto(char *parametre){
    bool res;
    if (strncmp(parametre, "liste", 5) == 0){
        modeListeAuto = !modeListeAuto;
        res = modeListeAuto;
    } else if (strncmp(parametre, "tableau", 7) == 0){
        modeTDBAuto = !modeTDBAuto;
        res = modeTDBAuto;
    } else {
        log(LOG_ERROR, "parametre de la commande 'auto' inconnu : %s", parametre);
        return;
    }
    if (res){
        log(LOG_INFO, "activation affichage automatique de '%s'", parametre);
    } else {
        log(LOG_INFO, "desactivation affichage automatique de '%s'", parametre);
    }
}

//-----------------------------------------
//
//          setVariableGlobale
//
//-----------------------------------------
bool setVariableGlobale(char *valeur){
    char *tmp = &valeur[4];
    char nomVariable [50] = "";
    char valeurVariable[50] = "";
    bool varOuVal = true;
    int index = 0;
    int j = 0;
    log(LOG_DEBUG, "tools : setVariableGlobale => debut set '%s'", tmp);
    for (int i = 0 ; i < NB_VARIABLE_SCRIPT_HUM ; i++){
        if (strlen(variablesDeScript[i].nom) == 0){
            // on peut utiliser cette variable, elle est libre
            //log(LOG_DEBUG, "Humain::setVariableGlobale => la variable %d est libre", i);
            while (j < strlen(tmp)){
                if (tmp[j] == ' '){
                    varOuVal = false;
                    j++;
                    index=0;
                    //log(LOG_DEBUG, "on passe du nom de variable a la valeur");
                }
                if (varOuVal){
                    nomVariable[index++] = tmp[j++];
                    nomVariable[index] = '\0';
                } else {
                    valeurVariable[index++] = tmp[j++];
                    valeurVariable[index] = '\0';
                }
            }
            if (strlen(valeurVariable)> 0){
                // test si variable deja definie
                for (int k = 0 ; k < NB_VARIABLE_SCRIPT_HUM ; k++){
                    if (strcmp(variablesDeScript[k].nom, nomVariable) == 0){
                        // cette variable existe deja : on la met a jour
                        log(LOG_DEBUG, "la variable '%s' existe deja, on met a jour sa nouvelle valeur '%s'", nomVariable, valeurVariable);
                        strcpy(variablesDeScript[k].valeur,valeurVariable);
                        return true;
                    }
                }
                strcpy(variablesDeScript[i].nom,nomVariable);
                strcpy(variablesDeScript[i].valeur,valeurVariable);
                log(LOG_DEBUG,"tools : affectation de la variable <%s> avec la valeur <%s> en position %d", variablesDeScript[i].nom, variablesDeScript[i].valeur, i);
                return true;
            } else {
                log(LOG_ERROR, "commande 'set' : erreur de syntaxe, manque valeur ");
                return false;
            }
        }
    }
    log(LOG_ERROR, "commande 'set' : nombre de variables depasse (%d) ", NB_VARIABLE_SCRIPT_HUM);
    return false;
}

//-----------------------------------------
//
//          getVariableGlobale
//
//-----------------------------------------
char *getVariableGlobale(char *nom){
    //log(LOG_DEBUG, "tools : getVariableGlobale => debut  get '%s'", nom);
    for(int i = 0 ; i < NB_VARIABLE_SCRIPT_HUM ; i++){
        //log(LOG_DEBUG, "comparaison avec variable %d : <%s>", i, variablesDeScript[i].nom);
        if (strcmp(variablesDeScript[i].nom, nom) == 0){
            // on a trouve la valeur avec le bon nom
            //log(LOG_DEBUG, "on a trouver la bonne variable, on retourne sa valeur <%s>", variablesDeScript[i].valeur);
            return variablesDeScript[i].valeur;
        }
    }
    //log(LOG_DEBUG, "tools : getVariableGlobale => on a pas trouve la variable <%s>", nom);
    return NULL;
}

//-----------------------------------------
//
//          Humain::unsetVariableGlobale
//
//-----------------------------------------
bool unsetVariableGlobale(char *nom){
    char *tmp = &nom[6];
    log(LOG_DEBUG, "tools : unsetVariableGlobale => debut unset '%s'\n", tmp);
    for(int i = 0 ; i < NB_VARIABLE_SCRIPT_HUM ; i++){
        //log(LOG_DEBUG, "comparaison avec variable %d : <%s>", i, variablesDeScript[i].nom);
        if (strcmp(variablesDeScript[i].nom, tmp) == 0){
            // on a trouve la valeur avec le bon nom
            strcpy(variablesDeScript[i].nom,"");
            strcpy(variablesDeScript[i].valeur,"");
            log(LOG_DEBUG, "on a trouver la bonne variable, on l'efface");
            return true;
        }
    }
    return false;
}

//-----------------------------------------
//
//          initTools
//
//-----------------------------------------
void initTools(void){
    initVariablesDeScript();
    initGenerateurAleatoire();
    if (tabPrenomMasculin == NULL) initTableauPrenomsMasculins();
    if (tabPrenomFeminin == NULL) initTableauPrenomsFeminins();
}