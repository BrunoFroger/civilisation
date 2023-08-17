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
            void creeElementHumain(int sexe, char *nom);
            void creeElementEntreprise(int activite, char *nom);
            void evolutionCivilisation(void);
            void listeCivilisation(void);
            void killCivilisation(void);
            int getTypeElement(Element element);

        private:
            void incElementId(void);
            int getNbHumain(void);
            Element elements[MAX_ELEMENTS];
            int courantElementId;
            int nbHumains;
            int nbEntreprises;
            
    };

#endif
