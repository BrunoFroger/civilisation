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

    #define MAX_ENFANTS 10

    #define STATUS_MARITAL_CELIB    0
    #define STATUS_MARITAL_MARIE    1
    #define STATUS_MARITAL_VEUF     2
    #define STATUS_MARITAL_DIVOR    3
    #define STATUS_MARITAL_DECES    4

    #define NB_COMMANDES_HUMAIN     3
    #define NB_VARIABLE_HUMAIN      5

    class Entreprise;


    class Humain{
        public:
            Humain();
            Humain(int id, int sexe, char *nom, int capitalInitial);
            void initHumain(int id, int sexe, char *nom, int capitalInitial);
            void evolutionHumain(void);
            int getIdHumain();
            char *getNomHumain();
            void setNom(char *nom);
            int getSexe();
            char getSexeChar();
            void setSexe(int sexe);
            int getAge();
            int getStatusMarital();
            static bool isVariable(char *nomVariable);
            int getIntValue(char *nomVariable);
            char *getCharValue(char *nomVariable);
            bool testSiCommandeValideHumain(char *valeur);
            bool testSiListeCommandeValideHumain(char *valeur);
            int calculExpression(char *data1, char op, char *data2);
            bool execCommandeHumain(char *commande);
            CompteBancaire *compteBancaireHumain;
            void listeHumain(void);
            void acheteProduit(Entreprise *entreprise);
            static char *listeVariables(void);
            bool evalueExpressionHumain(char *expression);
            void setConjoint(Humain *pretendant);

        private:
            int id;
            int sexe;   // 0 : homme, 1 = femme
            char nom[50];
            int age;
            int statusMarital;
            int nbEnfants;
            int idEmployeur;    // -1 => sans emploi
            void mortPossible(void);
            void chercheConjoint(void);
            bool naissancePossible(void);
            Humain *conjoint;
            Humain *enfants[MAX_ENFANTS];
    };

#endif