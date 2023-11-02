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

    typedef struct {
        char expression[500];
        char ListeCommandeSiVrai[1000];
        char ListeCommandeSiFaux[1000];
    } structSi;

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
            char *getNom(void);
            CompteBancaire *getCompteBancaire(void);
            bool testSiListeCommandeValide(char *valeur);
            bool decomposeScript(char *script, char *instruction, char *listeInstructions);
            bool decomposeSi(char *ligne, structSi *resultat);
            bool decomposeSet(char *ligne, char *listeInstructionRestante);
            bool isVariable(char *nomVariable);

        protected:

        private:
            int idElement;
            int typeElement;
            bool evalueListeInstructions(char *listeInstructions);
    };

#endif