//-----------------------------------------
//
//          tests.cpp
//
//-----------------------------------------
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>

#include "../inc/civilisation.hpp"
#include "../inc/element.hpp"
#include "../inc/humain.hpp"
#include "../inc/log.hpp"
#include "../inc/tests.hpp"
#include "../inc/tools.hpp"

#define NB_RUBRIQUES    6

//Paramètre  Couleur
//0 reinit |30 Noir |31 Rouge | 32 Vert | 33 Jaune | 34 Bleu| 35 Magenta | 36 Cyan | 37 Blanc
#define color(param) printf("\033[%dm",param)

typedef struct {
    char nomRubrique[30];
    int nbtests;
    int nbOK;
    int nbKO;
    int tauxReussite;
    long duree;
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
bool stopOnFail = false;
bool StatusBilanTests = true;
struct timeval debutTests, finTests;
struct timeval debutRubrique, finRubrique;
void *tmpTime=NULL;

structResultatTest tableauresultatsTests[NB_RUBRIQUES];



//-----------------------------------------
//
//          diffTime
//
//-----------------------------------------
long myDifftime(struct timeval *debut, struct timeval *fin){
    //printf("myDiffTime => nbSec debut = %ld\n", debut->tv_sec);
    //printf("myDiffTime => nbSec fin   = %ld\n", fin->tv_sec);
    unsigned long nbSec = difftime(fin->tv_sec, debut->tv_sec);
    //printf("myDiffTime => nbSec = %ld\n", nbSec);
    unsigned long nbMs = (unsigned long)fin->tv_usec - (unsigned long)debut->tv_usec;
    //printf("myDiffTime => nb microSec = %ld\n", nbMs);
    long retValue = (long)nbSec * 1000000;
    retValue += (long)nbMs;
    //printf("myDiffTime => retValue = %ld\n", retValue);
    return retValue;
}

//-----------------------------------------
//
//          baniereDebutTests
//
//-----------------------------------------
void baniereDebutTests(void){
    log(LOG_INFO, "===================================");
    log(LOG_INFO, "                                   ");
    log(LOG_INFO, "       execution des tests         ");
    log(LOG_INFO, "                                   ");
    log(LOG_INFO, "===================================");
    gettimeofday(&debutTests, tmpTime);
}

//-----------------------------------------
//
//          baniereTest
//
//-----------------------------------------
void baniereTest(char *rubrique, char *descriptionTest){
    log(LOG_DEBUG, "-----------------------------------------------------");
    log(LOG_DEBUG, "");
    log(LOG_DEBUG, "    %s : %s", rubrique, descriptionTest);
    log(LOG_DEBUG, "");
    log(LOG_DEBUG, "-----------------------------------------------------");
}

//-----------------------------------------
//
//          baniereDebutRubrique
//
//-----------------------------------------
void baniereDebutRubrique(char *rubrique){
    log(LOG_DEBUG, "=====================================================");
    log(LOG_DEBUG, "");
    log(LOG_DEBUG, "        execution des tests rubrique %s", rubrique);
    log(LOG_DEBUG, "");
    log(LOG_DEBUG, "=====================================================");
    gettimeofday(&debutRubrique, tmpTime);
}

//-----------------------------------------
//
//          baniereFinTests
//
//-----------------------------------------
void baniereFinTests(void){
    log(LOG_INFO, "===================================");
    log(LOG_INFO, "                                   ");
    log(LOG_INFO, "           fin des tests           ");
    log(LOG_INFO, "                                   ");
    if (StatusBilanTests){
        log(LOG_INFO, "                O K                ");
    } else {
        log(LOG_INFO, "                K O                ");
    }
    log(LOG_INFO, "                                   ");
    log(LOG_INFO, "===================================");
}

//-----------------------------------------
//
//          initTableauTests
//
//-----------------------------------------
void initTableauTests(void){
    int index = 0;
    strcpy(tableauresultatsTests[index].nomRubrique, "tools");
    tableauresultatsTests[index].nbtests = 0;
    tableauresultatsTests[index].nbOK = 0;
    tableauresultatsTests[index].nbKO = 0;
    tableauresultatsTests[index].tauxReussite = 0;
    index++;
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
    strcpy(tableauresultatsTests[index].nomRubrique, "banque");
    tableauresultatsTests[index].nbtests = 0;
    tableauresultatsTests[index].nbOK = 0;
    tableauresultatsTests[index].nbKO = 0;
    tableauresultatsTests[index].tauxReussite = 0;
}

//-----------------------------------------
//
//          bilanTest
//
//-----------------------------------------
void bilanTests(void){
    //printf("execute bilanTests\n");
    char tauxReussite[10];
    gettimeofday(&finTests, tmpTime);
    long dureeTests = myDifftime(&debutTests, &finTests);
    //log(LOG_INFO, "durée des tests : %ld",dureeTests);
    printf("+-------------------------------------------------------------------+\n");
    printf("|                 Bilan des tests (duree en microsecondes)          |\n");
    printf("+--------------------------------+-----+-----+-----+-------+--------+\n");
    printf("|                  rubrique      |  NB |  OK |  KO |  %% OK |  duree |\n");
    printf("+--------------------------------+-----+-----+-----+-------+--------+\n");
    for (int i = 0 ; i < NB_RUBRIQUES ; i++){
        if (tableauresultatsTests[i].nbtests == 0){
            strcpy(tauxReussite, "");
            continue;
        } else {
            snprintf(tauxReussite, sizeof(tauxReussite), "%3d%%", tableauresultatsTests[i].nbOK * 100 / tableauresultatsTests[i].nbtests);
        }
        printf("| %30s | %3d | %3d | %3d | %5s |  %5ld |\n", 
            tableauresultatsTests[i].nomRubrique,
            tableauresultatsTests[i].nbtests,
            tableauresultatsTests[i].nbOK,
            tableauresultatsTests[i].nbKO, 
            tauxReussite,
            tableauresultatsTests[i].duree);
    }
    if (nbTests == 0){
        strcpy(tauxReussite, "");
    } else {
        snprintf(tauxReussite, sizeof(tauxReussite), "%3d%%", nbOK * 100 / nbTests);
    }
    printf("+--------------------------------+-----+-----+-----+-------+--------+\n");
    printf("|                  Total         | %3d | %3d | %3d | %5s |  %5ld |\n", nbTests, nbOK, nbKO, tauxReussite, dureeTests);
    printf("+--------------------------------+-----+-----+-----+-------+--------+\n");
}

//-----------------------------------------
//
//          bilanTestrubrique
//
//-----------------------------------------
void bilanTestsRubrique(char *rubrique){
    //printf("execute bilanTestsRubrique\n");
    gettimeofday(&finRubrique, tmpTime);
    long dureeRubrique = myDifftime(&debutRubrique, &finRubrique);
    if (nbTestsRubrique > 0){
        printf("    %d tests executés dans la rubrique %s\n", nbTestsRubrique, rubrique);
        printf("    Durée de la rubrique = %ld\n", dureeRubrique);
        for (int i = 0; i < NB_RUBRIQUES ; i++){
            //printf("construction ligne %d de la rubrique %s (%s)=> ", i, rubrique, tableauresultatsTests[i].nomRubrique);
            if (strcmp(tableauresultatsTests[i].nomRubrique, rubrique) == 0){
                tableauresultatsTests[i].nbtests = nbTestsRubrique;
                tableauresultatsTests[i].nbOK = nbOKRubrique;
                tableauresultatsTests[i].nbKO = nbKORubrique;
                tableauresultatsTests[i].duree = dureeRubrique;
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
//          resultatTest
//
//-----------------------------------------
bool resultatTest(char *rubrique, bool status){
    nbTests++;
    nbTestsRubrique++;
    if (status){
        printf("    Test n° %d OK \n", nbTestsRubrique);
        nbOK++;
        nbOKRubrique++;
    } else {
        color(31);
        printf("    Test n° %d KO dans %s\n", nbTestsRubrique, rubrique);
        color(0);
        nbKO++;
        nbKORubrique++;
        StatusBilanTests = false;
        if (stopOnFail){
            bilanTestsRubrique(rubrique);
            bilanTests();
            baniereFinTests();
            exit(-1);
        } 
    }
    return status;
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
    baniereDebutTests();
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
        baniereDebutRubrique(rubrique);
        
        if (1 || exec_all ) { // test de suppression des blancs inutiles d'une chaine
            baniereTest(rubrique, (char *)"test de suppression des blancs inutiles d'une chaine");
            char expression[200];
            snprintf(expression, sizeof(expression), "   1234   12345     12345678     123   123456789   ");
            char resultat_attendu[200] = "1234 12345 12345678 123 123456789";
            remove_extra_spaces(expression);
            resultatTest(rubrique, (strcmp(expression, resultat_attendu) == 0));
        }

        if (1 || exec_all){ // tests génération aleatoire du sexe
            baniereTest(rubrique, (char *)"tests génération aleatoire du sexe");
            int nbHommes=0, nbFemmes = 0;
            for (int i = 0 ; i < 100 ; i++){
                if (getSexeAleatoire() == HOMME) nbHommes++; else nbFemmes++;
            }
            printf("nbHommes = %d, nbFemmes = %d\n", nbHommes, nbFemmes);
            resultatTest(rubrique, (nbHommes >= 40));
            resultatTest(rubrique, (nbFemmes >= 40));
        }

        if (1 || exec_all){ // tests génération aleatoire du prenom
            baniereTest(rubrique, (char *)"tests génération aleatoire du prenom");
            char tabPrenoms[200][20];
            // tests sur prenoms masculin
            //log(LOG_DEBUG, "tests prenoms masculin");
            int nbPrenomGeneres = 100;
            int maxDoublons = 7;
            int nbDoublons = 0;
            for (int i = 0 ; i < nbPrenomGeneres ; i++){
                //log(LOG_DEBUG,"--------------------------------");
                strcpy(tabPrenoms[i], getPrenomAleatoire(HOMME));
                //log(LOG_DEBUG, "prenoms masculin genere : %s", tabPrenoms[i]);
                for (int j = 0 ; j < i ; j++){
                    //log(LOG_DEBUG, "comparaison de (%d)%s avec (%d)%s", i, tabPrenoms[i], j, tabPrenoms[j]);
                    if (strcmp(tabPrenoms[i], tabPrenoms[j]) == 0){
                        log(LOG_DEBUG, "tirage %d : le prenoms masculin %s a dejà ete généré au tirage %d", i, tabPrenoms[i], j);
                        nbDoublons++;
                        break;
                    }
                }
            }
            log(LOG_DEBUG, "%d doublons de prenoms masculins", nbDoublons);
            resultatTest(rubrique, (nbDoublons < maxDoublons));
            nbDoublons = 0;
            // tests sur prenoms femin
            for (int i = 0 ; i < 200 ; i++) strcpy(tabPrenoms[i], "");
            //log(LOG_DEBUG, "tests prenoms femin");
            for (int i = 0 ; i < nbPrenomGeneres ; i++){
                //log(LOG_DEBUG,"--------------------------------");
                strcpy(tabPrenoms[i], getPrenomAleatoire(FEMME));
                //log(LOG_DEBUG, "prenoms feminin genere : %s", tabPrenoms[i]);
                for (int j = 0 ; j < i ; j++){
                    //log(LOG_DEBUG, "comparaison de (%d)%s avec (%d)%s", i, tabPrenoms[i], j, tabPrenoms[j]);
                    if (strcmp(tabPrenoms[i], tabPrenoms[j]) == 0){
                        log(LOG_DEBUG, "tirage %d : le prenoms feminin %s a dejà ete généré au tirage %d", i, tabPrenoms[i], j);
                        nbDoublons++;
                        break;
                    }
                }
            }
            log(LOG_DEBUG, "%d doublons de prenoms feminin", nbDoublons);
            resultatTest(rubrique, (nbDoublons < maxDoublons));
            nbDoublons = 0;
        }

        if (1 || exec_all ) { // test fonction evaluation expression Int
            baniereTest(rubrique, (char *)"test fonction evaluation expression Int");
            int val1, val2;
            char opeTest[100];
            val1=10; val2 =10;
            strcpy(opeTest, "=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(rubrique, evaluationExpressionInt(val1,opeTest, val2));

            val1=10; val2 =20;
            strcpy(opeTest, "=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(rubrique, !evaluationExpressionInt(val1,opeTest, val2));

            val1=10; val2 =20;
            strcpy(opeTest, "!=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(rubrique, evaluationExpressionInt(val1,opeTest, val2));

            val1=20; val2 =20;
            strcpy(opeTest, "!=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(rubrique, !evaluationExpressionInt(val1,opeTest, val2));

            val1=10; val2 =20;
            strcpy(opeTest, ">");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(rubrique, !evaluationExpressionInt(val1,opeTest, val2));

            val1=30; val2 =20;
            strcpy(opeTest, ">");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(rubrique, evaluationExpressionInt(val1,opeTest, val2));

            val1=10; val2 =20;
            strcpy(opeTest, "<");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(rubrique, evaluationExpressionInt(val1,opeTest, val2));

            val1=30; val2 =20;
            strcpy(opeTest, "<");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(rubrique, !evaluationExpressionInt(val1,opeTest, val2));

            val1=30; val2 =20;
            strcpy(opeTest, ">=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(rubrique, evaluationExpressionInt(val1,opeTest, val2));

            val1=5; val2 =10;
            strcpy(opeTest, ">=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(rubrique, !evaluationExpressionInt(val1, opeTest, val2));

            val1=30; val2 =20;
            strcpy(opeTest, "<=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(rubrique, !evaluationExpressionInt(val1,opeTest, val2));

            val1=5; val2 =10;
            strcpy(opeTest, "<=");
            printf("evaluation de %d %s %d \n", val1, opeTest, val2);
            resultatTest(rubrique, evaluationExpressionInt(val1, opeTest, val2));
        } 

        if (1 || exec_all ){ // test extraire Si 
            baniereTest(rubrique, (char *)"test extraire si simple");
            char ligne[5000] = "";
            char expression[200];
            char expressionsRestantes[200];
            snprintf(ligne, sizeof(ligne),  "si age = 0 alors mortPossible sinon chercheConjoint finsi naissancePossible");
            resultatTest(rubrique, extraireSi(ligne, expression, expressionsRestantes));
            resultatTest(rubrique, (strcmp(expression, "si age = 0 alors mortPossible sinon chercheConjoint finsi") == 0));
            resultatTest(rubrique, (strcmp(expressionsRestantes, "naissancePossible") == 0));

            baniereTest(rubrique, (char *)"test extraire si imbrique");
            snprintf(ligne, sizeof(ligne),  "si age = 0 alors mortPossible sinon si age > 20 alors chercheConjoint finsi naissancePossible finsi achat-aubonpain");
            resultatTest(rubrique, extraireSi(ligne, expression, expressionsRestantes));
            resultatTest(rubrique, (strcmp(expression, "si age = 0 alors mortPossible sinon si age > 20 alors chercheConjoint finsi naissancePossible finsi") == 0));
            resultatTest(rubrique, (strcmp(expressionsRestantes, "achat-aubonpain") == 0));
        }

        if (1 || exec_all ){ // test decompose si 
            baniereTest(rubrique, (char *)"test decompose si");
            Civilisation newCivilisation;
            char ligne[5000] = "";
            structSi resultat;
            Element *testScript = newCivilisation.creeElementHumain(HOMME, (char *)"joseph", 2000);
            snprintf(ligne, sizeof(ligne),  "si age = 0 alors mortPossible finsi");
            resultatTest(rubrique, testScript->decomposeSi(ligne, &resultat));
            resultatTest(rubrique, (strcmp(resultat.expression, "age = 0") == 0));
            resultatTest(rubrique, (strcmp(resultat.ListeCommandeSiVrai, "mortPossible") == 0));
            resultatTest(rubrique, (strcmp(resultat.ListeCommandeSiFaux, "") == 0));
            
            snprintf(ligne, sizeof(ligne), "si age = 0 alors mortPossible sinon naissancePossible finsi");
            resultatTest(rubrique, testScript->decomposeSi(ligne, &resultat));
            resultatTest(rubrique, (strcmp(resultat.expression, "age = 0") == 0));
            resultatTest(rubrique, (strcmp(resultat.ListeCommandeSiVrai, "mortPossible") == 0));
            resultatTest(rubrique, (strcmp(resultat.ListeCommandeSiFaux, "naissancePossible") == 0));
        }

        if (1 || exec_all ){ // test decomposeScript
            baniereTest(rubrique, (char *)"test decomposeScript");
            Civilisation newCivilisation;
            Element *testScript = newCivilisation.creeElementHumain(HOMME, (char *)"joseph", 2000);
            char script[5000];
            char instruction[1000];
            char listeInstructions[5000];
            strcpy(script, (char*)"");
            strcpy(instruction, (char*)"");
            strcpy(listeInstructions, (char*)"");

            log(LOG_DEBUG, "------------------------------------------");
            snprintf(script, sizeof(script), "");
            resultatTest(rubrique, testScript->decomposeScript(script, instruction, listeInstructions));
            resultatTest(rubrique, (strcmp(instruction, "") == 0));
            resultatTest(rubrique, (strcmp(listeInstructions, "") == 0));

            log(LOG_DEBUG, "------------------------------------------");
            snprintf(script, sizeof(script), "toto");
            resultatTest(rubrique, testScript->decomposeScript(script, instruction, listeInstructions));
            resultatTest(rubrique, (strcmp(instruction, "toto") == 0));
            resultatTest(rubrique, (strcmp(listeInstructions, "") == 0));

            log(LOG_DEBUG, "------------------------------------------");
            snprintf(script, sizeof(script), "si age = 0 alors mortPossible sinon naissancePossible finsi");
            resultatTest(rubrique, testScript->decomposeScript(script, instruction, listeInstructions));
            resultatTest(rubrique, (strcmp(instruction, "si age = 0 alors mortPossible sinon naissancePossible finsi") == 0));
            resultatTest(rubrique, (strcmp(listeInstructions, "") == 0));

            log(LOG_DEBUG, "------------------------------------------");
            snprintf(script, sizeof(script), "si age = 0 alors mortPossible finsi naissancePossible");
            resultatTest(rubrique,testScript->decomposeScript(script, instruction, listeInstructions));
            printf("fin de la fonction decompose script\n");
            resultatTest(rubrique,(strcmp(instruction, "si age = 0 alors mortPossible finsi") == 0));
            resultatTest(rubrique,(strcmp(listeInstructions, "naissancePossible") == 0));

            log(LOG_DEBUG, "------------------------------------------");
            snprintf(script, sizeof(script), "si age = 0 alors mortPossible naissancePossible ");
            resultatTest(rubrique, !(testScript->decomposeScript(script, instruction, listeInstructions)));

            log(LOG_DEBUG, "------------------------------------------");
            snprintf(script, sizeof(script), "si age = 0 alors mortPossible finsi si age > 20 alors naissancePossible finsi ");
            resultatTest(rubrique, testScript->decomposeScript(script, instruction, listeInstructions));
        }


        if (1 || exec_all ){ // test variables de script
            baniereTest(rubrique, (char *)"test gestion variables de script");
            resultatTest(rubrique, setVariable((char *)"set maVariable 50"));
            resultatTest(rubrique, !setVariable((char *)"set maVariable 50"));
            resultatTest(rubrique, !setVariable((char *)"set maVariable"));
            resultatTest(rubrique, strcmp(getVariable((char *)"maVariable"), "50") == 0);
            resultatTest(rubrique, getVariable((char *)"toto") == NULL);
            resultatTest(rubrique, unsetVariable((char *)"unset maVariable"));
            resultatTest(rubrique, getVariable((char *)"maVariable") == NULL);
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
        baniereDebutRubrique(rubrique);
        Civilisation newCivilisation;

        baniereTest(rubrique, (char *)"test de creation de civilisation avec id element = 0");
        resultatTest(rubrique, (newCivilisation.getNbHumain() == 0));
        resultatTest(rubrique, (newCivilisation.getNbHommes() == 0));
        resultatTest(rubrique, (newCivilisation.getNbFemmes() == 0));

        baniereTest(rubrique, (char *)"test de creation d'un homme");
        Element *pere = newCivilisation.creeElementHumain(HOMME, (char *)"Marcel", 1000);
        resultatTest(rubrique, strcmp(pere->getNomHumain(), "Marcel") == 0);
        resultatTest(rubrique, pere->getTypeElement() == TYPE_HUMAIN);
        resultatTest(rubrique, pere->getSexe() == HOMME);
        resultatTest(rubrique, (newCivilisation.getNbHumain() == 1));
        resultatTest(rubrique, (newCivilisation.getNbHommes() == 1));
        resultatTest(rubrique, (newCivilisation.getNbFemmes() == 0));

        baniereTest(rubrique, (char *)"test de creation d'une femme");
        Element *mere = newCivilisation.creeElementHumain(FEMME, (char *)"Simone", 1000);
        resultatTest(rubrique, strcmp(mere->getNomHumain(), "Simone") == 0);
        resultatTest(rubrique, mere->getTypeElement() == TYPE_HUMAIN);
        resultatTest(rubrique, mere->getSexe() == FEMME);
        resultatTest(rubrique, (newCivilisation.getNbHumain() == 2));
        resultatTest(rubrique, (newCivilisation.getNbHommes() == 1));
        resultatTest(rubrique, (newCivilisation.getNbFemmes() == 1));

        baniereTest(rubrique, (char *)"test de creation d'un element entreprise");
        resultatTest(rubrique, newCivilisation.getNbEntreprise() == 0);
        Element *entreprise = newCivilisation.creeElementEntreprise(ACTIVITE_COMMERCE, (char *)"auBonPain", 25000, NULL);
        resultatTest(rubrique, entreprise->getTypeElement() == TYPE_ENTREPRISE);
        resultatTest(rubrique, strcmp(entreprise->getNomEntreprise(), "auBonPain") == 0);
        resultatTest(rubrique, strcmp(entreprise->getNomCommercialEntreprise(), "au bon pain") == 0);
        resultatTest(rubrique, entreprise->compteBancaireEntreprise->getSolde() == 25000);
        resultatTest(rubrique, newCivilisation.getNbEntreprise() == 1);

        baniereTest(rubrique, (char *)"test de mariage");
        resultatTest(rubrique, mariage(pere, mere));

        baniereTest(rubrique, (char *)"test de creation d'enfants");
        for (int i = 0 ; i < MAX_ENFANTS + 2 ; i++){
            bool result;
            if (i >= MAX_ENFANTS) {
                result = true;
            } else {
                Element *enfant = naissance(&newCivilisation, pere, mere);
                int id = enfant->getElementId();
                log(LOG_DEBUG, "test creation enfant %d", id);
                result = (enfant->getElementId() != -1);
            }
            resultatTest(rubrique, result);
        }

        bilanTestsRubrique(rubrique);
    }

    //=======================================
    //
    //         tests classe Element
    //
    //=======================================
    if (0 || exec_all || exec_element){
        strcpy(rubrique, "element");
        baniereDebutRubrique(rubrique);
        Civilisation newCivilisation;
        Element *element = newCivilisation.creeElementHumain(FEMME, (char *)"eve", 1000);
        newCivilisation.creeElementEntreprise(ACTIVITE_COMMERCE, (char *)"auBonPain", 25000, NULL);

        baniereTest(rubrique, (char *)"test creation element");
        resultatTest(rubrique, element->getIdHumain() == 0);
        resultatTest(rubrique, element->getElementId() == 0);
        resultatTest(rubrique, element->getAge() == 0);
        resultatTest(rubrique, (strcmp(element->getNom(), "eve") == 0));

        baniereTest(rubrique, (char *)"test execution script");
        resultatTest(rubrique, element->execScript());

        bilanTestsRubrique(rubrique);
    }

    //=======================================
    //
    //         tests classe Humain
    //
    //=======================================
    if (0 || exec_all || exec_humain){
        strcpy(rubrique, "humain");
        baniereDebutRubrique(rubrique);
        Civilisation *newCivilisation = new Civilisation();

        baniereTest(rubrique, (char *)"test creation humain");
        Humain humain(0,HOMME, (char *)"adam", 1000);
        resultatTest(rubrique, humain.getAge() == 0);
        resultatTest(rubrique, strcmp(humain.getNomHumain(), "adam") == 0);

        baniereTest(rubrique, (char *)"test evolution");
        humain.evolutionHumain();
        resultatTest(rubrique, humain.getAge() == 1);

        baniereTest(rubrique, (char *)"test fonction liste de commandes valide");
        resultatTest(rubrique, humain.testSiCommandeValideHumain((char *)"mortPossible"));
        resultatTest(rubrique, !humain.testSiCommandeValideHumain((char *)"sdfqsdfqdf"));
        resultatTest(rubrique, humain.testSiCommandeValideHumain((char *)"achat-aubonpain"));
        resultatTest(rubrique, humain.calculExpressionHumain((char *)"20", '+', (char *)"10") == 30);
        resultatTest(rubrique, !(humain.calculExpressionHumain((char *)"20", '+', (char *)"20") == 30));
        resultatTest(rubrique, humain.calculExpressionHumain((char *)"20", '*', (char *)"10") == 200);
        resultatTest(rubrique, humain.calculExpressionHumain((char *)"20", '/', (char *)"10") == 2);
        resultatTest(rubrique, humain.calculExpressionHumain((char *)"20", '-', (char *)"10") == 10);
        resultatTest(rubrique, humain.calculExpressionHumain((char *)"age", '+', (char *)"10") == 11);

        baniereTest(rubrique, (char *)"test execution commandes");
        resultatTest(rubrique, humain.execCommandeHumain((char *)"mortPossible"));
        resultatTest(rubrique, !humain.execCommandeHumain((char *)"toto"));
        resultatTest(rubrique, !(humain.getStatusMarital() == STATUS_MARITAL_DECES));
        for (int i = 0 ; i < 20 ; i++) humain.evolutionHumain();
        humain.execCommandeHumain((char *)"mortPossible");
        //resultatTest(rubrique, humain.getStatusMarital() == STATUS_MARITAL_DECES);

        baniereTest(rubrique, (char *)"test mariage et naissance");
        int ancienNbHomme = newCivilisation->getNbHommes();
        int ancienNbFemme = newCivilisation->getNbFemmes();
        int ancienNbHumain = newCivilisation->getNbHumain();
        Element *pere = newCivilisation->creeElementHumain(HOMME, (char *)"papa", 1000);
        resultatTest(rubrique, (newCivilisation->getNbHommes() == ancienNbHomme + 1));
        resultatTest(rubrique, (newCivilisation->getNbFemmes() == ancienNbFemme));
        resultatTest(rubrique, (newCivilisation->getNbHumain() == ancienNbHumain + 1));
        Element *mere = newCivilisation->creeElementHumain(FEMME, (char *)"maman", 1000);
        resultatTest(rubrique, (newCivilisation->getNbHommes() == ancienNbHomme + 1));
        resultatTest(rubrique, (newCivilisation->getNbFemmes() == ancienNbFemme + 1));
        resultatTest(rubrique, (newCivilisation->getNbHumain() == ancienNbHumain + 2));
        resultatTest(rubrique, (pere->getStatusMarital() == STATUS_MARITAL_CELIB));
        resultatTest(rubrique, (mere->getStatusMarital() == STATUS_MARITAL_CELIB));
        resultatTest(rubrique, (pere->compteBancaireHumain->getSolde() == 1000));
        resultatTest(rubrique, (mere->compteBancaireHumain->getSolde() == 1000));
        for (int i = 0 ; i < 25 ; i++){
            pere->evolutionHumain();
            mere->evolutionHumain();
        }
        log(LOG_DEBUG, "-----------------------------------------------------");
        log(LOG_DEBUG, "test mariage de %s et %s", pere->getNomHumain(), mere->getNomHumain());
        mariage(pere, mere);
        resultatTest(rubrique, (pere->getStatusMarital() == STATUS_MARITAL_MARIE));
        resultatTest(rubrique, (mere->getStatusMarital() == STATUS_MARITAL_MARIE));
        //civilisation.listeCivilisation();
        log(LOG_DEBUG, "-----------------------------------------------------");
        log(LOG_DEBUG, "test naissance");
        newCivilisation->listeCivilisation();
        ancienNbHumain = newCivilisation->getNbHumain();
        printf("ancienNbHumain = %d\n", ancienNbHumain);
        Element *enfant = naissance(newCivilisation, pere, mere);
        log(LOG_DEBUG, "creation d'un enfant en position %d", enfant->getElementId());
        resultatTest(rubrique, (enfant->getPere() == pere->getIdHumain()));
        resultatTest(rubrique, (enfant->getMere() == mere->getIdHumain()));
        newCivilisation->listeCivilisation();
        printf("getNbHumain = %d\n", newCivilisation->getNbHumain());
        resultatTest(rubrique, (newCivilisation->getNbHumain() == ancienNbHumain + 1));
        //newCivilisation.listeCivilisation();

        baniereTest(rubrique, (char *)"test deces et transfert capital");
        for (int i = 0 ; i < 100 ; i++){
            pere->evolutionHumain();
            mere->evolutionHumain();
        }
        log(LOG_DEBUG, "test deces du pere");
        int ancienSoldeEnfant = enfant->compteBancaireHumain->getSolde();
        int ancienSoldePere = pere->compteBancaireHumain->getSolde();
        int ancienSoldeMere = mere->compteBancaireHumain->getSolde();
        resultatTest(rubrique, (pere->execCommandeHumain((char*)"mortPossible")));
        resultatTest(rubrique, (pere->getStatusMarital() == STATUS_MARITAL_DECES));
        resultatTest(rubrique, (mere->compteBancaireHumain->getSolde() == (ancienSoldePere + ancienSoldeMere)));
        log(LOG_DEBUG, "test deces de mere");
        resultatTest(rubrique, (mere->execCommandeHumain((char*)"mortPossible")));
        resultatTest(rubrique, (mere->getStatusMarital() == STATUS_MARITAL_DECES));
        log(LOG_DEBUG, "test transfert capital");
        resultatTest(rubrique, (enfant->compteBancaireHumain->getSolde() == (ancienSoldeEnfant + ancienSoldePere + ancienSoldeMere)));

        baniereTest(rubrique, (char *)"test commande produit");
        Element *entreprise = newCivilisation->creeElementEntreprise(ACTIVITE_COMMERCE, (char *)"auBonPain", 25000, NULL);
        resultatTest(rubrique, (entreprise->getNbCommandes() == 0));
        pere->acheteProduit(entreprise, 1);
        resultatTest(rubrique, (entreprise->getNbCommandes() == 1));

        baniereTest(rubrique, (char *)"test commande achat produits");
        Element *entrepriseToto = newCivilisation->creeElementEntreprise(ACTIVITE_COMMERCE, (char *)"toto", 10000, NULL);
        Element *clientToto = newCivilisation->creeElementHumain(HOMME, (char*)"clientToto", 1000);
        //civilisation.listeCivilisation();
        resultatTest(rubrique, clientToto->testSiCommandeValideHumain((char *)"achat-toto")); 
        humain.acheteProduit(entrepriseToto,1);
        //civilisation.listeCivilisation();
        resultatTest(rubrique, (entrepriseToto->getNbCommandes() == 1));
        bilanTestsRubrique(rubrique);
        
        bilanTestsRubrique(rubrique);
    }

    //=======================================
    //
    //         tests classe Entreprise
    //
    //=======================================
    if (0 || exec_all || exec_entreprise){
        strcpy(rubrique, "entreprise");
        baniereDebutRubrique(rubrique);
        Civilisation newCivilisation;
        Element *elementEntreprise, *elementHumain;

        baniereTest(rubrique, (char *)"test creation entreprise avec fichier de configuration spécifique");
        elementEntreprise = newCivilisation.creeElementEntreprise(ACTIVITE_COMMERCE, (char *)"auBonPain", 10000, NULL);
        resultatTest(rubrique, (strcmp(elementEntreprise->getNomEntreprise(), (char *)"auBonPain") == 0));
        resultatTest(rubrique, (strcmp(elementEntreprise->getNomCommercialEntreprise(), (char *)"au bon pain") == 0));
        resultatTest(rubrique, (elementEntreprise->getNbSalaries() == 0));
        resultatTest(rubrique, (elementEntreprise->getCoutSalaries() == 80));
        resultatTest(rubrique, (elementEntreprise->getCoutProduit() == 3));
        resultatTest(rubrique, (elementEntreprise->getPrixProduit() == 10));
        resultatTest(rubrique, (elementEntreprise->getStockProduit() == 20));
        resultatTest(rubrique, (elementEntreprise->getMaxEmployes() == 5));
        resultatTest(rubrique, (elementEntreprise->getProductiviteSalarie() == 15));

        baniereTest(rubrique, (char *)"test creation entreprise avec fichier de configuration par default");
        elementEntreprise = newCivilisation.creeElementEntreprise(ACTIVITE_COMMERCE, (char *)"machin", 10000, NULL);
        resultatTest(rubrique, (strcmp(elementEntreprise->getNomEntreprise(), (char *)"machin") == 0));
        resultatTest(rubrique, (strcmp(elementEntreprise->getNomCommercialEntreprise(), (char *)"entreprise par default") == 0));
        resultatTest(rubrique, (elementEntreprise->getNbSalaries() == 0));
        resultatTest(rubrique, (elementEntreprise->getCoutSalaries() == 100));
        resultatTest(rubrique, (elementEntreprise->getCoutProduit() == 5));
        resultatTest(rubrique, (elementEntreprise->getPrixProduit() == 10));
        resultatTest(rubrique, (elementEntreprise->getStockProduit() == 0));

        baniereTest(rubrique, (char *)"test versement de salaire");
        elementHumain = newCivilisation.creeElementHumain(HOMME, (char *)"Adam", 1000);
        elementHumain = newCivilisation.creeElementHumain(FEMME, (char *)"Eve", 1000);
        //elementHumain = civilisation.getElement(idSalarie);
        int ancienSoldeHumain, ancienSoldeEntreprise, soldeAttendu;
        int salaire = 100;
        ancienSoldeHumain = elementHumain->compteBancaireHumain->getSolde();
        ancienSoldeEntreprise = elementEntreprise->compteBancaireEntreprise->getSolde();
        soldeAttendu = ancienSoldeHumain + salaire;
        elementEntreprise->verseSalaire(salaire, elementHumain);
        //printf("ancien solde = %d ; salaire = %d ; nouveau solde = %d\n", ancienSolde, salaire, nouveauSolde);
        resultatTest(rubrique, soldeAttendu == elementHumain->compteBancaireHumain->getSolde());
        soldeAttendu = ancienSoldeEntreprise - salaire;
        //printf("ancien solde = %d ; salaire = %d ; nouveau solde = %d\n", ancienSoldeEntreprise, salaire, soldeAttendu);
        resultatTest(rubrique, soldeAttendu == elementEntreprise->compteBancaireEntreprise->getSolde());

        baniereTest(rubrique, (char *)"test commande/livraison de produit");
        //elementEntreprise->creeCommande(elementHumain, 1);
        elementHumain->acheteProduit(elementEntreprise,1);
        log(LOG_DEBUG, "test l'entreprise embauche un salarie");
        elementEntreprise->embaucher();
        resultatTest(rubrique, elementEntreprise->getNbSalaries() > 0);
        log(LOG_DEBUG, "test l'entreprise effectue une production");
        elementEntreprise->produire();
        elementEntreprise->produire();
        resultatTest(rubrique, elementEntreprise->getStockProduit() > 0);
        resultatTest(rubrique, elementEntreprise->getNbCommandes() == 1);
        elementHumain->acheteProduit(elementEntreprise,1);
        resultatTest(rubrique, elementEntreprise->getNbCommandes() == 2);
        ancienSoldeHumain = elementHumain->compteBancaireHumain->getSolde();
        ancienSoldeEntreprise = elementEntreprise->compteBancaireEntreprise->getSolde();
        log(LOG_DEBUG, "anciens soldes : nb commandes en cours pour entreprise (%s) : (%d)", elementEntreprise->getNomEntreprise(), elementEntreprise->getNbCommandes());
        log(LOG_DEBUG, "anciens soldes : entreprise (%d) client (%d)", ancienSoldeEntreprise, ancienSoldeHumain);
        int prixProduit = elementEntreprise->getPrixProduit();
        elementEntreprise->livraison(elementHumain);
        log(LOG_DEBUG, "nouveaux soldes : nb commandes en cours pour entreprise (%s) : (%d)", elementEntreprise->getNomEntreprise(), elementEntreprise->getNbCommandes());
        log(LOG_DEBUG, "nouveaux soldes : entreprise (%d) client (%d) prix produit (%d)", elementEntreprise->compteBancaireEntreprise->getSolde(), 
                    elementHumain->compteBancaireHumain->getSolde(), prixProduit);
        resultatTest(rubrique, elementEntreprise->getNbCommandes() == 0);
        resultatTest(rubrique, (elementHumain->compteBancaireHumain->getSolde() == (ancienSoldeHumain - (prixProduit * 2))));
        resultatTest(rubrique, (elementEntreprise->compteBancaireEntreprise->getSolde() == (ancienSoldeEntreprise + (prixProduit * 2))));

        baniereTest(rubrique, (char *)"test fonction liste de commandes valide");
        resultatTest(rubrique, elementEntreprise->testSiCommandeValideEntreprise((char *)"produire"));
        resultatTest(rubrique, elementEntreprise->testSiCommandeValideEntreprise((char *)"embaucher"));
        resultatTest(rubrique, elementEntreprise->testSiCommandeValideEntreprise((char *)"livraison"));
        resultatTest(rubrique, !elementEntreprise->testSiCommandeValideEntreprise((char *)"sdfqsdfqdf"));

        baniereTest(rubrique, (char *)"test execution commandes");
        resultatTest(rubrique, elementEntreprise->execCommandeEntreprise((char *)"produire"));
        resultatTest(rubrique, !elementEntreprise->execCommandeEntreprise((char *)"toto"));
        resultatTest(rubrique, (elementEntreprise->getNbSalaries() == 1));
        resultatTest(rubrique, elementEntreprise->execCommandeEntreprise((char *)"embaucher"));
        resultatTest(rubrique, (elementEntreprise->getNbSalaries() == 2));
        resultatTest(rubrique, elementEntreprise->execCommandeEntreprise((char *)"debaucher"));
        resultatTest(rubrique, (elementEntreprise->getNbSalaries() == 1));
        resultatTest(rubrique, elementEntreprise->execCommandeEntreprise((char *)"livraison"));
    }

    //=======================================
    //
    //         tests classe CompteBancaire
    //
    //=======================================
    if (0 || exec_all || exec_banque){
        strcpy(rubrique, "banque");
        baniereDebutRubrique(rubrique);

        baniereTest(rubrique, (char *)"test creation de compte");
        CompteBancaire cpt(NULL);
        resultatTest(rubrique, cpt.getSolde() == 0);
        cpt.initCompteBancaire(NULL, 100);
        resultatTest(rubrique, cpt.getSolde() == 100);

        baniereTest(rubrique, (char *)"test creation de compte initialisé");
        CompteBancaire cpt1(NULL, 1000);
        resultatTest(rubrique, cpt1.getSolde() == 1000);

        baniereTest(rubrique, (char *)"test gestion epargne");
        cpt.sauveEpargne(50);
        resultatTest(rubrique, (cpt.getSolde() == 50) && (cpt.getEpargne() == 50));
        cpt.restitueEpargne(25);
        resultatTest(rubrique, (cpt.getSolde() == 75) && (cpt.getEpargne() == 25));

        baniereTest(rubrique, (char *)"test virement simple");
        CompteBancaire cpt2(NULL, 100);
        cpt1.virement(&cpt2, 500);
        resultatTest(rubrique, (cpt1.getSolde() == 500) && (cpt2.getSolde() == 600));

        baniereTest(rubrique, (char *)"test virement négatif impossible");
        resultatTest(rubrique, !cpt1.virement(&cpt2, -100));

        baniereTest(rubrique, (char *)"test virement vers compte NULL");
        resultatTest(rubrique, !cpt1.virement(NULL, 100));

        bilanTestsRubrique(rubrique);
    }

    bilanTests();

    baniereFinTests();

}