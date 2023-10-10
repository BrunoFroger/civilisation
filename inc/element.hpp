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

    #define MAX_HUMAIN          300
    #define MAX_ENTREPRISES     50
    #define MAX_ELEMENTS        MAX_HUMAIN + MAX_ENTREPRISES

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
            bool execScript(void);
            bool execScript(char *filename);
            bool executeExpression(char *expression);
            int getElementId(void);
            void setElementId(int id);
            int getTypeElement(void);
            void setTypeElement(int type);
            bool evalueExpression(char *expression);

        protected:

        private:
            int idElement;
            int typeElement;

    };

#endif