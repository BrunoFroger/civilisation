//-----------------------------------------
//
//          tools.hpp
//
//-----------------------------------------


#ifndef __TOOLS__
#define __TOOLS__


    #include "element.hpp"

    class Element;

    typedef struct {
        char expression[500];
        char ListeCommandeSiVrai[1000];
        char ListeCommandeSiFaux[1000];
    } structSi;

    extern CompteBancaire *compteBancaireFournisseurNull;
    extern bool modeListeAuto;
    extern bool modeTDBAuto;

    extern void initGenerateurAleatoire(void);
    extern void remove_extra_spaces(char* str);
    extern bool evaluationExpressionInt(int data1, char *test, int data2);
    extern bool evaluationExpressionChar(char *data1, char *test, char *data2);
    extern bool decomposeSi(char *ligne, structSi *resultat);
    extern bool decomposeScript(char *script, char *instruction, char *listeInstructions);
    extern Element *naissance(Humain *pere, Humain *mere);
    extern bool mariage(Humain *homme, Humain *femme);
    extern int getSexeAleatoire(void);
    extern char *getPrenomAleatoire(int sexe);
    extern void setAuto(char *parametre);

#endif