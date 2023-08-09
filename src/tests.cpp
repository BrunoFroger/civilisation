//-----------------------------------------
//
//          tests.cpp
//
//-----------------------------------------
#include <stdio.h>
#include <string.h>

#include "../inc/tools.hpp"
#include "../inc/log.hpp"
#include "../inc/humain.hpp"

int nbTests=0;
int nbOK=0;
int nbKO=0;

//-----------------------------------------
//
//          resutatTest
//
//-----------------------------------------
bool resultatTest(bool status){
    nbTests++;
    if (status){
        printf("    Test OK \n");
        nbOK++;
    } else {
        printf("    Test KO \n");
        nbKO++;
    }
    return status;
}

//-----------------------------------------
//
//          executeTests
//
//-----------------------------------------
void executeTests(void){
    printf("Executions des tests du programme civilisation\n");

    char ligne[200];
    structIf resultat;

    //=======================================
    //
    //         tests fonctions tools
    //
    //=======================================
    // tests de l'analyse de scripts
    if (0){ // tests de si
        printf("-----------------------------\n");
        strcpy(ligne, "si   age   >   50  mort");
        printf("decomposition de la ligne '%s'\n", ligne);
        if (resultatTest(decomposeSi(ligne, &resultat))){
            printf("dataOrigine    : '%s'\n", resultat.dataOrigine);
            printf("operateurTest  : '%s'\n", resultat.operateurTest);
            printf("dataReference  : '%s'\n", resultat.dataReference);
            printf("commandeSiVrai : '%s'\n", resultat.commandeSiVrai);
        } else {
            log(LOG_ERROR, "erreur dans la ligne '%s'\n", ligne);
        }
        
        printf("-----------------------------\n");
        strcpy(ligne, "si   age   ");
        printf("analyse de la ligne erronee '%s'\n", ligne);
        resultatTest(!decomposeSi(ligne, &resultat));
    }
    if (0){
        int val1, val2;
        char opeTest[10];
        printf("-----------------------------\n");
        printf("analyse de l'evaluation des tests de variables\n");

        val1=10; val2 =10;
        strcpy(opeTest, "=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(evaluation(val1,opeTest, val2));

        val1=10; val2 =20;
        strcpy(opeTest, "=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(!evaluation(val1,opeTest, val2));

        val1=10; val2 =20;
        strcpy(opeTest, "!=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(evaluation(val1,opeTest, val2));

        val1=10; val2 =20;
        strcpy(opeTest, ">");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(!evaluation(val1,opeTest, val2));

        val1=10; val2 =20;
        strcpy(opeTest, "<");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(evaluation(val1,opeTest, val2));

        val1=30; val2 =20;
        strcpy(opeTest, ">");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(evaluation(val1,opeTest, val2));

        val1=30; val2 =20;
        strcpy(opeTest, ">=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(evaluation(val1,opeTest, val2));

        val1=5; val2 =10;
        strcpy(opeTest, ">=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(!evaluation(val1, opeTest, val2));

        val1=30; val2 =20;
        strcpy(opeTest, "<=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(!evaluation(val1,opeTest, val2));

        val1=5; val2 =10;
        strcpy(opeTest, "<=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(evaluation(val1, opeTest, val2));

    }

    //=======================================
    //
    //         tests class Humain
    //
    //=======================================
    if (0){ // tests execScript Humain
        printf("-----------------------------\n");
        printf("tests script humain.scr\n");
        Humain humain;
        humain.init(10, 0, "marcel");
        resultatTest(humain.execScript());
    }
    if (0){     // tests isVariable
        printf("-----------------------------\n");
        printf("tests isVariable\n");
        Humain humain;
        humain.init(10, 0, "marcel");
        printf("test si 'age' est une variable connue\n");
        resultatTest(humain.isVariable((char *)"age"));
        printf("test si 'toto' n'est pas une variable connue\n");
        resultatTest(!humain.isVariable((char *)"toto"));
    }
    if (1){
        printf("-----------------------------\n");
        printf("tests si commandeSiVrai valide\n");
        Humain humain;
        humain.init(10, 0, "marcel");
        resultatTest(humain.testCommandeSiVraiValide((char *)"mort"));
        resultatTest(humain.testCommandeSiVraiValide((char *)"chercheConjoint"));
        resultatTest(!humain.testCommandeSiVraiValide((char *)"gfqhjksgdf"));
    }

    printf("-----------------------------\n");
    printf("Bilan des tests : \n");
    printf(" nb executés : %d\n", nbTests);
    printf(" nb OK       : %d\n", nbOK);
    printf(" nb KO       : %d\n", nbKO);
}