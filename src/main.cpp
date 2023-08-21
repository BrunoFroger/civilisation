//-----------------------------------------
//
//          main.cpp
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include "../inc/log.hpp"
#include "../inc/humain.hpp"
#include "../inc/tests.hpp"
#include "../inc/element.hpp"
#include "../inc/civilisation.hpp"
#include "../inc/analyseParametres.hpp"

Civilisation civilisation;
int nbEvolutions = 0;

int main(int argc, char **argv){
    char ligneSaisie[100];
    if (!analyseParametres(argc, argv)){
        exit (1);
    }

    civilisation.listeElements();
    civilisation.creeElementHumain(HOMME, (char *)"adam");
    civilisation.listeElements();
    civilisation.creeElementHumain(FEMME, (char *)"eve");
    civilisation.listeElements();
    civilisation.creeElementEntreprise(ACTIVITE_COMMERCE, (char *)"Boulangerie");
    civilisation.listeElements();
    //creeHumain(HOMME, "adam");
    //creeHumain(FEMME, "eve");

    while (1){
        civilisation.evolutionCivilisation();
        civilisation.listeCivilisation();
        printf ("evolution (%d) > ", nbEvolutions++);
        fgets(ligneSaisie, 100, stdin);
        switch(ligneSaisie[0]){
            case 'q':
            case 'Q':
                return 0;
                break;
            default:
                break;
        }
    }
    civilisation.killCivilisation();
}