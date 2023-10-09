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

extern Civilisation civilisation;


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
        civilisation.creeElementEntreprise(typeEntreprise, nom, capital);
    }
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
    } else if (strncmp(ligneCommande, "aide", 9) == 0) {
        aide();
    } else {
        printf("commande <%s> inconnue (tapez 'aide' pour la liste des commandes disponibles\n)", ligneCommande);
    }
}