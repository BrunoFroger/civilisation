//-----------------------------------------
//
//          main.cpp
//
//-----------------------------------------

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include "../inc/log.hpp"
#include "../inc/humain.hpp"
#include "../inc/tests.hpp"
#include "../inc/element.hpp"
#include "../inc/civilisation.hpp"
#include "../inc/analyseParametres.hpp"
#include "../inc/aide.hpp"
#include "../inc/analyseLigneCommande.hpp"

Civilisation civilisation;
int nbEvolutions = 0;
int nbRepetitions = 0;
char configFilename[100] = "scripts/civilisation.scr";

int main(int argc, char **argv){
    char ligneSaisie[100];
    if (!analyseParametres(argc, argv)){
        exit (1);
    }
    initGenerateurAleatoire();
    initHistoriqueCommande();
    
    civilisation.chargeConfiguration(configFilename);

    while (1){
        printf ("main => evolution (%d) > ", nbEvolutions);
        strcpy(ligneSaisie, "");
        fgets(ligneSaisie, 100, stdin);
        ligneSaisie[strlen(ligneSaisie) - 1] = '\0';
        switch(ligneSaisie[0]){
            case 'q':
            case 'Q':
                return 0;
                break;
            case 't':
            case 'T':
                civilisation.tableauDeBord();
                break; 
            case '!':
                afficheHistorique();
                break; 
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                nbRepetitions = atoi(ligneSaisie);
                while (nbRepetitions-- > 0){
                    civilisation.evolutionCivilisation();
                    nbEvolutions++;
                }
                break; 
            default:
                if (strlen(ligneSaisie) > 0){
                    analyseLigneCommande(ligneSaisie);
                } else {
                    civilisation.evolutionCivilisation();
                    nbEvolutions++;
                }
                break;
        }
        if (strlen(ligneSaisie) > 0){
            historiseCommande(ligneSaisie);
        }
    }
    civilisation.killCivilisation();
}