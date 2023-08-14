//-----------------------------------------
//
//          main.cpp
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>

#include "../inc/log.hpp"
#include "../inc/humain.hpp"
#include "../inc/tests.hpp"
#include "../inc/element.hpp"

Element elementRacine;

int main(int argc, char **argv){
    log(LOG_INFO, "===================================");
    log(LOG_INFO, "     C I V I L I S A T I O N ");
    log(LOG_INFO, "===================================");
    elementRacine.initPopulation();

    if (argc > 1){
        if (strcmp(argv[1], "tests") == 0){
            log(LOG_INFO, "     execution des tests ");
            log(LOG_INFO, "===================================");
            executeTests();
            return 0;
        }
    }
    elementRacine.creeHumain(HOMME, "adam");
    //creeHumain(HOMME, "adam");
    //creeHumain(FEMME, "eve");
    elementRacine.listePopulation();

    while (1){
        elementRacine.evolutionPopulation();
        elementRacine.listePopulation();
        getchar();
    }
    elementRacine.killPopulation();
}