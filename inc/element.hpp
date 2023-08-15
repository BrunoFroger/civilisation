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

    #define MAX_HUMAIN  3

    typedef struct {
        char expression[500];
        char ListeCommandeSiVrai[1000];
        char ListeCommandeSiFaux[1000];
    } structIf;

    typedef struct{
        char item1[500];
        char opTest[100];
        char item2[500];
    } structExpression;


    extern void remove_extra_spaces(char *chaine);

    class Element : public Humain, public Entreprise{
        public:
            void creeHumain(int sexe, const char *nom);
            void initPopulation(void);   
            bool execScript(void);
            bool execScript(char *filename); 
            long getCourantId();
            void listePopulation(void);
            void killPopulation(void);
            void evolutionPopulation(void);
            bool decomposeSi(FILE *fic, char *ligne, structIf *resultat);
            bool decomposeExpression(char *chaine, structExpression *resultat);
            bool evaluationExpressionInt(int data1, char *test, int data2);
            bool evaluationExpressionChar(char *data1, char *test, char *data2);
            int calculExpression(char *data1, char op, char *data2);

        protected:
            long newId(void);

        private:

    };

#endif