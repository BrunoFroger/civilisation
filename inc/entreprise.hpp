//-----------------------------------------
//
//          entreprise.hpp
//
//-----------------------------------------

#ifndef __ENTREPRISE__
#define __ENTREPRISE__

    #define ACTIVITE_INCONNUE   0
    #define ACTIVITE_COMMERCE   1
    #define ACTIVITE_INDUSTRIE  2

    class Entreprise{
        public:
            void initEntreprise(int id, int activite, char *nom);
            void evolutionEntreprise(void);
            int getIdEntreprise();
            char *getNomEntreprise();
            int getActivite();

        private:
            int id;
            int activite;
            char nom[50]; 
    };

#endif