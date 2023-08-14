//-----------------------------------------
//
//          tests.cpp
//
//-----------------------------------------
#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include "../inc/element.hpp"
#include "../inc/humain.hpp"
#include "../inc/log.hpp"

int nbTests=0;
int nbOK=0;
int nbKO=0;
bool exec_all=false;

//-----------------------------------------
//
//          resultatTest
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
    //printf("Executions des tests du programme civilisation\n");

    char ligne[500];
    structIf resultat;

    Element elementHumain;
    elementHumain.creeHumain(HOMME, "albert");
    long idHumain = elementHumain.getId();
    int ageHumain = elementHumain.getAge();
    printf("age albert : %d\n", elementHumain.getAge());
    printf("getIntValue(age) : %d\n", elementHumain.getIntValue((char *)"age"));

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

    if (0 || exec_all){ // test suppression des blancs
        printf("-----------------------------\n");
        printf("test de suppression des blancs inutiles d'une chaine");
        char expression[200] = "   1234   12345     12345678     123   123456789   ";
        char resultat_attendu[200] = "1234 12345 12345678 123 123456789";
        remove_extra_spaces(expression);
        printf("nouvelle expression : '%s'\n", expression);
        resultatTest((strcmp(expression, resultat_attendu) == 0));
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
        /*
        
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
        resultatTest(res);*/
    }

    if (0 || exec_all){ // tests execScript Humain
        printf("-----------------------------\n");
        printf("tests script humain.scr\n");
        Humain humain;
        humain.init(10, 0, "marcel");
        resultatTest(elementHumain.execScript());
    }
    if (0 || exec_all){     // tests isVariable
        printf("-----------------------------\n");
        printf("tests isVariable\n");
        Humain humain;
        humain.init(10, 0, "marcel");
        printf("test si 'age' est une variable connue\n");
        resultatTest(humain.isVariable((char *)"age"));
        printf("test si 'toto' n'est pas une variable connue\n");
        resultatTest(!humain.isVariable((char *)"toto"));
    }
    if (0 || exec_all){
        printf("-----------------------------\n");
        printf("tests si commande valide\n");
        Humain humain;
        humain.init(10, 0, "marcel");
        resultatTest(humain.testSiCommandeValide((char *)"mort"));
        resultatTest(humain.testSiCommandeValide((char *)"chercheConjoint"));
        resultatTest(!humain.testSiCommandeValide((char *)"gfqhjksgdf"));
    }

    printf("-----------------------------\n");
    printf("Bilan des tests : \n");
    printf(" nb executés : %d\n", nbTests);
    printf(" nb OK       : %d\n", nbOK);
    printf(" nb KO       : %d\n", nbKO);
}