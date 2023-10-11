//-----------------------------------------
//
//          aide.cpp
//
//-----------------------------------------

#include <cstdio>


void aide(void){

    printf("Syntaxe du programme civilisation \n");
    printf("civilisation [-options]\n");
    printf("      -c nomFichier => fixe le nom du fichier de configuration a utiliser (civilisation.scr par defaut) doit etre dans le repertoire scripts\n");
    printf("      -e => arret si test en erreur uniquement si option test active -t\n");
    printf("      -l [info|warning|error|debug] => fixe le niveau de log\n");
    printf("      -t [all|civilisation|element|humain|entreprise|tools|banque] => doit etre le dernier parametre\n");
    printf("commandes disponibles en execution (ligne de commande)\n");
    printf("    commandes : affichage de la liste des commandes et variables disponibles\n");
    printf("    cree [humain <sexe> <nom> <capital> | entreprise <activite> <nom> <capital>] : création d'un nouvel element\n");
    printf("    logLevel [debug | error | warning | info] : change le niveau de log\n");
    printf("    historique, ! : affiche historique des commandes\n");
    printf("    aide : affichage de cette aide\n");
    printf("    liste [id] : affichage de la liste des éléments, ou un element specifique\n");
    printf("    q, Q, quit : quitte le programme\n");
    printf("    t, T : affichage du tableau de bord\n");
}
