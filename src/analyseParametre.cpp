//-----------------------------------------
//
//          analyseParametres.cpp
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>

#include "../inc/log.hpp"
#include "../inc/tests.hpp"

bool analyseParametres(int argc, char **argv){
    setLogLevel(LOG_INFO);
    log(LOG_DEBUG, "analyseParametres");
    if (argc > 1){
        for (int i = 1 ; i < argc ; i++){
            //printf("Analyse du parametre %s\n", argv[i]);
            if (strcmp(argv[i], "tests") == 0){
                log(LOG_INFO, "     execution des tests ");
                log(LOG_INFO, "===================================");
                executeTests(TEST_MODE_STD);
                return false;
            }
            if (argv[i][0] == '-'){
                int tmpExecTest = TEST_MODE_STD;
                // analyse d'une option
                switch(argv[i][1]){
                    case 'l':
                    case 'L':
                        // modification du niveau de log
                        if (strcmp(argv[i+1], "info") == 0){
                            setLogLevel(LOG_INFO);
                            i++;
                        } else if (strcmp(argv[i+1], "waarning") == 0){
                            setLogLevel(LOG_WARNING);
                            i++;
                        } else if (strcmp(argv[i+1], "error") == 0){
                            setLogLevel(LOG_ERROR);
                            i++;
                        } else if (strcmp(argv[i+1], "debug") == 0){
                            setLogLevel(LOG_DEBUG);
                            i++;
                        } else {
                            printf("ERREUR : niveau de log (%s) inconnu\n", argv[i+1]);
                        }
                        break;
                    case 't':
                    case 'T':
                        log(LOG_INFO, "     execution des tests ");
                        log(LOG_INFO, "===================================");
                        printf("i+1=%d, argc=%d\n", i+1, argc);
                        if ((i+1) < argc){
                            printf("argv[i+1] = %s\n", argv[i+1]);
                            if (strcmp(argv[i+1], "all") == 0){
                                printf("set test mode exec all\n");
                                tmpExecTest = TEST_MODE_ALL;
                            } else if (strcmp(argv[i+1], "civilisation") == 0){
                                printf("set test mode exec civilisation\n");
                                tmpExecTest = TEST_MODE_CIVI;
                            } else if (strcmp(argv[i+1], "element") == 0){
                                printf("set test mode exec element\n");
                                tmpExecTest = TEST_MODE_ELEM;
                            } else if (strcmp(argv[i+1], "humain") == 0){
                                printf("set test mode exec humain\n");
                                tmpExecTest = TEST_MODE_HUMA;
                            } else if (strcmp(argv[i+1], "entreprise") == 0){
                                printf("set test mode exec entreprise\n");
                                tmpExecTest = TEST_MODE_ENTR;
                            } else if (strcmp(argv[i+1], "tools") == 0){
                                printf("set test mode exec tools\n");
                                tmpExecTest = TEST_MODE_TOOL;
                            } else if (strcmp(argv[i+1], "banque") == 0){
                                printf("set test mode exec tools\n");
                                tmpExecTest = TEST_MODE_BANK;
                            } else {
                                printf("ERREUR mode de selectiond e test (%s) inconnu\n", argv[i+1]);
                            }
                            i++;
                        }
                        executeTests(tmpExecTest);
                        return false;
                        break;
                    default:
                        printf("ERREUR : option %c inconnue\n", argv[i][1]);
                        return false;
                        break;
                }
            }
        }
    }
    return true;
}
