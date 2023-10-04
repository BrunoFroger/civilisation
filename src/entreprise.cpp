//-----------------------------------------
//
//          entreprise.hpp
//
//-----------------------------------------

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "../inc/entreprise.hpp"
#include "../inc/log.hpp"
#include "../inc/tools.hpp"
#include "../inc/civilisation.hpp"

char listeCommandesEntreprise[NB_COMMANDES_ENTREPRISE][30] = {"produire", "embaucher", "debaucher"};
char listeVariablesEntreprise[NB_VARIABLE_ENTREPRISE][20] = {"nom", "nbSalarie", "nbCommande"};

//-----------------------------------------
//
//          Entreprise::Entreprise
//
//-----------------------------------------
Entreprise::Entreprise(){
    this->compteBancaireEntreprise = new CompteBancaire();
    for (int i = 0 ; i < MAX_EMPLOYES ; i++){
        listeEmployes[i] = NULL;
    }
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        listeCommandes[i].status = COMMANDE_VIDE;
    }
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
    this->nbSalaries = 0;
    strcpy(this->nom ,nom);
    // lecture du fichier de définition de l'entreprise
    char filename[100];
    char repertoire[50] = "scripts/entreprises";
    char ligne[100];
    char *tmp;
    compteBancaireEntreprise = new CompteBancaire(capitalInitial);
    snprintf(filename, sizeof(filename), "%s/%s", repertoire, nom);
    FILE *fic;
    fic = fopen(filename, "r");
    if (fic == NULL){
        log(LOG_ERROR, "Impossible d'ouvrir le fichier de définition d'entreprise %s\n", filename );
        snprintf(filename, sizeof(filename),"%s/default", repertoire);
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
    return newRef;
}

//-----------------------------------------
//
//          Entreprise::creeCommande
//
//-----------------------------------------
structCommande *Entreprise::creeCommande(Humain *client, int quantite){
    //bool result = false;
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
            log(LOG_DEBUG, "Entreprise::creeCommande enregistree avec succes (id = %d)", i);
            nbCommandes++;
            return tmpCde;
        }
    }
    log(LOG_DEBUG, "Entreprise::creeCommande le tableau des commandes est plein\n");
    return NULL;
}

//-----------------------------------------
//
//          Entreprise::livraison
//
//-----------------------------------------
void Entreprise::livraison(Humain *client){
    //bool result = false;
    log(LOG_DEBUG, "Entreprise::livraison => TODO");
    log(LOG_DEBUG, "Entreprise::livraison à %s \n", client->getNomHumain());
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        structCommande *tmpCde = &listeCommandes[i];
        if (tmpCde->client == client){
            log(LOG_DEBUG, "livraison de %d produit a %s", tmpCde->quantité, client->getNomHumain());
            client->valideAchatProduit(this, prixProduit);
            tmpCde->client = NULL;
            tmpCde->reference = -1;
            tmpCde->quantité = -1;
            tmpCde->prixUnitaire = -1;
            tmpCde->status = COMMANDE_VIDE;
            nbCommandes--;
            return;
        }
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
    log(LOG_INFO, "Entreprise::evolution => evolution de %s", this->nom);
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
    printf("| nb Salaries   |     %25d   |\n", this->nbSalaries);
    printf("| cout/Salaries |     %25d   |\n", this->coutSalarie);
    printf("| max Salaries  |     %25d   |\n", this->maxEmployes);
    printf("| prix Produit  |     %25d   |\n", this->prixProduit);
    printf("| stock Produit |     %25d   |\n", this->stock);
    printf("| nb commandes  |     %25d   |\n", this->nbCommandes);
    printf("| cpt bancaire  |     %25d   |\n", this->compteBancaireEntreprise->getSolde());
    printf("| epargne       |     %25d   |\n", this->compteBancaireEntreprise->getEpargne());
    printf("+---------------+---------------------------------+\n");
}

//-----------------------------------------
//
//          Entreprise::testSiCommandeValideEntreprise
//
//-----------------------------------------
bool Entreprise::testSiCommandeValideEntreprise(char *valeur){
    //printf("test si commande '%s' valide\n", valeur);
    for (int i = 0 ; i < NB_COMMANDES_ENTREPRISE ; i++){
        //printf("comparaison avec %s : ", listeCommandesEntreprise[i]);
        if (strcmp(valeur, listeCommandesEntreprise[i]) == 0) {
            //printf("OK\n");
            return true;
        } else {
            //printf("NOK\n");
        }
    }
    return false;
}

