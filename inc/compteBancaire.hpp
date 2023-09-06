//-----------------------------------------
//
//          compteBancaire.hpp
//
//-----------------------------------------

#ifndef __COMPTE_BANCAIRE__
#define __COMPTE_BANCAIRE__


    class CompteBancaire{
        public:
            CompteBancaire();
            CompteBancaire(int capitalInitial);
            void initCompteBancaire(int capitalInitial);
            int getSolde(void);
            int getEpargne(void);
            bool sauveEpargne(int valeur);
            bool restitueEpargne(int Valeur);
            bool virement(CompteBancaire *destinataire, int valeur);

        private:
            int solde;
            long epargne;
            bool debite(int valeur);
            bool credite(int valeur);
    };

#endif