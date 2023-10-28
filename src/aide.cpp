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
    printf("      -l [none | info | warning | error | debug] => fixe le niveau de log\n");
    printf("      -t [all|civilisation|element|humain|entreprise|tools|banque] => doit etre le dernier parametre\n");
    printf("commandes disponibles en execution (ligne de commande)\n");
    printf("    commandes : affichage de la liste des commandes et variables disponibles\n");
    printf("    cree [humain <sexe> <nom> <capital> | entreprise <activite> <nom> <capital>] : création d'un nouvel element\n");
    printf("    loglevel [none | debug | error | warning | info] : change le niveau de log\n");
    printf("    historique, ! : affiche historique des commandes\n");
    printf("    aide, ? : affichage de cette aide\n");
    printf("    liste [id] : affichage de la liste des éléments, ou un element specifique\n");
    printf("    liste [humain|entreprise|banque] : active/desactive affichage des rubrique avec la commande liste\n");
    printf("    auto [liste|tableau] : switch on/off sur affichage automatique de la liste des elements ou du tableau de bord\n");
    printf("    q, Q, quit : quitte le programme\n");
    printf("    t, T : affichage du tableau de bord\n");
    printf("    RC : une ligne vide (touche enter) lance une évolution\n");
    printf("    xx : execute xx fois l'évolution\n");
    printf("Pendant l'execution du programme des scripts modifiable sont executes afin de modifier le comportement du logiciel\n");
    printf("    ces scripts sont situes dans le repertoires scripts\n");
    printf("    plusieurs types de scripts sont possibles\n");
    printf("        scripts d'initialisation, (execute lors de la creation d'un element) : \n");
    printf("            civilisation.scr : execute lors de la creation de la civilisation initiale\n");
    printf("            entreprise/<nom> : ces scripts permettent de definir la configuration specifique d'une entreprise lors de sa creation\n");
    printf("        A chaque evolution un script est lance pour chaque type d'element : \n");
    printf("            humain.scr : execute lors de l'evolution d'un humain\n");
    printf("            entreprise.scr : execute lors de l'evolution d'une entreprise\n");
}
