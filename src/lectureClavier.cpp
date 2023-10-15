//-----------------------------------------
//
//          lectureClavier.cpp
//
//-----------------------------------------

#include <cstdio>
#include <cstring>

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
    fflush(stdin);
    while (!fin){
        // lecture d'un caractere au clavier
        car = getc(stdin);
        switch(car){
            case 13 : // touche entree
            case 10:
                printf(" touche entree .... fin");
                fin = true;
                break;
            default:
                printf("car lu : %c\n", car);
                //putchar(car);
                tmpLectureClavier[i++] = car;
                tmpLectureClavier[i] = '\0';
                break;
        }
    }
    return tmpLectureClavier; 
}