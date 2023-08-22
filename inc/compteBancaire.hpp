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
            bool credite(int valeur);
            bool debite(int valeur);
            int getSolde(void);
            int getEpargne(void);

        private:
            int solde;
            long epargne;
            bool sauveEpargne(int valeur);
            bool restitueEpargne(int Valeur);
    };

#endif