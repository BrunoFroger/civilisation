//-----------------------------------------
//
//          analyseLigneCommande.cpp
//
//-----------------------------------------

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "../inc/log.hpp"
#include "../inc/civilisation.hpp"
#include "../inc/tools.hpp"
#include "../inc/aide.hpp"
#include "../inc/analyseLigneCommande.hpp"

extern Civilisation civilisation;
char historiqueCommandes[NB_COMMANDE_HISTORIQUE][50];

//-----------------------------------------
//
//          commandeCree
//
//-----------------------------------------
void commandeCree(char *commande){
    char parametres[10][20];
    int j = 0, i = 0;
    int idxParam = 0;
    char nom[50] = "";
    int sexe = -1;
    int capital = -1;
    int typeEntreprise = -1;
    int typeElement = TYPE_INDEFINI;

    for (int i = 0 ; i < 10 ; i++){
        strcpy(parametres[i], "");
    }

    while (i < strlen(commande)){
        if (commande[i] == ' '){
            idxParam += 1;
            if (idxParam >= 10){
                log(LOG_ERROR, "trop de parametres pour la commande <cree type .... >");
                return;
            }
            j = 0;
        } else {
            parametres[idxParam][j++] = commande[i];
            parametres[idxParam][j] = '\0';
        }
        i++;
    }
    i = 0;
    if (strlen(parametres[i]) == 0){    // analyse du sexe
        log(LOG_ERROR, "pas assez de parametres pour la commande <cree [humain|entreprise] ... >");
        return;
    } else {
        if (strncmp(parametres[i], "humain", 6) == 0){
            typeElement = TYPE_HUMAIN;
            if (strlen(parametres[i]) == 0){    // analyse du sexe
                log(LOG_ERROR, "pas assez de parametres pour la commande <cree humain sexe nom capital>");
                return;
            } else {
                switch (parametres[i][0]){
                    case 'h':
                    case 'H':
                        sexe = HOMME;
                        break;
                    case 'f':
                    case 'F':
                        sexe = FEMME;
                    default :
                        sexe = -1;
                        break;
                }
            }
        } else if (strncmp(parametres[i], "entreprise", 10) == 0){
            if (strlen(parametres[i]) == 0){    // analyse du sexe
                log(LOG_ERROR, "pas assez de parametres pour la commande <cree entreprise [commerce|industrie] nom capital>");
                return;
            } else {
                if (strncmp(parametres[i], "commerce", 8) == 0){
                    typeEntreprise = ACTIVITE_COMMERCE;
                } else if (strncmp(parametres[i], "industrie", 9) == 0){
                    typeEntreprise = ACTIVITE_INDUSTRIE;
                } else {
                    typeEntreprise = ACTIVITE_INCONNUE;
                }
            }
        } else {
            log(LOG_ERROR, "erreur de parametres pour la commande <cree [humain|entreprise] ... >");
        }
        i++;
    }
    i++;
    if (strlen(parametres[i]) == 0){    // analyse du nom
        log(LOG_ERROR, "pas assez de parametres pour la commande <cree humain sexe nom capital>");
        return;
    } else {
        strcpy(nom, parametres[i]);
    }
    i++;
    if (strlen(parametres[i]) == 0){    // analyse du capital
        log(LOG_ERROR, "pas assez de parametres pour la commande <cree humain sexe nom capital>");
        return;
    } else {
        if (atoi(parametres[i]) > 0){
            capital = atoi(parametres[i]);
        }
    }
    i++;
    if (strlen(parametres[i]) > 0) {
        log(LOG_ERROR, "trop de parametres pour la commande <cree humain sexe nom capital>");
        return;
    }
    if (typeElement == TYPE_HUMAIN){
        printf("creation d'un humain nom : %s de sexe %d avec un capital de %d\n", nom, sexe, capital);
        civilisation.creeElementHumain(sexe, nom, capital);
    } else {
        printf("creation d'une entreprise nom : %s de type %d avec un capital de %d\n", nom, typeEntreprise, capital);
        civilisation.creeElementEntreprise(typeEntreprise, nom, capital, NULL);
    }
}


//-----------------------------------------
//
//          initHistoriqueCommande
//
//-----------------------------------------
void initHistoriqueCommande(void){
    for(int i = 0 ; i < NB_COMMANDE_HISTORIQUE ; i++){
        strcpy(historiqueCommandes[i], "");
    }
}

