//-----------------------------------------
//
//          log.cpp
//
//-----------------------------------------

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <cstdlib>
#include <time.h>

#include "../inc/log.hpp"

//Paramètre  Couleur
//0 reinit |30 Noir |31 Rouge | 32 Vert | 33 Jaune | 34 Bleu| 35 Magenta | 36 Cyan | 37 Blanc
#define color(param) printf("\033[%dm",param)

int logLevelLimit=LOG_INFO;
int oldLogLevel=LOG_INFO;

//-----------------------------------------
//
//          log
//
//-----------------------------------------
void log(int logLevel, const char *format, ...){
    char ligne[500];
    char message[500];
    char logLevelString[10];
    va_list args;    
    int h, min, s, day, mois, an;
    time_t now;
    char logDate[50];
    time(&now);
    struct tm *local = localtime(&now);
    h = local->tm_hour;
    min = local->tm_min;
    s = local->tm_sec;
    day = local->tm_mday;
    mois = local->tm_mon + 1;
    an = local->tm_year + 1900;
    snprintf(logDate, sizeof(logDate), "%02d-%02d-%04d %02d:%02d:%02d", day, mois, an, h, min, s);

    switch (logLevel){
        case 0:
            strcpy(logLevelString, "ERROR");
            break;
        case 1:
            strcpy(logLevelString, "WARNING");
            break;
        case 2:
            strcpy(logLevelString, "INFO");
            break;
        case 3:
            strcpy(logLevelString, "DEBUG");
            break;
        default:
            printf("Niveau de log incorrect : %d\n", logLevel);
            break;
    }

    va_start(args, format);
    if (logLevel <= logLevelLimit){
        if (sizeof(args) > 1) {
            vsnprintf(message, sizeof(message), format, args);
        }
        if (logLevel == 0) color(31);   // erreur
        if (logLevel == 1) color(33);   // warning
        if (logLevel == 3) color(34);   // debug
        snprintf(ligne, sizeof(ligne), "civilisation (%s) %s => %s", logLevelString, logDate, message);
        printf("%s\n",ligne);
        color(0);
    }
    va_end(args);
}   

//-----------------------------------------
//
//          setLogLevel
//
//-----------------------------------------
void setLogLevel(int logLevel){
    oldLogLevel = logLevelLimit;
    logLevelLimit = logLevel;
    log(LOG_DEBUG, "setLogLevel %d", logLevel);
} 

//-----------------------------------------
//
//          restoreLogLevel
//
//-----------------------------------------
void restoreLogLevel(void){
    log(LOG_DEBUG, "restoreLogLevel %d", oldLogLevel);
    logLevelLimit = oldLogLevel;
}