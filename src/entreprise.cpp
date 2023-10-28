//-----------------------------------------
//
//          entreprise.cpp
//
//-----------------------------------------

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "../inc/entreprise.hpp"
#include "../inc/log.hpp"
#include "../inc/tools.hpp"
#include "../inc/civilisation.hpp"
#include "../inc/aide.hpp"

char listeCommandesEntreprise[NB_COMMANDES_ENTREPRISE][30] = {"produire", "embaucher", "debaucher", "livraison"};
char listeVariablesEntreprise[NB_VARIABLE_ENTREPRISE][20] = {"nom", "nbSalarie", "nbCommande", "stock"};

extern Civilisation civilisation;

//-----------------------------------------
//
//          Entreprise::Entreprise
//
//-----------------------------------------
Entreprise::Entreprise(){
    this->compteBancaireEntreprise = new CompteBancaire((Element*)this);
    for (int i = 0 ; i < MAX_EMPLOYES ; i++){
        listeEmployes[i] = NULL;
    }
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        listeCommandes[i].status = COMMANDE_VIDE;
    }
    cptRefCommande = 0;
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
void Entreprise::initEntreprise(int id, int activite, char *nom, int capitalInitial, Entreprise *maisonMere){
    //log(LOG_DEBUG, "Entreprise::initEntreprise : debut");
    this->id = id;
    this->activite = activite;
    this->nbCommandes = 0;
    this->maxEmployes = 0;
    this->nbSalaries = 0;
    this->maisonMere = NULL;
    this->nbDemandeEmbauche = 0;
    this->capitalInitial = capitalInitial;
    strcpy(this->nom ,nom);
    // lecture du fichier de définition de l'entreprise
    char filename[100];
    char repertoire[50] = "scripts/entreprises";
    char ligne[100];
    char *tmp;
    compteBancaireEntreprise = new CompteBancaire((Element *)this, capitalInitial);
    snprintf(filename, sizeof(filename), "%s/%s", repertoire, nom);
    FILE *fic;
    fic = fopen(filename, "r");
    if (fic == NULL){
        log(LOG_ERROR, "Impossible d'ouvrir le fichier de définition d'entreprise %s", filename );
        snprintf(filename, sizeof(filename),"%s/default", repertoire);
        log(LOG_WARNING, "        ouverture du fichier par defaut %s", filename );
        fic = fopen(filename, "r");
        if (fic == NULL){
            log(LOG_ERROR, "Impossible d'ouvrir le fichier par defaut de définition d'entreprise %s", filename );
            exit(-1);  
        }
    }
    // lecture et analyse du fichier de definition entreprise
    int nbVariablesObligatoires = NB_VARIABLES_SCRIPT_OBLIGATOIRES;
    while (!feof(fic)){
        strcpy(ligne,"");
        fgets(ligne, 100, fic);
        ligne[strlen(ligne) - 1] = '\0';
        if (strncmp(ligne, "nom", 3) == 0){
            tmp = &ligne[3];
            while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
            strcpy(this->nomCommercial, tmp);
            nbVariablesObligatoires--;
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
            nbVariablesObligatoires--;
            //printf("cout salarie :  <%s> <%d>\n", tmp, this->coutSalarie);
        } else if (strncmp(ligne, "prix produit", 11) == 0){
            tmp = &ligne[13];
            while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
            this->prixProduit = atoi(tmp);
            nbVariablesObligatoires--;
            //printf("prix produit :  <%s> <%d>\n", tmp, this->prixProduit);
        } else if (strncmp(ligne, "cout produit", 11) == 0){
            tmp = &ligne[13];
            while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
            this->coutProduit = atoi(tmp);
            nbVariablesObligatoires--;
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
            nbVariablesObligatoires--;
            //printf("maxEmployes  :  <%s> <%d>\n", tmp,this->maxEmployes);
        } else if (strncmp(ligne, "productiviteSalarie", 19) == 0){
            tmp = &ligne[19];
            while ((tmp[0] == ' ') || (tmp[0] == '=')) tmp++;
            this->productiviteSalarie = atoi(tmp);
            nbVariablesObligatoires--;
            //printf("maxEmployes  :  <%s> <%d>\n", tmp,this->maxEmployes);
        }
    }
    if (nbVariablesObligatoires != 0){
        log(LOG_ERROR, "ERREUR, il manque au moins une des variables obligatoires");
        aide();
        exit(-1);
    }
    fclose(fic);
}

