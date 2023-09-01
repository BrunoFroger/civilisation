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

    civilisation.creeElementHumain(HOMME, (char *)"adam");
    civilisation.creeElementHumain(FEMME, (char *)"eve");
    civilisation.creeElementEntreprise(ACTIVITE_COMMERCE, (char *)"auBonPain", 10000);

    while (1){
        printf ("main => evolution (%d) > ", nbEvolutions);
        strcpy(ligneSaisie, "");
        fgets(ligneSaisie, 100, stdin);
        ligneSaisie[strlen(ligneSaisie) - 1] = '\0';
        switch(ligneSaisie[0]){
            case 'h': // aide
            case 'H': 
            case '?': 
                printf("commandes disponibles :\n");
                printf("    h, H, ? : affichage de cette aide\n");
                printf("    l, L [id] : affichage de la liste des éléments, ou un element specifique\n");
                printf("    q, Q : quitte le programme\n");
                printf("    t, T : affichage du tableau de bord\n");
                break;
            case 'l': // liste un element 
            case 'L': // 2eme caractere type element, puis id element
                if (strlen(ligneSaisie) > 2){
                    civilisation.listeElement(atoi(&ligneSaisie[1]));
                } else {
                    civilisation.listeCivilisation();
                }
                break;
            case 'q':
            case 'Q':
                return 0;
                break;
            case 't':
            case 'T':
                civilisation.tableauDeBord();
                break; 
            default:
                if (strlen(ligneSaisie) > 0){
                    printf("erreur : commade <%s> inconnue\n", ligneSaisie);
                } else {
                    civilisation.evolutionCivilisation();
                    nbEvolutions++;
                }
                break;
        }
    }
    civilisation.killCivilisation();
}