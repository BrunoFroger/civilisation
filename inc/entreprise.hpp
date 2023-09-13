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

    #define NB_COMMANDES_ENTREPRISE 3
    #define NB_VARIABLE_ENTREPRISE  3

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
            void initEntreprise(int id, int activite, char *nom, int capital);
            void evolutionEntreprise(void);
            int getIdEntreprise();
            char *getNomEntreprise();
            int getActivite();
            int getNbSalaries();
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
            bool testSiCommandeValideEntreprise(char *valeur);
            bool testSiListeCommandeValideEntreprise(char *valeur);
            bool execCommandeEntreprise(char *commande);
            bool demission(Humain *salarie);
            static char *listeVariables(void);

        private:
            int id;
            int activite;
            char nom[50];
            int nbSalaries;
            int coutSalarie;
            int coutProduit;
            int prixProduit;
            int stock;
            int nbCommandes;
            int maxEmployes;
            Humain  *listeEmployes[MAX_EMPLOYES];
            structCommande listeCommandes[MAX_COMMANDES];
            int getRefCommande(void);
            bool produire();
            bool embaucher();
            bool debaucher();
            Humain *getSalarie(void);
    };

#endif