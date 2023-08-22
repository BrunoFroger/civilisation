//-----------------------------------------
//
//          civilisation.hpp
//
//-----------------------------------------


#ifndef __CIVILISATION__
#define __CIVILISATION__

    #include "element.hpp"

    #define MAX_ELEMENTS    5

    class Civilisation{
        public:
            Civilisation();
            ~Civilisation();
            void creeElementHumain(int sexe, char *nom);
            void creeElementEntreprise(int activite, char *nom, int capitalInitial);
            void evolutionCivilisation(void);
            void listeCivilisation(void);
            void killCivilisation(void);
            int getCourantElementId(void);
            void listeElements(void);
            Element *getElement(int index);

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