//-----------------------------------------
//
//          Entreprise::creeCommande
//
//-----------------------------------------
structCommande *Entreprise::creeCommande(Humain *client, int quantite){
    //bool result = false;
    // recherche si dans les filliales une des entreprise a moins de commandes en cours
    // traitement uniquement pour la maison mere
    if (getNbCommandes() >= MAX_COMMANDES){
        if (this->maisonMere == NULL){
            log(LOG_DEBUG, "recherche si une filiale est moins chargee en commande");
            int minCommande = nbCommandes;
            Entreprise *candidateGestionCommande = this;
            for (int i = 0 ; i < MAX_FILIALES ; i++){
                if (listeFiliales[i] != NULL){
                    Entreprise *filiale = listeFiliales[i];
                    if (filiale->getNbCommandes() < minCommande){
                        candidateGestionCommande = filiale;
                        minCommande = filiale->getNbCommandes();
                    }
                }
            }
            if (candidateGestionCommande != this){
                // une filiale est moins chargee, on lui transfere cette commande
                log(LOG_INFO, "on transfere la commande a l'entreprise %s (%d)", candidateGestionCommande->getNomEntreprise(), candidateGestionCommande->getIdEntreprise());
                return candidateGestionCommande->creeCommande(client, quantite);
            }
        }
    } else {
        log(LOG_DEBUG, "Entreprise::creeCommande => TODO");
        log(LOG_DEBUG, "Entreprise::creeCommande %s passe commande de %d à %s (%d)\n", client->getNomHumain(), quantite, getNomEntreprise(), getIdEntreprise());
        for (int i = 0 ; i < MAX_COMMANDES ; i++){
            structCommande *tmpCde = &listeCommandes[i];
            if (tmpCde->status == COMMANDE_VIDE){
                tmpCde->client = client;
                tmpCde->reference = cptRefCommande++;
                tmpCde->quantité = quantite;
                tmpCde->prixUnitaire = this->prixProduit;
                tmpCde->status = COMMANDE_INIT;
                log(LOG_DEBUG, "Entreprise::creeCommande => commande enregistree avec succes (id = %d)", i);
                nbCommandes++;
                return tmpCde;
            }
        }
    }
    log(LOG_DEBUG, "Entreprise::creeCommande le tableau des commandes est plein\n");
    return NULL;
}

//-----------------------------------------
//
//          Entreprise::gereLivraison
//
//-----------------------------------------
void Entreprise::gereLivraisons(void){
    log(LOG_DEBUG, "Entreprise::gereLivraisons");
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        if (listeCommandes[i].client != NULL){
            livraison(listeCommandes[i].client);
        }
    }

}

