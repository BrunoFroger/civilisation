//-----------------------------------------
//
//          tests.cpp
//
//-----------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>

#include "../inc/civilisation.hpp"
#include "../inc/element.hpp"
#include "../inc/humain.hpp"
#include "../inc/log.hpp"
#include "../inc/tests.hpp"
#include "../inc/tools.hpp"

#define NB_RUBRIQUES    6

typedef struct {
    char nomRubrique[30];
    int nbtests;
    int nbOK;
    int nbKO;
    int tauxReussite;
} structResultatTest;

int nbTests=0;
int nbOK=0;
int nbKO=0;
int nbTestsRubrique=0;
int nbOKRubrique=0;
int nbKORubrique=0;
bool exec_all=false;
bool exec_civilisation=false;
bool exec_element=false;
bool exec_humain=false;
bool exec_entreprise=false;
bool exec_tools=false;
bool exec_banque=false;
structResultatTest tableauresultatsTests[NB_RUBRIQUES];

//-----------------------------------------
//
//          resultatTest
//
//-----------------------------------------
void initTableauTests(void){
    int index = 0;
    strcpy(tableauresultatsTests[index].nomRubrique, "civilisation");
    tableauresultatsTests[index].nbtests = 0;
    tableauresultatsTests[index].nbOK = 0;
    tableauresultatsTests[index].nbKO = 0;
    tableauresultatsTests[index].tauxReussite = 0;
    index++;
    strcpy(tableauresultatsTests[index].nomRubrique, "element");
    tableauresultatsTests[index].nbtests = 0;
    tableauresultatsTests[index].nbOK = 0;
    tableauresultatsTests[index].nbKO = 0;
    tableauresultatsTests[index].tauxReussite = 0;
    index++;
    strcpy(tableauresultatsTests[index].nomRubrique, "humain");
    tableauresultatsTests[index].nbtests = 0;
    tableauresultatsTests[index].nbOK = 0;
    tableauresultatsTests[index].nbKO = 0;
    tableauresultatsTests[index].tauxReussite = 0;
    index++;
    strcpy(tableauresultatsTests[index].nomRubrique, "entreprise");
    tableauresultatsTests[index].nbtests = 0;
    tableauresultatsTests[index].nbOK = 0;
    tableauresultatsTests[index].nbKO = 0;
    tableauresultatsTests[index].tauxReussite = 0;
    index++;
    strcpy(tableauresultatsTests[index].nomRubrique, "tools");
    tableauresultatsTests[index].nbtests = 0;
    tableauresultatsTests[index].nbOK = 0;
    tableauresultatsTests[index].nbKO = 0;
    tableauresultatsTests[index].tauxReussite = 0;
    index++;
    strcpy(tableauresultatsTests[index].nomRubrique, "banque");
    tableauresultatsTests[index].nbtests = 0;
    tableauresultatsTests[index].nbOK = 0;
    tableauresultatsTests[index].nbKO = 0;
    tableauresultatsTests[index].tauxReussite = 0;
}

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
        nbOKRubrique++;
    } else {
        printf("    Test KO \n");
        nbKO++;
        nbKORubrique++;
    }
    return status;
}

//-----------------------------------------
//
//          bilanTestrubrique
//
//-----------------------------------------
void bilanTestsRubrique(char *rubrique){
    if (nbTestsRubrique > 0){
        printf("    %d tests executés dans la rubrique %s\n", nbTestsRubrique, rubrique);
        for (int i = 0; i < NB_RUBRIQUES ; i++){
            //printf("construction ligne %d de la rubrique %s (%s)=> ", i, rubrique, tableauresultatsTests[i].nomRubrique);
            if (strcmp(tableauresultatsTests[i].nomRubrique, rubrique) == 0){
                tableauresultatsTests[i].nbtests = nbTestsRubrique;
                tableauresultatsTests[i].nbOK = nbOKRubrique;
                tableauresultatsTests[i].nbKO = nbKORubrique;
                //printf("OK\n");
                break;
            } else {
                //printf("KO\n");
            }
        }
        nbTestsRubrique = 0;
        nbOKRubrique = 0;
        nbKORubrique = 0;
    }
    printf("\n");
}

