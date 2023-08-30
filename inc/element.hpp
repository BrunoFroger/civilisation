//-----------------------------------------
//
//          element.hpp
//
//-----------------------------------------

#include <stdio.h>

#ifndef __ELEMENT__
#define __ELEMENT__

    #include "humain.hpp"
    #include "entreprise.hpp"
    #include "tools.hpp"

    #define MAX_HUMAIN  3

    #define TYPE_INDEFINI   0
    #define TYPE_HUMAIN     1
    #define TYPE_ENTREPRISE 2

    typedef struct{
        char item1[500];
        char opTest[100];
        char item2[500];
    } structExpression;


    extern void remove_extra_spaces(char *chaine);

    class Element : public Humain, public Entreprise{
        public:
            Element();
            ~Element();
            Element(int id, int type);
            //void initPopulation(int id);
            void creeHumain(int id, int sexe, char *nom);
            bool execScript(void);
            bool execScript(char *filename);
            long getCourantId();
            //void listePopulation(void);
            //void killPopulation(void);
            //void evolutionPopulation(void);
            bool decomposeExpression(char *chaine, structExpression *resultat);
            int getElementId(void);
            void setElementId(int id);
            int typeElement;

        protected:

        private:
            int idElement;

    };

#endif