//-----------------------------------------
//
//          Entreprise::testSiListeCommandeValideEntreprise
//
//-----------------------------------------
bool Entreprise::testSiListeCommandeValideEntreprise(char *valeur){
    char *tmp;
    tmp = &valeur[0];
    char buffer[50];
    int i;
    while (tmp[0] != '\0'){
        i=0;
        strcpy(buffer,"");
        while (*tmp == ' ') tmp++;  // suppression des blancs au debut
        if (strlen(tmp) == 0) return true;
        while (*tmp != ' '){
            buffer[i++] = *tmp++;
            buffer[i] = '\0';
        }
        if (strlen(buffer) != 0){
            if (!testSiCommandeValideEntreprise(buffer)){
                log(LOG_ERROR, "commande %s inconnue", buffer);
                return false;
            }
        }
    }
    return true;
}

//-----------------------------------------
//
//          Entreprise::produire
//
//-----------------------------------------
bool Entreprise::produire(){
    int nbProduitsFabriques = 0;
    log(LOG_DEBUG,"Humain::produire : TODO");
    for (int i = 0 ; i < MAX_EMPLOYES ; i++){
        Humain *employe = listeEmployes[i];
        if (employe != NULL){
            compteBancaireEntreprise->virement(NULL, coutProduit);
            compteBancaireEntreprise->virement(employe->compteBancaireHumain, coutSalarie);
            nbProduitsFabriques++;
        }
    }
    stock += nbProduitsFabriques;
    log(LOG_DEBUG, "Humain::produire : %d produits fabriques", nbProduitsFabriques);
    return true;
}

//-----------------------------------------
//
//          Entreprise::embaucher
//
//-----------------------------------------
bool Entreprise::embaucher(void){
    log(LOG_DEBUG,"Humain::embaucher : TODO modifier pour trouver aleatoirement un salarie");
    Humain *tmpSalarie = Civilisation::getSalarie();
    if (tmpSalarie != NULL){
        for (int i = 0 ; i < MAX_EMPLOYES ; i++){
            if (listeEmployes[i] == NULL){
                listeEmployes[i] = tmpSalarie;
                tmpSalarie->setEmployeur(this);
                nbSalaries++;
                return true;
            }
        }
    }
    return false;
}

//-----------------------------------------
//
//          Entreprise::listeVariables
//
//-----------------------------------------
char tmpDataEntreprise[5000];
char *Entreprise::listeVariables(void){
    strcpy(tmpDataEntreprise, "");
    strcat(tmpDataEntreprise,"liste des variables Entreprise : ");
    for (int i = 0 ; i < NB_VARIABLE_HUMAIN ; i++){
        strcat(tmpDataEntreprise, listeVariablesEntreprise[i]);
        strcat(tmpDataEntreprise,", ");
    }
    strcat(tmpDataEntreprise, "\n");

    strcat(tmpDataEntreprise,"liste des commandes Entreprise : ");
    for (int i = 0 ; i < NB_COMMANDES_HUMAIN ; i++){
        strcat(tmpDataEntreprise, listeCommandesEntreprise[i]);
        strcat(tmpDataEntreprise,", ");
    }
    strcat(tmpDataEntreprise, "\n");
    return tmpDataEntreprise;
}

//-----------------------------------------
//
//          Entreprise:debaucher
//
//-----------------------------------------
bool Entreprise::debaucher(void){
    log(LOG_DEBUG,"Humain::debaucher : TODO modifier pour trouver aleatoirement un salarie");
    for (int i = 0 ; i < MAX_EMPLOYES ; i++){
        Humain *employe = listeEmployes[i];
        if (employe != NULL){
            employe->setEmployeur(NULL);
            employe = NULL;
            nbSalaries--;
            return true;
        }
    }
    return false;
}

//-----------------------------------------
//
//          Entreprise:demission
//
//-----------------------------------------
bool Entreprise::demission(Humain *salarie){
    log(LOG_DEBUG,"Humain::demission : TODO");
    for (int i = 0 ; i < MAX_EMPLOYES ; i++){
        Humain *employe = listeEmployes[i];
        if (employe == salarie){
            employe->setEmployeur(NULL);
            employe = NULL;
            nbSalaries--;
            return true;
        }
    }
    return false;
}

//-----------------------------------------
//
//          Entreprise::execCommandeEntreprise
//
//-----------------------------------------
bool Entreprise::execCommandeEntreprise(char *valeur){
    log(LOG_DEBUG,"Humain::execCommandeEntreprise <%s> : TODO", valeur);
    for (int i = 0 ; i < NB_COMMANDES_ENTREPRISE ; i++){
        if (strcmp(listeCommandesEntreprise[i], valeur) == 0){
            switch(i){ 
                case 0: // produire
                    produire();
                    return true;
                    break;
                case 1: // embaucher
                    embaucher();
                    return true;
                    break;
                case 2: // debaucher
                    debaucher();
                    return true;
                    break;
            }
            break;
        } 
    }
    log(LOG_ERROR, "commande <%s> inconnue", valeur);

    return false;
}
