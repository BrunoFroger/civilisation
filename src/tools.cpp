//-----------------------------------------
//
//          tools.cpp
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>

#include "../inc/humain.hpp"
#include "../inc/log.hpp"
#include "../inc/tools.hpp"

#define MAX_HUMAIN  3

long courantId=0;
Humain population[MAX_HUMAIN];

//-----------------------------------------
//
//          initPopulation
//
//-----------------------------------------
void initPopulation(void){
    //log(LOG_INFO, "initPopulation : debut");
    for (int i = 0 ; i < MAX_HUMAIN ; i++){
        population[i].init(-1,-1,"");
    }
    //log(LOG_INFO, "initPopulation : fin");
}

//-----------------------------------------
//
//          evolutionPopulation
//
//-----------------------------------------
void evolutionPopulation(void){
    for (int i = 0 ; i < MAX_HUMAIN ; i++){
        if (population[i].getId() != -1){
            population[i].evolution();
        }
    }
}

//-----------------------------------------
//
//          killPopulation
//
//-----------------------------------------
void killPopulation(void){
    for (int i = 0 ; i < MAX_HUMAIN ; i++){
        //delete population[i];
    }
}

//-----------------------------------------
//
//          newId
//
//-----------------------------------------
long newId(){
    courantId ++;
    //printf("nouvel id : %ld\n", courantId);
    return courantId;
}

//-----------------------------------------
//
//          getId
//
//-----------------------------------------
long getId(){
    printf("courant id : %ld\n", courantId);
    return courantId;
}

//-----------------------------------------
//
//          creeHumain
//
//-----------------------------------------
void creeHumain(int sexe, const char *nom){
    population[courantId].init(courantId, sexe, nom);
    newId();
}

//-----------------------------------------
//
//          listePopulation
//
//-----------------------------------------
void listePopulation(void){
    printf("+--------------------------------------------------------+\n");
    printf("|             population  %4ld individus                 |\n", courantId);
    printf("+--------+---------------------------+-----+-------+-----+\n");
    printf("|   id   |                       nom | sexe|  age  |celib|\n");
    printf("+--------+---------------------------+-----+-------+-----+\n");
    for (int i = 0 ; i < MAX_HUMAIN ; i++){
        Humain *ptr = &population[i];
        if (ptr->getId() != -1){
            printf("| %5ld  | %25s |  %d  | %5d |  %d  |\n", 
                ptr->getId(),
                ptr->getNom(), 
                ptr->getSexe(),
                ptr->getAge(),
                ptr->getCelibataire());
        }
    }
    printf("+--------+---------------------------+-----+-------+-----+\n");
}

//-----------------------------------------
//
//          decomposeIf
//
//-----------------------------------------
bool decomposeSi(char *ligne, structIf *resultat){

    int i = 0;
    strcpy(resultat->dataOrigine,"");
    strcpy(resultat->dataReference,"");
    strcpy(resultat->operateurTest,"");
    strcpy(resultat->commandeSiVrai,"");
    if (strncmp(ligne, "si", 2) != 0){
        return false;
    } else {
        int decalage = 2;
        i=0;
        while (ligne[decalage] == ' ') decalage++;  // suppression des blancs entre chaque item
        while (ligne[decalage] != ' '){
            if (decalage >= strlen(ligne)) return false;
            //printf("on ajoute '%c' a reference.origine\n", ligne[decalage] );
            resultat->dataOrigine[i] = ligne[decalage];
            i++; decalage++;
            resultat->dataOrigine[i] = '\0';
        }
        i=0;
        while (ligne[decalage] == ' ') decalage++;  // suppression des blancs entre chaque item
        while (ligne[i + decalage] != ' '){
            if (decalage >= strlen(ligne)) return false;
            //printf("on ajoute '%c' a reference.origine\n", ligne[decalage] );
            resultat->operateurTest[i] = ligne[decalage];
            i++; decalage++;
            resultat->operateurTest[i] = '\0';
        }
        i=0;
        while (ligne[decalage] == ' ') decalage++;  // suppression des blancs entre chaque item
        while (ligne[decalage] != ' '){
            if (decalage >= strlen(ligne)) return false;
            //printf("on ajoute '%c' a reference.origine\n", ligne[decalage] );
            resultat->dataReference[i] = ligne[decalage];
            i++; decalage++;
            resultat->dataReference[i] = '\0';
        }
        i=0;
        while (ligne[decalage] == ' ') decalage++;  // suppression des blancs entre chaque item
        while (ligne[decalage] != ' '){
            if (decalage >= strlen(ligne)) break;
            //printf("on ajoute '%c' a reference.origine\n", ligne[decalage] );
            resultat->commandeSiVrai[i] = ligne[decalage];
            i++; decalage++;
            resultat->commandeSiVrai[i] = '\0';
        }
        //printf("commandeSiVrai = '%s'\n", resultat->commandeSiVrai);
        if (strlen(resultat->commandeSiVrai) == 0) return false;
    }
    //printf("decomposeIf : OK\n");
    return true;
}

//-----------------------------------------
//
//          evaluation
//
//-----------------------------------------
bool evaluation(int data1, char *test, int data2){
    //printf("test '='\n");
    if (strcmp(test, "=") == 0) return (data1==data2);
    //printf("test '!='\n");
    if (strcmp(test, "!=") == 0) return !(data1==data2);
    if (strcmp(test, ">") == 0) return (data1>data2);
    if (strcmp(test, "<") == 0) return (data1<data2);
    if (strcmp(test, ">=") == 0) return (data1 >= data2);
    if (strcmp(test, "<=") == 0) return (data1 <= data2);
    //printf("aucun test valide\n");
    return false;
}