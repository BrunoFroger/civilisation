//-----------------------------------------
//
//          main.cpp
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>

#include "../inc/log.hpp"
#include "../inc/humain.hpp"
#include "../inc/tools.hpp"
#include "../inc/tests.hpp"


int main(int argc, char **argv){
    log(LOG_INFO, "===================================");
    log(LOG_INFO, "     C I V I L I S A T I O N ");
    log(LOG_INFO, "===================================");
    initPopulation();
    creeHumain(HOMME, "adam");
    creeHumain(FEMME, "eve");
    listePopulation();

    if (argc > 1){
        if (strcmp(argv[1], "tests") == 0){
            executeTests();
            return 0;
        }
    }

    while (1){
        evolutionPopulation();
        listePopulation();
        getchar();
    }
    killPopulation();
}