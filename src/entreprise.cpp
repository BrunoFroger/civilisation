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
#include "../inc/tools.hpp"

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
    //log(LOG_DEBUG, "Entreprise::initEntreprise : debut");
    this->id = id;
    this->activite = activite;
    this->nbCommandes = 0;
    this->maxEmployes = 0;
    strcpy(this->nom ,nom);
    // lecture du fichier de définition de l'entreprise
    char filename[100];
    char repertoire[50] = "scripts/entreprises";
    char ligne[100];
    char *tmp;
    compteBancaireEntreprise = new CompteBancaire(capitalInitial);
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
    }
    // lecture et analyse du fichier de definition entreprise
    while (!feof(fic)){
        strcpy(ligne,"");
        fgets(ligne, 100, fic);
        ligne[strlen(ligne) - 1] = '\0';
        if (strncmp(ligne, "nom", 3) == 0){
            tmp = &ligne[3];
            while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
            strcpy(this->nom, tmp);
            //printf("nom          :  <%s> <%s>\n", tmp, this->nom);
        } else if (strncmp(ligne, "nbSalarie", 9) == 0){
            tmp = &ligne[9];
            while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
            this->nbSalaries = atoi(tmp);
            //printf("nbSalarie    :  <%s> <%d>\n", tmp, atoi(tmp));
        } else if (strncmp(ligne, "cout Salarie", 11) == 0){
            tmp = &ligne[13];
            while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
            this->coutSalarie = atoi(tmp);
            //printf("cout salarie :  <%s> <%d>\n", tmp, this->coutSalarie);
        } else if (strncmp(ligne, "prix produit", 11) == 0){
            tmp = &ligne[13];
            while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
            this->prixProduit = atoi(tmp);
            //printf("prix produit :  <%s> <%d>\n", tmp, this->prixProduit);
        } else if (strncmp(ligne, "cout produit", 11) == 0){
            tmp = &ligne[13];
            while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
            this->coutProduit = atoi(tmp);
            //printf("cout produit :  <%s> <%d>\n", tmp, this->coutProduit);
        } else if (strncmp(ligne, "stock", 5) == 0){
            tmp = &ligne[5];
            while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
            this->stock = atoi(tmp);
            //printf("stock        :  <%s> <%d>\n", tmp,this->stock);
        } else if (strncmp(ligne, "maxEmployes", 11) == 0){
            tmp = &ligne[11];
            while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
            this->maxEmployes = atoi(tmp);
            //printf("maxEmployes  :  <%s> <%d>\n", tmp,this->maxEmployes);
        }
    }
    fclose(fic);
}

//-----------------------------------------
//
//          Entreprise::getRefCommande
//
//-----------------------------------------
int Entreprise::getRefCommande(void){
    int newRef = 0;
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        if (listeCommandes[i].reference > newRef){
            newRef = listeCommandes[i].reference;
        }
    }
    newRef++;
}

//-----------------------------------------
//
//          Entreprise::creeCommande
//
//-----------------------------------------
structCommande *Entreprise::creeCommande(Humain *client, int quantite){
    bool result = false;
    log(LOG_DEBUG, "Entreprise::creeCommande => TODO");
    log(LOG_DEBUG, "Entreprise::creeCommande %s passe commande de %d\n", client->getNomHumain(), quantite);
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        structCommande *tmpCde = &listeCommandes[i];
        if (tmpCde->status == COMMANDE_VIDE){
            tmpCde->client = client;
            tmpCde->reference = getRefCommande();
            tmpCde->quantité = quantite;
            tmpCde->prixUnitaire = this->prixProduit;
            tmpCde->status = COMMANDE_INIT;
        }
        nbCommandes++;
        break;
    }
    return NULL;
}

//-----------------------------------------
//
//          Entreprise::livraison
//
//-----------------------------------------
void Entreprise::livraison(Humain *client){
    bool result = false;
    log(LOG_DEBUG, "Entreprise::livraison => TODO");
    log(LOG_DEBUG, "Entreprise::livraison à %s \n", client->getNomHumain());
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        structCommande *tmpCde = &listeCommandes[i];
        if (tmpCde->client == client){
            tmpCde->client = NULL;
            tmpCde->reference = -1;
            tmpCde->quantité = -1;
            tmpCde->prixUnitaire = -1;
            tmpCde->status = COMMANDE_VIDE;
        }
        nbCommandes--;
        break;
    }
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
//          Entreprise::getMaxEmployes
//
//-----------------------------------------
int Entreprise::getMaxEmployes(void){
    return maxEmployes;
}

//-----------------------------------------
//
//          Entreprise::getNbCommandes
//
//-----------------------------------------
int Entreprise::getNbCommandes(void){
    return nbCommandes;
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
//          Entreprise::verseSalaire
//
//-----------------------------------------
bool Entreprise::verseSalaire(int salaire, Humain *salarie){
    if (compteBancaireEntreprise->getSolde() < salaire){
        printf("errreur : l'entreprise n'a pas asssez de fond pour payer le salaire\n");
        return false;
    }
    this->compteBancaireEntreprise->virement(salarie->compteBancaireHumain, salaire);
    return true;
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

//-----------------------------------------
//
//          Entreprise::listeEntreprise
//
//-----------------------------------------
void Entreprise::listeEntreprise(void){
    char tmp[30];
    printf("+-------------------------------------------------+\n");
    printf("|  donnees entreprise (id = %5d)                |\n", this->id);
    printf("+---------------+---------------------------------+\n");
    printf("| donnee        |     valeur                      |\n");
    printf("+---------------+---------------------------------+\n");
    switch(this->activite){
        case ACTIVITE_COMMERCE:
            strcpy(tmp,"commerce");
            break;
        case ACTIVITE_INDUSTRIE:
            strcpy(tmp,"industrie");
            break;
        default:
            strcpy(tmp,"inconnue");
            break;
    }
    printf("| activité      |     %25s   |\n", tmp);
    printf("| nom           |     %25s   |\n", this->nom);
    printf("| nb Salaries   |               %15d   |\n", this->nbSalaries);
    printf("| cout/Salaries |               %15d   |\n", this->coutSalarie);
    printf("| max Salaries  |               %15d   |\n", this->maxEmployes);
    printf("| prix Produit  |               %15d   |\n", this->prixProduit);
    printf("| stock Produit |               %15d   |\n", this->stock);
    printf("| nb commandes  |               %15d   |\n", this->nbCommandes);
    printf("| cpt bancaire  |               %15d   |\n", this->compteBancaireEntreprise->getSolde());
    printf("| epargne       |               %15d   |\n", this->compteBancaireEntreprise->getEpargne());
    printf("+---------------+---------------------------------+\n");
}
