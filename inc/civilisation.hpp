//-----------------------------------------
//
//          civilisation.hpp
//
//-----------------------------------------


#ifndef __CIVILISATION__
#define __CIVILISATION__

    #include "element.hpp"

    #define MAX_ELEMENTS    500

    class Civilisation{
        public:
            Civilisation();
            ~Civilisation();
            Element *creeElementHumain(int sexe, char *nom, int capitalInitial);
            Element *creeElementEntreprise(int activite, char *nom, int capitalInitial);
            void evolutionCivilisation(void);
            void listeCivilisation(void);
            void killCivilisation(void);
            int getCourantElementId(void);
            void listeElement(int id);
            Element *getElement(int index);
            void tableauDeBord(void);
            void listeCommandesEtVariables(void);

        private:
            void incElementId(void);
            int getNbHumain(void);
            int getNbEntreprise(void);
            Element *elements[MAX_ELEMENTS];
            int courantElementId;
            int nbHumains;
            int nbEntreprises;
            
    };

#endif
