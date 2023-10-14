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
    while (!fin){
        // lecture d'un caractere au clavier
        car = getchar();
        switch(car){
            case 13 : // touche entree
            case 10:
                printf(" touche entree .... fin");
                fin = true;
                break;
            default:
                putchar(car);
                tmpLectureClavier[i++] = car;
                tmpLectureClavier[i] = '\0';
                break;
        }
    }
    return tmpLectureClavier; 
}