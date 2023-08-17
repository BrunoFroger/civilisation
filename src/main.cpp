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
#include "../inc/civilisation.hpp"

Civilisation civilisation;

int main(int argc, char **argv){

    setLogLevel(LOG_DEBUG);
    if (argc > 1){
        if (strcmp(argv[1], "tests") == 0){
            log(LOG_INFO, "     execution des tests ");
            log(LOG_INFO, "===================================");
            executeTests();
            return 0;
        }
    }
    civilisation.creeElementHumain(HOMME, (char *)"adam");
    //creeHumain(HOMME, "adam");
    //creeHumain(FEMME, "eve");
    civilisation.listeCivilisation();

    while (1){
        civilisation.evolutionCivilisation();
        civilisation.listeCivilisation();
        getchar();
    }
    civilisation.killCivilisation();
}