//-----------------------------------------
//
//          bilanTest
//
//-----------------------------------------
void bilanTests(void){
    char tauxReussite[10];
    printf("+----------------------------------------------------------+\n");
    printf("|                       Bilan des tests                    |\n");
    printf("+--------------------------------+-----+-----+-----+-------+\n");
    printf("|                  rubrique      |  NB |  OK |  KO |  %% OK |\n");
    printf("+--------------------------------+-----+-----+-----+-------+\n");
    for (int i = 0 ; i < NB_RUBRIQUES ; i++){
        if (tableauresultatsTests[i].nbtests == 0){
            strcpy(tauxReussite, "");
            continue;
        } else {
            sprintf(tauxReussite, "%3d%%", tableauresultatsTests[i].nbOK * 100 / tableauresultatsTests[i].nbtests);
        }
        printf("| %30s | %3d | %3d | %3d | %5s |\n", 
            tableauresultatsTests[i].nomRubrique,
            tableauresultatsTests[i].nbtests,
            tableauresultatsTests[i].nbOK,
            tableauresultatsTests[i].nbKO, 
            tauxReussite);
    }
    if (nbTests == 0){
        strcpy(tauxReussite, "");
    } else {
        sprintf(tauxReussite, "%3d%%", nbOK * 100 / nbTests);
    }
    printf("+--------------------------------+-----+-----+-----+-------+\n");
    printf("|                  Total         | %3d | %3d | %3d | %5s |\n", nbTests, nbOK, nbKO, tauxReussite);
    printf("+--------------------------------+-----+-----+-----+-------+\n");
}

