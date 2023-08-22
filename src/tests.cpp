//-----------------------------------------
//
//          tests.cpp
//
//-----------------------------------------
#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include "../inc/civilisation.hpp"
#include "../inc/element.hpp"
#include "../inc/humain.hpp"
#include "../inc/log.hpp"
#include "../inc/tests.hpp"

int nbTests=0;
int nbTestsRubrique=0;
int nbOK=0;
int nbKO=0;
bool exec_all=false;
bool exec_civilisation=false;
bool exec_element=false;
bool exec_humain=false;
bool exec_entreprise=false;
bool exec_tools=false;
bool exec_banque=false;

//-----------------------------------------
//
//          resultatTest
//
//-----------------------------------------
bool resultatTest(bool status){
    nbTests++;
    nbTestsRubrique++;
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
//          bilanTestrubrique
//
//-----------------------------------------
void bilanTestsRubrique(void){
    if (nbTestsRubrique > 0){
        printf("    %d tests executés dans cette rubrique\n", nbTestsRubrique);
        nbTestsRubrique = 0;
    }
    printf("\n");
}

//-----------------------------------------
//
//          bilanTest
//
//-----------------------------------------
void bilanTests(void){
    printf("-----------------------------\n");
    printf("Bilan des tests : \n");
    printf(" nb executés : %d\n", nbTests);
    printf(" nb OK       : %d\n", nbOK);
    printf(" nb KO       : %d\n", nbKO);
}

//-----------------------------------------
//
//          executeTests
//
//-----------------------------------------
void executeTests(int mode){
    printf("Executions des tests du programme civilisation mode = %d\n", mode);
    setLogLevel(LOG_DEBUG);
    switch (mode){
        case TEST_MODE_ALL:
            exec_all = true;
            break;
        case TEST_MODE_CIVI:
            exec_civilisation = true;
            break;
        case TEST_MODE_ELEM:
            exec_element = true;
            break;
        case TEST_MODE_HUMA:
            exec_humain = true;
            break;
        case TEST_MODE_ENTR:
            exec_entreprise = true;
            break;
        case TEST_MODE_TOOL:
            exec_tools = true;
            break;
        case TEST_MODE_BANK:
            exec_banque = true;
            break;
        default :
            break;
    }

    //char ligne[500];
    //structIf resultat;

    /*
    Element elementHumain;
    elementHumain.creeHumain(HOMME, "albert");
    long idHumain = elementHumain.getId();
    int ageHumain = elementHumain.getAge();
    printf("age albert : %d\n", elementHumain.getAge());
    printf("getIntValue(age) : %d\n", elementHumain.getIntValue((char *)"age"));
    */

    //=======================================
    //
    //         tests fonction de tools
    //
    //=======================================
    if (0 || exec_all || exec_tools){
        log(LOG_DEBUG, "=====================================================");
        log(LOG_DEBUG, "execution des tests de la fonction de tools");
        log(LOG_DEBUG, "-----------------------------------------------------");
        
        log(LOG_DEBUG, "-----------------------------------------------------");
        log(LOG_DEBUG, "test de suppression des blancs inutiles d'une chaine");
        char expression[200] = "   1234   12345     12345678     123   123456789   ";
        char resultat_attendu[200] = "1234 12345 12345678 123 123456789";
        remove_extra_spaces(expression);
        resultatTest((strcmp(expression, resultat_attendu) == 0));

        bilanTestsRubrique();
    }

    //=======================================
    //
    //         tests classe Civilisation
    //
    //=======================================
    if (0 || exec_all || exec_civilisation){
        log(LOG_DEBUG, "=====================================================");
        log(LOG_DEBUG, "execution des tests de la classe civilisation");
        log(LOG_DEBUG, "-----------------------------------------------------");
        log(LOG_DEBUG, "test de creation de la classe");
        Civilisation civilisation;
        bool result;
        resultatTest((civilisation.getCourantElementId() == 0));
        log(LOG_DEBUG, "test de creation d'un element humain");
        civilisation.creeElementHumain(HOMME,"Marcel");
        resultatTest(strcmp(civilisation.getElement(civilisation.getCourantElementId()-1)->getNomHumain(), "Marcel") == 0);
        log(LOG_DEBUG, "test de creation d'un element entreprise");
        civilisation.creeElementEntreprise(ACTIVITE_COMMERCE, "boulangerie", 25000);
        resultatTest(strcmp(civilisation.getElement(civilisation.getCourantElementId()-1)->getNomEntreprise(), "boulangerie") == 0);
        resultatTest(civilisation.getElement(civilisation.getCourantElementId()-1)->compteBancaireEntreprise->getSolde() == 25000);

        bilanTestsRubrique();
    }

    //=======================================
    //
    //         tests classe Element
    //
    //=======================================
    if (0 || exec_all || exec_element){
        log(LOG_DEBUG, "=====================================================");
        log(LOG_DEBUG, "execution des tests de la classe element");
        log(LOG_DEBUG, "-----------------------------------------------------");

        bilanTestsRubrique();
    }

    //=======================================
    //
    //         tests classe Humain
    //
    //=======================================
    if (0 || exec_all || exec_humain){
        log(LOG_DEBUG, "=====================================================");
        log(LOG_DEBUG, "execution des tests de la classe humain");
        log(LOG_DEBUG, "-----------------------------------------------------");
        log(LOG_DEBUG, "test fonction liste de commandes valide");
        Humain humain(0,1, (char *)"adam");
        resultatTest(humain.testSiCommandeValide((char *)"mort"));
        resultatTest(humain.testSiCommandeValide((char *)"ecole"));
        resultatTest(!humain.testSiCommandeValide((char *)"sdfqsdfqdf"));

        bilanTestsRubrique();
    }

    //=======================================
    //
    //         tests classe Entreprise
    //
    //=======================================
    if (0 || exec_all || exec_entreprise){
        log(LOG_DEBUG, "=====================================================");
        log(LOG_DEBUG, "execution des tests de la classe entreprise");
        log(LOG_DEBUG, "-----------------------------------------------------");

        bilanTestsRubrique();
    }

    //=======================================
    //
    //         tests classe CompteBancaire
    //
    //=======================================
    if (0 || exec_all || exec_banque){
        log(LOG_DEBUG, "=====================================================");
        log(LOG_DEBUG, "execution des tests de la classe CompteBancaire");
        log(LOG_DEBUG, "-----------------------------------------------------");

        bilanTestsRubrique();
    }

    bilanTests();

/*
    //=======================================
    //
    //         tests fonctions tools
    //
    //=======================================
    // tests de l'analyse de scripts
    if (0 || exec_all){
        printf("-----------------------------\n");
        printf("analyse de scripts\n");
        printf("-----------------------------\n");
        printf("execution du tests du script testIfOK1.scr\n");
        resultatTest(elementHumain.execScript((char *)"scripts/testIfOK1.scr"));
        printf("-----------------------------\n");
        printf("execution du tests du script testIfOK2.scr\n");
        resultatTest(elementHumain.execScript((char *)"scripts/testIfOK2.scr"));
        printf("-----------------------------\n");
        printf("execution du tests du script testIfOK3.scr\n");
        resultatTest(elementHumain.execScript((char *)"scripts/testIfOK3.scr"));
        printf("-----------------------------\n");
    }
    if (0 || exec_all){ // tests de si
        printf("-----------------------------\n");
        printf("test si\n");
        FILE *fic;
        char *tmp;
        fic = fopen("scripts/testIfKO.scr", "r");
        while (!feof(fic)){
            fgets(ligne, 200, fic);
            //printf("ligne lue '%s'\n", ligne);
            tmp = &ligne[0];
            if ( tmp[strlen(tmp) - 1] == '\n'){ // suppr RC en fin de ligne
                //printf("ligne avec retour chariot on le supprime\n");
                tmp[strlen(tmp) - 1] = '\0';
            }
             while (*tmp == ' ') tmp++;  // suppression des blancs en debut de ligne
            if (strlen(tmp) == 0) continue;
            if (ligne[0] == '#') continue;

            printf("decomposition de la ligne '%s'\n", tmp);
            if (resultatTest(!elementHumain.decomposeSi(fic, tmp, &resultat))){
                printf("expression1         : '%s'\n", resultat.expression);
                printf("listeCommandeSiVrai : '%s'\n", resultat.ListeCommandeSiVrai);
                printf("listeCommandeSiFaux : '%s'\n", resultat.ListeCommandeSiFaux);
            }
        }
        
        printf("-----------------------------\n");
        strcpy(ligne, "si   age   ");
        printf("analyse d'une ligne erronee '%s'\n", ligne);
        resultatTest(!elementHumain.decomposeSi(fic, ligne, &resultat));
    }

    if (0 || exec_all){
        printf("-----------------------------\n");
        printf("tests de evaluation d'expressions\n");
        int val1, val2;
        char opeTest[100];

        val1=10; val2 =10;
        strcpy(opeTest, "=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(elementHumain.evaluationExpressionInt(val1,opeTest, val2));

        val1=10; val2 =20;
        strcpy(opeTest, "=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(!elementHumain.evaluationExpressionInt(val1,opeTest, val2));

        val1=10; val2 =20;
        strcpy(opeTest, "!=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(elementHumain.evaluationExpressionInt(val1,opeTest, val2));

        val1=10; val2 =20;
        strcpy(opeTest, ">");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(!elementHumain.evaluationExpressionInt(val1,opeTest, val2));

        val1=10; val2 =20;
        strcpy(opeTest, "<");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(elementHumain.evaluationExpressionInt(val1,opeTest, val2));

        val1=30; val2 =20;
        strcpy(opeTest, ">");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(elementHumain.evaluationExpressionInt(val1,opeTest, val2));

        val1=30; val2 =20;
        strcpy(opeTest, ">=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(elementHumain.evaluationExpressionInt(val1,opeTest, val2));

        val1=5; val2 =10;
        strcpy(opeTest, ">=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(!elementHumain.evaluationExpressionInt(val1, opeTest, val2));

        val1=30; val2 =20;
        strcpy(opeTest, "<=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(!elementHumain.evaluationExpressionInt(val1,opeTest, val2));

        val1=5; val2 =10;
        strcpy(opeTest, "<=");
        printf("evaluation de %d %s %d \n", val1, opeTest, val2);
        resultatTest(elementHumain.evaluationExpressionInt(val1, opeTest, val2));

    }

    if (1 || exec_all){ // tests decompose expression
        printf("-----------------------------\n");
        printf("tests de decomposition d'expressions\n");
        char expression[500];
        bool res;
        structExpression resultat;
        strcpy(resultat.item1,"");
        strcpy(resultat.opTest,"");
        strcpy(resultat.item2,"");
        
        strcpy(expression, "  (age + 20)  =  (40 - 20)  ");
        elementHumain.decomposeExpression(expression, &resultat);
        res = (strcmp(resultat.item1, "20") == 0);
        res &= (strcmp(resultat.opTest, "=") == 0);
        res &= (strcmp(resultat.item2, "20") == 0);
        resultatTest(res);
        
        
        strcpy(expression, "  age  =  0  ");
        elementHumain.decomposeExpression(expression, &resultat);
        res = (strcmp(resultat.item1, "0") == 0);
        res &= (strcmp(resultat.opTest, "=") == 0);
        res &= (strcmp(resultat.item2, "0") == 0);
        res &= elementHumain.evaluationExpressionInt(atoi(resultat.item1), resultat.opTest, atoi(resultat.item2));
        resultatTest(res);
        
        strcpy(expression, "  (age - 20)  =  (age - 10)  ");
        elementHumain.decomposeExpression(expression, &resultat);
        res = (strcmp(resultat.item1, "age - 20") == 0);
        res &= (strcmp(resultat.opTest, "=") == 0);
        res &= (strcmp(resultat.item2, "age - 10") == 0);
        resultatTest(res);
    }

    if (0 || exec_all){ // tests execScript Humain
        printf("-----------------------------\n");
        printf("tests script humain.scr\n");
        Humain humain;
        humain.initHumain(10, 0, "marcel");
        resultatTest(elementHumain.execScript());
    }
    if (0 || exec_all){     // tests isVariable
        printf("-----------------------------\n");
        printf("tests isVariable\n");
        Humain humain;
        humain.initHumain(10, 0, "marcel");
        printf("test si 'age' est une variable connue\n");
        resultatTest(humain.isVariable((char *)"age"));
        printf("test si 'toto' n'est pas une variable connue\n");
        resultatTest(!humain.isVariable((char *)"toto"));
    }
    */
}