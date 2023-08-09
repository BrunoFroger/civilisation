//-----------------------------------------
//
//          tools.hpp
//
//-----------------------------------------

#ifndef __TOOLS__
#define __TOOLS__

    typedef struct {
        char dataOrigine[20];
        char operateurTest[3];
        char dataReference[20];
        char commandeSiVrai[100];
    } structIf;

    extern long newId();
    extern long getId();
    extern void creeHumain(int sexe, const char *nom);
    extern void listePopulation(void);
    extern void initPopulation(void);
    extern void killPopulation(void);
    extern void evolutionPopulation(void);
    extern bool decomposeSi(char *ligne, structIf *resultat);
    extern bool evaluation(int data1, char *test, int data2);

#endif