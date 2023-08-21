//-----------------------------------------
//
//          tools.cpp
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>


//-----------------------------------------
//
//          remove_extra_spaces
//
//-----------------------------------------
void remove_extra_spaces(char* str) {
    int i, j;
    int len = strlen(str);

    for (i = 0, j = 0; i < len; i++) {
        if (str[i] != ' ' || (i > 0 && str[i - 1] != ' ')) {
            str[j++] = str[i];
        }
    }
    while (str[j - 1] == ' '){
        str[j - 1] = '\0';
        j--;
    }
    str[j] = '\0';
}