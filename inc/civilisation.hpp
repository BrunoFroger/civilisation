//-----------------------------------------
//
//          civilisation.hpp
//
//-----------------------------------------


#ifndef __CIVILISATION__
#define __CIVILISATION__

    #include "element.hpp"


    class Civilisation{
        public:
            Civilisation();
            ~Civilisation();
            void chargeConfiguration(char *configFilename);
            Element *creeElementHumain(int sexe, char *nom, int capitalInitial);
            Element *creeElementEntreprise(int activite, char *nom, int capitalInitial, Entreprise *maisonMere);
            void evolutionCivilisation(void);
            void listeCivilisation(void);
            void killCivilisation(void);
            //int getCourantElementId(void);
            void listeElement(int id);
            Element *getElement(int index);
            void tableauDeBord(void);
            void listeCommandesEtVariables(void);
            static Humain *getConjoint(int sexe);
            static Humain *getSalarie(void);
            int getNbHommes(void);
            int getNbFemmes(void);
            int getNbHumain(void);
            int getNbEntreprise(void);
            static Entreprise *getEntrepriseByNom(char *nom);
            Entreprise *dupliqueEntreprise(Entreprise *maisonMere);

        private:
            //void incElementId(void);
            //int courantElementId;
            int nbHumains;
            int nbHommes, nbFemmes;
            int nbEntreprises;
            
    };

#endif
