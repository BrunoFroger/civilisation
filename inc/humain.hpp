//-----------------------------------------
//
//          humain.hpp
//
//-----------------------------------------

#ifndef __HUMAIN__
#define __HUMAIN__

    #include "../inc/compteBancaire.hpp"
    #include "../inc/entreprise.hpp"

    #define HOMME   0
    #define FEMME   1

    #define STATUS_MARITAL_CELIB    0
    #define STATUS_MARITAL_MARIE    1
    #define STATUS_MARITAL_VEUF     2
    #define STATUS_MARITAL_DIVOR    3

    class Humain{
        public:
            Humain();
            Humain(int id, int sexe, char *nom);
            void initHumain(int id, int sexe, char *nom);
            void evolutionHumain(void);
            int getIdHumain();
            char *getNomHumain();
            void setNom(char *nom);
            int getSexe();
            void setSexe(int sexe);
            int getAge();
            int getStatusMarital();
            static bool isVariable(char *nomVariable);
            int getIntValue(char *nomVariable);
            char *getCharValue(char *nomVariable);
            bool testSiCommandeValide(char *valeur);
            bool testSiListeCommandeValide(char *valeur);
            int calculExpression(char *data1, char op, char *data2);
            bool execCommande(char *commande);
            CompteBancaire *compteBancaireHumain;
            void listeHumain(void);
            void acheteProduit(Entreprise *entreprise);

        private:
            int id;
            int sexe;   // 0 : homme, 1 = femme
            char nom[50];
            int age;
            int statusMarital;
            int nbEnfants;
            int idEmployeur;    // -1 => sans emploi
    };

#endif