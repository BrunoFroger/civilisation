//-----------------------------------------
//
//          tools.hpp
//
//-----------------------------------------


#ifndef __TOOLS__
#define __TOOLS__


    #include "element.hpp"

    class Element;

    extern CompteBancaire *compteBancaireFournisseurNull;
    extern CompteBancaire *compteBancaireHeritageNull;
    extern bool modeListeAuto;
    extern bool modeTDBAuto;

    extern void initGenerateurAleatoire(void);
    extern void remove_extra_spaces(char* str);
    extern bool evaluationExpressionInt(int data1, char *test, int data2);
    extern bool evaluationExpressionChar(char *data1, char *test, char *data2);
    extern Element *naissance(Humain *pere, Humain *mere);
    extern bool mariage(Humain *homme, Humain *femme);
    extern int getSexeAleatoire(void);
    extern char *getPrenomAleatoire(int sexe);
    extern void setAuto(char *parametre);
    extern bool testSiInstructionComplexe(char *instruction);
    extern bool extraireSi(char *ListeInstructionOrigine, char *instruction, char *listeInstructionsRestante);

#endif