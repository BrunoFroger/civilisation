//-----------------------------------------
//
//          lectureClavier.cpp
//
//-----------------------------------------

#include <cstdio>
#include <cstring>
#include <curses.h>
#include <unistd.h>

char tmpLectureClavier[100];

//-----------------------------------------
//
//          lectureClavier
//
//-----------------------------------------
char *lectureClavier(void){
    strcpy(tmpLectureClavier, "");
    char car;
    int i = 0;
    bool fin = false;
    initscr();
    while (!fin){
        // lecture d'un caractere au clavier
        fflush(stdin);
        usleep(1000);
        car = getch();
        //if (car != -1){        
            printf("car lu : %c(%d)\n", car, car);
        //}
        switch(car){
            case 13 : // touche entree
            case 10:
                printf(" touche entree .... fin\n");
                fin = true;
                break;
            default:
                if (car != -1){        
                    printf("car lu : %c(%d)\n", car, car);        
                    //putchar(car);
                    tmpLectureClavier[i++] = car;
                    tmpLectureClavier[i] = '\0';
                }
                break;
        }
    }
    printf("commande saisie : %s\n", tmpLectureClavier);
    return tmpLectureClavier; 
}