//-----------------------------------------
//
//          afficheHistorique
//
//-----------------------------------------
void afficheHistorique(void){
    //log(LOG_INFO, "historique des commandes saisies");
    //for (int i = 0 ; i < NB_COMMANDE_HISTORIQUE ; i++){
    //    printf("tmp : %d : %s\n", i, historiqueCommandes[i]);
    //}
    for (int i = (NB_COMMANDE_HISTORIQUE - 1) ; i >= 0 ; i--){
        //printf("tmp : %d : %s\n", i, historiqueCommandes[i]);
        if (strlen(historiqueCommandes[i]) > 0){
            printf("%d : %s\n", i, historiqueCommandes[i]);
        }
    }
}

//-----------------------------------------
//
//          historiseCommande
//
//-----------------------------------------
void historiseCommande(char *ligneCommande){
    // pas d'historisation si deja dans l'historique
    for (int i = 0 ; i < NB_COMMANDE_HISTORIQUE ; i ++){
        if (strcmp(ligneCommande, historiqueCommandes[i]) == 0) return;
    }
    for (int i = (NB_COMMANDE_HISTORIQUE - 1) ; i >= 0 ; i--){
        //printf("historisation : deplacment de la commande %s de la position %d vers %d", historiqueCommandes[i], i+1, i);
        strcpy(historiqueCommandes[i], historiqueCommandes[i - 1]);
    }
    strcpy(historiqueCommandes[0], ligneCommande);
    //log(LOG_INFO, "historise la commande '%s'", ligneCommande);
}

//-----------------------------------------
//
//          changeLogLevel
//
//-----------------------------------------
void changeLogLevel(char *logLevel){
    if (strncmp(logLevel, "debug", 5) == 0) setLogLevel(LOG_DEBUG);
    else if (strncmp(logLevel, "erreur", 6) == 0) setLogLevel(LOG_ERROR);
    else if (strncmp(logLevel, "warning", 7) == 0) setLogLevel(LOG_WARNING);
    else if (strncmp(logLevel, "info", 4) == 0) setLogLevel(LOG_INFO);
    else if (strncmp(logLevel, "none", 4) == 0) setLogLevel(LOG_NONE);
    else log(LOG_ERROR, "miveau de log <%s> inconnu ; voir l'aide", logLevel);
}

//-----------------------------------------
//
//          analyseLigneCommande
//
//-----------------------------------------
void analyseLigneCommande(char *ligneCommande){
    log(LOG_DEBUG, "analyseLigneCommande => debut");
    remove_extra_spaces(ligneCommande);
    if (strncmp(ligneCommande, "cree", 4) == 0){
        commandeCree(&(ligneCommande[5]));
    } else if (strncmp(ligneCommande, "commandes", 9) == 0) {
        civilisation.listeCommandesEtVariables();
    } else if (strncmp(ligneCommande, "historique", 10) == 0) {
        afficheHistorique();
    } else if (strncmp(ligneCommande, "liste", 5) == 0) {
        if (strlen(ligneCommande) > 5){
            char *tmp = &(ligneCommande[6]);
            if (strtol(&ligneCommande[6], NULL, 10) != 0){
                civilisation.listeElement(atoi(tmp));
            } else {
                bool res;
                if (strncmp(tmp, "humain", 6) == 0){
                    displayListeHumains = !displayListeHumains;
                    res = displayListeHumains;
                } else if (strncmp(tmp, "entreprise", 10) == 0){
                    displayListeEntreprises = !displayListeEntreprises;
                    res = displayListeEntreprises;
                } else if (strncmp(tmp, "banque", 6) == 0){
                    displayListeBanques = !displayListeBanques;
                    res = displayListeBanques;
                } else {
                    log(LOG_ERROR, "parametre de la commande 'liste' inconnu : %s", tmp);
                    return;
                }
                if (res){
                    log(LOG_INFO, "activation affichage de la liste des '%s'", tmp);
                } else {
                    log(LOG_INFO, "desactivation affichage de la liste des '%s'", tmp);
                }
            }
        }else {
            civilisation.listeCivilisation();
        }
    } else if (strncmp(ligneCommande, "aide", 4) == 0) {
        aide();
    } else if (strncmp(ligneCommande, "quit", 4) == 0) {
        exit(0);
    } else if (strncmp(ligneCommande, "auto", 4) == 0) {
        char *tmpCommande = &(ligneCommande[5]);
        setAuto(tmpCommande);
    } else if (strncmp(ligneCommande, "loglevel", 8) == 0) {
        if (strlen(ligneCommande) > 10){
            changeLogLevel(&(ligneCommande[9]));
        }
    } else {
        printf("commande <%s> inconnue (tapez 'aide' pour la liste des commandes disponibles\n)", ligneCommande);
    }
}
