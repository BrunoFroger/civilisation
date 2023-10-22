//-----------------------------------------
//
//          entreprise.hpp
//
//-----------------------------------------

#ifndef __ENTREPRISE__
#define __ENTREPRISE__

    #include "../inc/compteBancaire.hpp"

    #define ACTIVITE_INCONNUE   0
    #define ACTIVITE_COMMERCE   1
    #define ACTIVITE_INDUSTRIE  2

    #define MAX_FILIALES    10

    #define MAX_EMPLOYES    25
    #define MAX_COMMANDES   50

    #define COMMANDE_VIDE       -1
    #define COMMANDE_INIT       0
    #define COMMANDE_RECUE      1
    #define COMMANDE_EN_COURS   2
    #define COMMANDE_TRAITEE    3
    #define COMMANDE_LIVREE     4
    #define COMMANDE_REGLEE     5
    #define COMMANDE_FERMEE     6

    #define NB_COMMANDES_ENTREPRISE 4
    #define NB_VARIABLE_ENTREPRISE  4

    #define NB_VARIABLES_SCRIPT_OBLIGATOIRES   6
    // nom, cout salarie, prix produit, cout produit

    class Humain;

    typedef struct{
        Humain *client;
        int reference;
        int quantité;
        int prixUnitaire;
        int status;
    } structCommande;

    class Entreprise{
        public:
            Entreprise();
            ~Entreprise();
            void initEntreprise(int id, int activite, char *nom, int capital, Entreprise *maisonMere);
            void evolutionEntreprise(void);
            int getIdEntreprise();
            char *getNomEntreprise();
            char *getNomCommercialEntreprise();
            int getActivite();
            int getNbSalaries();
            int getProductiviteSalarie();
            int getCoutSalaries();
            int getCoutProduit();
            int getPrixProduit();
            int getStockProduit();
            int getMaxEmployes(void);
            int getNbCommandes(void);
            CompteBancaire *compteBancaireEntreprise;
            void listeEntreprise(void);
            bool verseSalaire(int salaire, Humain *salarie);
            structCommande *creeCommande(Humain *humain, int quantite);
            void livraison(Humain *humain);
            void gereLivraisons(void);
            bool testSiCommandeValideEntreprise(char *valeur);
            bool testSiListeCommandeValideEntreprise(char *valeur);
            bool execCommandeEntreprise(char *commande);
            bool demission(Humain *salarie);
            static char *listeVariables(void);
            bool evalueExpressionEntreprise(char *expression);
            bool isVariable(char *nomVariable);
            int getIntValue(char *valeur);
            int getCapitalInitial(void);
            bool embaucher();
            bool produire();

        private:
            int id;
            int activite;
            char nom[50];
            char nomCommercial[50];
            int nbSalaries;
            int coutSalarie;
            int coutProduit;
            int prixProduit;
            int productiviteSalarie;
            int stock;
            int nbCommandes;
            int maxEmployes;
            int capitalInitial;
            Humain  *listeEmployes[MAX_EMPLOYES];
            structCommande listeCommandes[MAX_COMMANDES];
            int getRefCommande(void);
            bool debaucher();
            Humain *getSalarie(void);
            Entreprise *maisonMere;
            Entreprise *listeFiliales[MAX_FILIALES];
            int nbDemandeEmbauche;
            Humain *patron;
    };

#endif