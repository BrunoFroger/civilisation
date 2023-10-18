//-----------------------------------------
//
//          compteBancaire.hpp
//
//-----------------------------------------

#ifndef __COMPTE_BANCAIRE__
#define __COMPTE_BANCAIRE__

    class Element;

    class CompteBancaire{
        public:
            CompteBancaire(Element *titulaire);
            CompteBancaire(Element *titulaire, int capitalInitial);
            void initCompteBancaire(Element *titulaire, int capitalInitial);
            int getId();
            int getSolde(void);
            int getEpargne(void);
            bool sauveEpargne(int valeur);
            bool restitueEpargne(int Valeur);
            bool virement(CompteBancaire *destinataire, int valeur);

        private:
            int id;
            int solde;
            long epargne;
            Element *titulaire;
            bool debite(int valeur);
            bool credite(int valeur);
    };

#endif