//-----------------------------------------
//
//          tools.hpp
//
//-----------------------------------------


#ifndef __TOOLS__
#define __TOOLS__


    #include "element.hpp"

    typedef struct {
        char expression[500];
        char ListeCommandeSiVrai[1000];
        char ListeCommandeSiFaux[1000];
    } structIf;

    extern void remove_extra_spaces(char* str);
    extern bool evaluationExpressionInt(int data1, char *test, int data2);
    extern bool evaluationExpressionChar(char *data1, char *test, char *data2);
    extern bool decomposeSi(char *ligne, structIf *resultat);
    extern bool decomposeScript(char *script, char *instruction, char *listeInstructions);

#endif