//-----------------------------------------
//
//          executeTests
//
//-----------------------------------------
void executeTests(int mode){
    //printf("Executions des tests du programme civilisation mode = %d\n", mode);
    initTableauTests();
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

   char rubrique[30];

    //=======================================
    //
    //         tests fonction de tools
    //
    //=======================================
    if (0 || exec_all || exec_tools){
        strcpy(rubrique, "tools");
        log(LOG_DEBUG, "=====================================================");
        log(LOG_DEBUG, "execution des tests rubrique %s", rubrique);
        log(LOG_DEBUG, "-----------------------------------------------------");
        
        log(LOG_DEBUG, "-----------------------------------------------------");

        if (0 || exec_all ) { // bloc suppression des blancs inutiles d'une chaine
            log(LOG_DEBUG, "-----------------------------------------------------");
            log(LOG_DEBUG, "test de suppression des blancs inutiles d'une chaine");
            char expression[200];
            sprintf(expression, " 1234   12345     12345678     123   123456789   ");
            char resultat_attendu[200] = "1234 12345 12345678 123 123456789";
            remove_extra_spaces(expression);
            resultatTest((strcmp(expression, resultat_attendu) == 0));
        }


        if (0 || exec_all ) { // bloc evaluationExpressionInt
            log(LOG_DEBUG, "-----------------------------------------------------");
            log(LOG_DEBUG, "test fonction evaluation expression Int");
            int val1, val2;
            char opeTest[100];
            val1=10; val2 =10;
            strcpy(opeTest, "=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(evaluationExpressionInt(val1,opeTest, val2));

            val1=10; val2 =20;
            strcpy(opeTest, "=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(!evaluationExpressionInt(val1,opeTest, val2));

            val1=10; val2 =20;
            strcpy(opeTest, "!=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(evaluationExpressionInt(val1,opeTest, val2));

            val1=10; val2 =20;
            strcpy(opeTest, ">");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(!evaluationExpressionInt(val1,opeTest, val2));

            val1=10; val2 =20;
            strcpy(opeTest, "<");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(evaluationExpressionInt(val1,opeTest, val2));

            val1=30; val2 =20;
            strcpy(opeTest, ">");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(evaluationExpressionInt(val1,opeTest, val2));

            val1=30; val2 =20;
            strcpy(opeTest, ">=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(evaluationExpressionInt(val1,opeTest, val2));

            val1=5; val2 =10;
            strcpy(opeTest, ">=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(!evaluationExpressionInt(val1, opeTest, val2));

            val1=30; val2 =20;
            strcpy(opeTest, "<=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(!evaluationExpressionInt(val1,opeTest, val2));

            val1=5; val2 =10;
            strcpy(opeTest, "<=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(evaluationExpressionInt(val1, opeTest, val2));
        } else {
            log(LOG_DEBUG, "Bloc evaluationExpressionInt non executé\n");
        }

        if (0 || exec_all ){ // bloc decomposeSi
            log(LOG_DEBUG, "-----------------------------------------------------");
            log(LOG_DEBUG, "test decompose si ");
            char ligne[5000] = "";
            structIf resultat;
            bool res = false;
            
            sprintf(ligne, "si toto alors titi finsi commande");
            res = decomposeSi(ligne, &resultat);
            res |= (strcmp(resultat.ListeCommandeSiVrai, "toto") == 0);
            res |= (strcmp(resultat.ListeCommandeSiVrai, "titi") == 0);
            resultatTest(res);
            
            sprintf(ligne, "si toto alors titi \n tata finsi commande1\ncommande2");
            res = decomposeSi(ligne, &resultat);
            res |= (strcmp(resultat.ListeCommandeSiVrai, "titi \n tata ") == 0);
            res |= (strcmp(resultat.ListeCommandeSiVrai, "commande1\ncommande2") == 0);
            resultatTest(res);
        }


        if (0 || exec_all ){ // bloc decomposeListeInstructions
            log(LOG_DEBUG, "-----------------------------------------------------");
            log(LOG_DEBUG, "test decomposeListeInstructions");
            char script[5000] = "";
            char instruction[100] = "";
            char listeInstructions[5000] = "";
            bool res = true;
            sprintf(script, "#commentaire\nchercheConjoint");
            res = decomposeListeInstructions(script, instruction, listeInstructions);
            res &= (strcmp(instruction, "#commentaire") == 0);
            res &= (strcmp(listeInstructions, "chercheConjoint") == 0);
            resultatTest(res);
            sprintf(script, "#commentaire\nchercheConjoint\ntoto");
            res = decomposeListeInstructions(script, instruction, listeInstructions);
            res &= (strcmp(instruction, "#commentaire") == 0);
            res &= (strcmp(listeInstructions, "chercheConjoint\ntoto") == 0);
            resultatTest(res);

            sprintf(script, "#commentaire\n chercheConjoint");
            res = decomposeListeInstructions(script, instruction, listeInstructions);
            res &= (strcmp(instruction, "#commentaire") == 0);
            res &= (strcmp(listeInstructions, " chercheConjoint") == 0);
            resultatTest(res);

            sprintf(script, "si toto alors titi finsi commande");
            res = decomposeListeInstructions(script, instruction, listeInstructions);
            res &= (strcmp(instruction, "si toto alors titi finsi") == 0);
            res &= (strcmp(listeInstructions, "commande") == 0);
            resultatTest(res);

            sprintf(script, "si toto alors titi finsi commande\n ");
            res = decomposeListeInstructions(script, instruction, listeInstructions);
            res &= (strcmp(instruction, "si toto alors titi finsi") == 0);
            res &= (strcmp(listeInstructions, "commande\n ") == 0);
            resultatTest(res);

            sprintf(script, "si toto alors titi finsi \n commande");
            res = decomposeListeInstructions(script, instruction, listeInstructions);
            res &= (strcmp(instruction, "si toto alors titi finsi") == 0);
            res &= (strcmp(listeInstructions, "\n commande") == 0);
            resultatTest(res);

            sprintf(script, "si toto \n tata alors titi \n tutu finsi commande1\n commande2\n ");
            res = decomposeListeInstructions(script, instruction, listeInstructions);
            res &= (strcmp(instruction, "si toto \n tata alors titi \n tutu finsi") == 0);
            res &= (strcmp(listeInstructions, "commande1\n commande2\n ") == 0);
            resultatTest(res);

            sprintf(script, "si toto alors titi commande\n ");
            res = decomposeListeInstructions(script, instruction, listeInstructions);
            resultatTest(!res);
        } else {
            log(LOG_DEBUG, "Bloc decomposeListeInstructions non executé\n");
        }

        bilanTestsRubrique(rubrique);
    }

    //=======================================
    //
    //         tests classe Civilisation
    //
    //=======================================
    if (0 || exec_all || exec_civilisation){
        strcpy(rubrique, "civilisation");
        log(LOG_DEBUG, "=====================================================");
        log(LOG_DEBUG, "execution des tests rubrique %s", rubrique);
        log(LOG_DEBUG, "-----------------------------------------------------");
        log(LOG_DEBUG, "test de creation de la classe");
        Civilisation civilisation;
        resultatTest((civilisation.getCourantElementId() == 0));
        log(LOG_DEBUG, "test de creation d'un element humain");
        civilisation.creeElementHumain(HOMME, (char *)"Marcel");
        resultatTest(strcmp(civilisation.getElement(civilisation.getCourantElementId()-1)->getNomHumain(), "Marcel") == 0);
        log(LOG_DEBUG, "test de creation d'un element entreprise");
        civilisation.creeElementEntreprise(ACTIVITE_COMMERCE, (char *)"auBonPain", 25000);
        resultatTest(strcmp(civilisation.getElement(civilisation.getCourantElementId()-1)->getNomEntreprise(), "au bon pain") == 0);
        resultatTest(civilisation.getElement(civilisation.getCourantElementId()-1)->compteBancaireEntreprise->getSolde() == 25000);

        bilanTestsRubrique(rubrique);
    }

    //=======================================
    //
    //         tests classe Element
    //
    //=======================================
    if (0 || exec_all || exec_element){
        strcpy(rubrique, "element");
        log(LOG_DEBUG, "=====================================================");
        log(LOG_DEBUG, "execution des tests rubrique %s", rubrique);
        log(LOG_DEBUG, "-----------------------------------------------------");
        Element element;
        element.initHumain(10, FEMME, (char *)"eve");
        bool res = true;
        printf("res %d init \n", res);
        res = (element.getIdHumain() == 10);
        printf("res %d get id = %d\n", res, element.getIdHumain());
        res = (element.getAge() == 0);
        printf("res %d get age = %d\n", res, element.getAge());
        resultatTest(res);
        bilanTestsRubrique(rubrique);
    }

    //=======================================
    //
    //         tests classe Humain
    //
    //=======================================
    if (0 || exec_all || exec_humain){
        strcpy(rubrique, "humain");
        log(LOG_DEBUG, "=====================================================");
        log(LOG_DEBUG, "execution des tests rubrique %s", rubrique);
        log(LOG_DEBUG, "-----------------------------------------------------");
        Civilisation civilisation;

        log(LOG_DEBUG, "test creation humain");
        Humain humain(0,HOMME, (char *)"adam");
        resultatTest(humain.getAge() == 0);
        resultatTest(strcmp(humain.getNomHumain(), "adam") == 0);

        log(LOG_DEBUG, "test evolution age");
        humain.evolutionHumain();
        resultatTest(humain.getAge() == 1);

        log(LOG_DEBUG, "test fonction liste de commandes valide");
        resultatTest(humain.testSiCommandeValide((char *)"mort"));
        resultatTest(humain.testSiCommandeValide((char *)"ecole"));
        resultatTest(!humain.testSiCommandeValide((char *)"sdfqsdfqdf"));
        resultatTest(humain.calculExpression((char *)"20", '+', (char *)"10") == 30);
        resultatTest(!(humain.calculExpression((char *)"20", '+', (char *)"20") == 30));
        resultatTest(humain.calculExpression((char *)"20", '*', (char *)"10") == 200);
        resultatTest(humain.calculExpression((char *)"20", '/', (char *)"10") == 2);
        resultatTest(humain.calculExpression((char *)"20", '-', (char *)"10") == 10);
        resultatTest(humain.calculExpression((char *)"age", '+', (char *)"10") == 11);

        bilanTestsRubrique(rubrique);
    }

    //=======================================
    //
    //         tests classe Entreprise
    //
    //=======================================
    if (0 || exec_all || exec_entreprise){
        strcpy(rubrique, "entreprise");
        log(LOG_DEBUG, "=====================================================");
        log(LOG_DEBUG, "execution des tests rubrique %s", rubrique);
        log(LOG_DEBUG, "-----------------------------------------------------");
        Civilisation civilisation;
        Element *elementEntreprise, *elementHumain;
        bool res;
        int idEntreprise, idSalarie;

        // test creation entreprise avec fichier de configuration spécifique
        res = true;
        idEntreprise = civilisation.getCourantElementId();
        idEntreprise = civilisation.creeElementEntreprise(ACTIVITE_COMMERCE, (char *)"auBonPain", 10000);
        printf("creation entreprise id : %d\n", idEntreprise);
        elementEntreprise = civilisation.getElement(idEntreprise);
        res &= (strcmp(elementEntreprise->getNomEntreprise(), (char *)"au bon pain") == 0);
        //printf("res = %d\n", res);
        res &= (elementEntreprise->getNbSalaries() == 2);
        //printf("res = %d\n", res);
        res &= (elementEntreprise->getCoutSalaries() == 100);
        //printf("res = %d\n", res);
        res &= (elementEntreprise->getCoutProduit() == 5);
        //printf("res = %d\n", res);
        res &= (elementEntreprise->getPrixProduit() == 10);
        //printf("res = %d\n", res);
        res &= (elementEntreprise->getStockProduit() == 20);
        //printf("res = %d\n", res);
        res &= (elementEntreprise->getMaxEmployes() == 5);
        //printf("res = %d\n", res);
        resultatTest(res);

        // test creation entreprise avec fichier de configuration par default
        res = true;
        idEntreprise = civilisation.getCourantElementId();
        civilisation.creeElementEntreprise(ACTIVITE_COMMERCE, (char *)"machin", 10000);
        printf("creation entreprise id : %d\n", idEntreprise);
        elementEntreprise = civilisation.getElement(idEntreprise);
        res &= (strcmp(elementEntreprise->getNomEntreprise(), (char *)"entreprise par default") == 0);
        res &= (elementEntreprise->getNbSalaries() == 0);
        res &= (elementEntreprise->getCoutSalaries() == 100);
        res &= (elementEntreprise->getCoutProduit() == 5);
        res &= (elementEntreprise->getPrixProduit() == 10);
        res &= (elementEntreprise->getStockProduit() == 0);
        resultatTest(res);

        // test versement de salaire
        idSalarie = civilisation.creeElementHumain(HOMME, (char *)"Adam");
        elementHumain = civilisation.getElement(idSalarie);
        int ancienSoldeHumain, ancienSoldeEntreprise, soldeAttendu;
        int salaire = 100;
        ancienSoldeHumain = elementHumain->compteBancaireHumain->getSolde();
        ancienSoldeEntreprise = elementEntreprise->compteBancaireEntreprise->getSolde();
        soldeAttendu = ancienSoldeHumain + salaire;
        elementEntreprise->verseSalaire(salaire, elementHumain);
        //printf("ancien solde = %d ; salaire = %d ; nouveau solde = %d\n", ancienSolde, salaire, nouveauSolde);
        resultatTest(soldeAttendu == elementHumain->compteBancaireHumain->getSolde());
        soldeAttendu = ancienSoldeEntreprise - salaire;
        //printf("ancien solde = %d ; salaire = %d ; nouveau solde = %d\n", ancienSoldeEntreprise, salaire, soldeAttendu);
        resultatTest(soldeAttendu == elementEntreprise->compteBancaireEntreprise->getSolde());


        // test commande/livraison de produit
        elementEntreprise->creeCommande(elementHumain, 1);
        resultatTest(elementEntreprise->getNbCommandes() == 1);
        elementEntreprise->creeCommande(elementHumain, 1);
        resultatTest(elementEntreprise->getNbCommandes() == 2);
        elementEntreprise->livraison(elementHumain);
        resultatTest(elementEntreprise->getNbCommandes() == 1);

        bilanTestsRubrique(rubrique);
    }

    //=======================================
    //
    //         tests classe CompteBancaire
    //
    //=======================================
    if (0 || exec_all || exec_banque){
        strcpy(rubrique, "banque");
        log(LOG_DEBUG, "=====================================================");
        log(LOG_DEBUG, "execution des tests rubrique %s", rubrique);
        log(LOG_DEBUG, "-----------------------------------------------------");

        CompteBancaire cpt;
        resultatTest(cpt.getSolde() == 0);
        cpt.credite(100);
        resultatTest(cpt.getSolde() == 100);
        cpt.sauveEpargne(50);
        resultatTest((cpt.getSolde() == 50) && (cpt.getEpargne() == 50));
        cpt.restitueEpargne(25);
        resultatTest((cpt.getSolde() == 75) && (cpt.getEpargne() == 25));
        cpt.debite(50);
        resultatTest(cpt.getSolde() == 25);

        CompteBancaire cpt1(1000);
        resultatTest(cpt1.getSolde() == 1000);

        // test creation de compte initialisé
        CompteBancaire cpt2(100);
        cpt1.virement(&cpt2, 500);
        resultatTest((cpt1.getSolde() == 500) && (cpt2.getSolde() == 600));

        // test virement négatif impossible
        resultatTest( ! cpt1.virement(&cpt2, -100));

        bilanTestsRubrique(rubrique);
    }

    bilanTests();

}