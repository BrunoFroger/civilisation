//-----------------------------------------
//
//          entreprise.hpp
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/entreprise.hpp"
#include "../inc/log.hpp"

//-----------------------------------------
//
//          Entreprise::Entreprise
//
//-----------------------------------------
Entreprise::Entreprise(){
    this->compteBancaireEntreprise = new CompteBancaire();
}

//-----------------------------------------
//
//          Entreprise::~Entreprise
//
//-----------------------------------------
Entreprise::~Entreprise(){
    delete this->compteBancaireEntreprise;
}

//-----------------------------------------
//
//          Entreprise::initEntreprise
//
//-----------------------------------------
void Entreprise::initEntreprise(int id, int activite, char *nom, int capitalInitial){
    log(LOG_DEBUG, "Entreprise::initEntreprise : debut");
    this->id = id;
    this->activite = activite;
    strcpy(this->nom ,nom);
    // lecture du fichier de définition de l'entreprise
    char filename[100];
    char repertoire[50] = "scripts/entreprises/";
    char ligne[100];
    char *tmp;
    sprintf(filename, "%s/%s", repertoire, nom);
    FILE *fic;
    fic = fopen(filename, "r");
    if (fic == NULL){
        log(LOG_ERROR, "Impossible d'ouvrir le fichier de définition d'entreprise %s\n", filename );
        sprintf(filename, "%s/default", repertoire);
        log(LOG_ERROR, "        ouverture du fichier par defaut %s\n", filename );
        fic = fopen(filename, "r");
        if (fic == NULL){
            log(LOG_ERROR, "Impossible d'ouvrir le fichier par defaut de définition d'entreprise %s\n", filename );
            exit(-1);  
        }
    } else {
        // lecture et analyse du fichier de definition entreprise
        while (!feof(fic)){
            strcpy(ligne,"");
            fgets(ligne, 100, fic);
            ligne[strlen(ligne) - 1] = '\0';
            if (strncmp(ligne, "nom", 3) == 0){
                tmp = &ligne[3];
                while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
                printf("nom          :  <%s>\n", tmp);
                strcpy(this->nom, tmp);
            } else if (strncmp(ligne, "nbSalarie", 9) == 0){
                tmp = &ligne[9];
                while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
                printf("nbSalarie    :  <%s>\n", tmp);
                this->nbSalaries = atoi(tmp);
            } else if (strncmp(ligne, "cout Salarie", 11) == 0){
                tmp = &ligne[13];
                while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
                printf("cout salarie :  <%s>\n", tmp);
                this->coutSalarie = atoi(tmp);
            } else if (strncmp(ligne, "prix produit", 11) == 0){
                tmp = &ligne[13];
                while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
                printf("prix produit :  <%s>\n", tmp);
                this->prixProduit = atoi(tmp);
            } else if (strncmp(ligne, "cout produit", 11) == 0){
                tmp = &ligne[13];
                while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
                printf("cout produit :  <%s>\n", tmp);
                this->coutProduit = atoi(tmp);
            } else if (strncmp(ligne, "stock", 5) == 0){
                tmp = &ligne[5];
                while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
                printf("stock        :  <%s>\n", tmp);
                this->stock = atoi(tmp);
            }
        }
    }
    fclose(fic);
}

//-----------------------------------------
//
//          Entreprise::getId
//
//-----------------------------------------
int Entreprise::getIdEntreprise(void){
    return id;
}

//-----------------------------------------
//
//          Entreprise::getId
//
//-----------------------------------------
int Entreprise::getNbSalaries(void){
    return nbSalaries;
}

//-----------------------------------------
//
//          Entreprise::getId
//
//-----------------------------------------
int Entreprise::getCoutSalaries(void){
    return coutSalarie;
}

//-----------------------------------------
//
//          Entreprise::getId
//
//-----------------------------------------
int Entreprise::getCoutProduit(void){
    return coutProduit;
}

//-----------------------------------------
//
//          Entreprise::getId
//
//-----------------------------------------
int Entreprise::getPrixProduit(void){
    return prixProduit;
}

//-----------------------------------------
//
//          Entreprise::getStockProduit
//
//-----------------------------------------
int Entreprise::getStockProduit(void){
    return stock;
}

//-----------------------------------------
//
//          Entreprise::getActivite
//
//-----------------------------------------
int Entreprise::getActivite(void){
    return activite;
}

//-----------------------------------------
//
//          Entreprise::getNom
//
//-----------------------------------------
char *Entreprise::getNomEntreprise(void){
    return nom;
}

//-----------------------------------------
//
//          Entreprise::evolution
//
//-----------------------------------------
void Entreprise::evolutionEntreprise(void){
    log(LOG_DEBUG, "Entreprise::evolution => evolution de %s", this->nom);
    log(LOG_DEBUG, "Entreprise::evolution => TODO");
    // TODO
}