//-----------------------------------------
//
//          Entreprise::livraison
//
//-----------------------------------------
void Entreprise::livraison(Humain *client){
    //bool result = false;
    //log(LOG_DEBUG, "Entreprise::livraison => TODO");
    log(LOG_DEBUG, "Entreprise::livraison à %s", client->getNomHumain());
    for (int i = 0 ; i < MAX_COMMANDES ; i++){
        structCommande *tmpCde = &listeCommandes[i];
        if (tmpCde->client == client){
            if (stock > 0){
                log(LOG_DEBUG, "livraison de %d produit a %s", tmpCde->quantité, client->getNomHumain());
                client->valideAchatProduit(this, prixProduit);
                tmpCde->client = NULL;
                tmpCde->reference = -1;
                tmpCde->quantité = -1;
                tmpCde->prixUnitaire = -1;
                tmpCde->status = COMMANDE_VIDE;
                nbCommandes--;
                stock--;
            } else {
                // plus de stock on arrete le processus de livraison
                log(LOG_ERROR, "livraison de %d produit a %s impossible (pas assez de stock)", tmpCde->quantité, client->getNomHumain());
                return;
            }

            //return;
        }
        //break;
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
//          Entreprise::getProductiviteSalaries
//
//-----------------------------------------
int Entreprise::getProductiviteSalarie(void){
    return productiviteSalarie;
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
//          Entreprise::getNomEntreprise
//
//-----------------------------------------
char *Entreprise::getNomEntreprise(void){
    return nom;
}

//-----------------------------------------
//
//          Entreprise::getNomCommercialEntreprise
//
//-----------------------------------------
char *Entreprise::getNomCommercialEntreprise(void){
    return nomCommercial;
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
            // .... TODO ... prevoir comment payer le cout produit a un compte bancaire fictif
            compteBancaireEntreprise->virement(compteBancaireFournisseurNull, (coutProduit * productiviteSalarie));
            log(LOG_INFO,"%s verse un salaire de %d a %s", nom, coutSalarie, employe->getNomHumain());
            compteBancaireEntreprise->virement(employe->compteBancaireHumain, coutSalarie);
            nbProduitsFabriques += productiviteSalarie;
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

    // verification si l'entreprise peut l'embaucher
    if (getNbSalaries() >= maxEmployes){
        log(LOG_INFO, "l'entreprise %s a ateint son nombre maximal d'employes(%d)", getNomEntreprise(), maxEmployes);
        if (maisonMere == NULL){
            log(LOG_DEBUG, "la maison mere recherche une filiale de %s capable d'embaucher", this->nom);
            // recherche dans les filiales d'une entreprise n'ayant pas atteint son nombre max de salarie
            for (int j = 0 ; j < MAX_FILIALES ; j ++){
                Entreprise *filiale = listeFiliales[j];
                if (filiale != NULL){
                    if (filiale->getNbSalaries() < maxEmployes){
                        // cette filiale peut embaucher
                        if (filiale->embaucher()){
                            // l'embauche est OK, on peu quitter
                            return true;
                        }
                    }
                }
            }
            // on a pas trouvé de filiale capable d'embaucher
            // on essaie d'en creer une nouvelle
            int j = 0;
            for (j = 0 ; j < MAX_FILIALES ; j++){
                log(LOG_INFO, "creation d'une filiale pour l'entreprise %s", this->nom);
                Entreprise *filiale = civilisation.dupliqueEntreprise(this);
                if (listeFiliales[j] == NULL){
                    listeFiliales[j] = filiale;
                    return filiale->embaucher();
                    break;
                }
            }
            if (j >= MAX_FILIALES){
                log(LOG_ERROR, "ERREUR : nombre max de filliale (%d) atteint pour %s", MAX_FILIALES, this->getNomEntreprise());
                return false;
            }
        } else {
            log(LOG_DEBUG, "on est dans une filiale, on ne peut pas creer de sous filiale");
        }
    } 
    // recherche d'une personne libre pouvant etre embauchee
    log(LOG_DEBUG, "l'entreprise %s (%d) peut embaucher .... ", this->nom, getIdEntreprise());
    Humain *tmpSalarie = Civilisation::getSalarie();
    if (tmpSalarie != NULL){
        for (int i = 0 ; i < maxEmployes ; i++){
            if (listeEmployes[i] == NULL){
                listeEmployes[i] = tmpSalarie;
                tmpSalarie->setEmployeur(this);
                nbSalaries++;
                log(LOG_INFO, "l'entreprise %s (%d) a embauché le salarie %s", getNomEntreprise(), getIdEntreprise(), tmpSalarie->getNomHumain());
                return true;
            }
        }
    }else {
        log(LOG_INFO, "l'entreprise %s n'a pas trouve de salarie a embaucher", getNomEntreprise());
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
    for (int i = 0 ; i < NB_VARIABLE_ENTREPRISE ; i++){
        strcat(tmpDataEntreprise, listeVariablesEntreprise[i]);
        strcat(tmpDataEntreprise,", ");
    }
    strcat(tmpDataEntreprise, "\n");

    strcat(tmpDataEntreprise,"liste des commandes Entreprise : ");
    for (int i = 0 ; i < NB_COMMANDES_ENTREPRISE ; i++){
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
    if (nbSalaries == 0) return true;
    log(LOG_DEBUG,"Humain::debaucher : TODO modifier pour selectionner aleatoirement un salarie");
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
                case 3: // livraison
                    gereLivraisons();
                    return true;
                    break;
            }
            break;
        } 
    }
    log(LOG_ERROR, "commande <%s> inconnue", valeur);

    return false;
}

//-----------------------------------------
//
//          Entreprise::evalueExpression
//
//-----------------------------------------
bool Entreprise::evalueExpressionEntreprise(char *expression){
    int val1;
    int val2;
    //bool res = false;
    char data1[30], op[5], data2[30];
    int i = 0, j = 0;
    log(LOG_DEBUG, "Entreprise::evalueExpressionHumain => debut : calcul de '%s'", expression);

    // decomposition de l'expression
    while ((expression[i] != ' ') && (i < strlen(expression))){
        data1[j++] = expression[i++];
        data1[j] = '\0';
    } 
    j=0;
    if (i >= strlen(expression)) return false;
    while((expression[i] == ' ') && (i < strlen(expression))) i++;
    while ((expression[i] != ' ') && (i < strlen(expression))){
        putchar(expression[i]);
        op[j++] = expression[i++];
        op[j] = '\0';
    } 
    j=0;
    if (i >= strlen(expression)) return false;
    while((expression[i] == ' ') && (i < strlen(expression))) i++;
    while ((expression[i] != ' ') && (i < strlen(expression))){
        data2[j++] = expression[i++];
        data2[j] = '\0';
    } 
    log(LOG_DEBUG, "Entreprise::evalueExpressionHumain => resultat decomposition : '%s' '%s' '%s'", data1, op, data2);

    if (Entreprise::isVariable(data1)){
        val1 = getIntValue(data1);
        log(LOG_DEBUG, "Entreprise::evalueExpressionHumain => data1 est une variable : '%s' => '%d'\n", data1, val1);
    } else {
        val1 = atoi(data1);
    }
    if (Entreprise::isVariable(data2)){
        val2 = getIntValue(data2);
        log(LOG_DEBUG, "Entreprise::evalueExpressionHumain => data2 est une variable : '%s' => '%d'\n", data2, val2);
    } else {
        val2 = atoi(data2);
    }
    log(LOG_DEBUG, "Entreprise::evalueExpressionHumain => apres evaluation : calcul de '%d' '%s' '%d'\n", val1, op, val2);
    return evaluationExpressionInt(val1, op, val2);
    //return res;
}

//-----------------------------------------
//
//          Entreprise::getIntValue
//
//-----------------------------------------
int Entreprise::getIntValue(char *valeur){
    if (strcmp(valeur, "stock") == 0){
        //printf("Entreprise::getIntValue : variable %s = %d\n", valeur, sexe);
        return stock;
    }
    if (strcmp(valeur, "nbCommande") == 0){
        //printf("Entreprise::getIntValue : variable %s = %d\n", valeur, age);
        return nbCommandes;
    }
    if (strcmp(valeur, "nbSalarie") == 0){
        //printf("Entreprise::getIntValue : variable %s = %d\n", valeur, statusMarital);
        return nbSalaries;
    }
    printf("Humain::getIntValue : pas trouve d'équivalence pour %s\n", valeur);
    return -1;
}

//-----------------------------------------
//
//          Entreprise::isVariable
//
//-----------------------------------------
bool Entreprise::isVariable(char *valeur){
    //printf("isvariable : test de la variable %s\n", valeur);
    char *tmp;

    //log(LOG_DEBUG, "TODO : a finir de developper");
    for (int i = 0 ; i < NB_VARIABLE_ENTREPRISE ; i++){
        tmp = listeVariablesEntreprise[i];
        if (strcmp(tmp, valeur) == 0) {
            return true;
        } else {
            //log(LOG_ERROR, "commande <%s> inconnue", valeur);
        }
    }
    return false;
}
//-----------------------------------------
//
//          Entreprise::getIntValue
//
//-----------------------------------------
int Entreprise::getCapitalInitial(void){
    return capitalInitial;
}