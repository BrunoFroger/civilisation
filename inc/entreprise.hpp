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

    class Entreprise{
        public:
            Entreprise();
            ~Entreprise();
            void initEntreprise(int id, int activite, char *nom, int capital);
            void evolutionEntreprise(void);
            int getIdEntreprise();
            char *getNomEntreprise();
            int getActivite();
            CompteBancaire *compteBancaireEntreprise;

        private:
            int id;
            int activite;
            char nom[50]; 
    };

#endif