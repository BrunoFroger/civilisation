//-----------------------------------------
//
//          humain.hpp
//
//-----------------------------------------

#ifndef __HUMAIN__
#define __HUMAIN__

    #include "../inc/compteBancaire.hpp"

    #define HOMME   0
    #define FEMME   1

    #define MAX_ENFANTS 5

    #define STATUS_MARITAL_CELIB    0
    #define STATUS_MARITAL_MARIE    1
    #define STATUS_MARITAL_VEUF     2
    #define STATUS_MARITAL_DIVOR    3
    #define STATUS_MARITAL_DECES    4

    #define NB_COMMANDES_HUMAIN     7
    #define NB_VARIABLE_HUMAIN      5
    #define NB_VARIABLE_SCRIPT_HUM  10

    class Entreprise;

    typedef struct{
        char nom[50];
        char valeur[50];
    } structVariableHumain;

    class Humain{
        public:
            Humain();
            Humain(int id, int sexe, char *nom, int capitalInitial);
            void acheteProduit(Entreprise *entreprise, int quantite);
            void ajouteEnfant(Humain *enfant);
            void ajouteParents(Humain *pere, Humain *mere);
            int calculExpressionHumain(char *data1, char op, char *data2);
            bool evalueExpressionHumain(char *expression);
            void evolutionHumain(void);
            bool execCommandeHumain(char *commande);
            int getAge();
            char *getCharValue(char *nomVariable);
            int getConjoint(void);
            Entreprise *getEmployeur(void);
            int getIdHumain();
            int getIntValue(char *nomVariable);
            int getMere(void);
            char *getNomHumain();
            int getNbEnfants(void);
            int getPere(void);
            int getSexe();
            char getSexeChar();
            char *getSexeString();
            int getStatusMarital();
            void initHumain(int id, int sexe, char *nom, int capitalInitial);
            bool isVariable(char *nomVariable);
            void listeHumain(void);
            static char *listeVariables(void);
            void setConjoint(Humain *pretendant);
            void setEmployeur(Entreprise *entreprise);
            void setNom(char *nom);
            void setSexe(int sexe);
            void setStatusMarital(int status);
            bool testSiCommandeValideHumain(char *valeur);
            bool testSiListeCommandeValideHumain(char *valeur);
            void valideAchatProduit(Entreprise *entreprise, int montant);
            char *getVariable(char *nom);
            bool setVariable(char *valeur);
            bool unsetVariable(char *valeur);
            
            CompteBancaire *compteBancaireHumain;

        private:
            int id;
            int sexe;   // 0 : homme, 1 = femme
            char nom[50];
            int age;
            int statusMarital;
            int nbEnfants;
            Entreprise *employeur;    // -1 => sans emploi
            void mortPossible(void);
            bool chercheConjoint(void);
            bool naissancePossible(void);
            Humain *pere;
            Humain *mere;
            Humain *conjoint;
            Humain *enfants[MAX_ENFANTS];
            structVariableHumain variablesDeScriptHumain[NB_VARIABLE_SCRIPT_HUM];
    };

#endif