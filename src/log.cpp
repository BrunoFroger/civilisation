//-----------------------------------------
//
//          log.cpp
//
//-----------------------------------------

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "../inc/log.hpp"

int logLevelLimit=LOG_INFO;

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
    sprintf(logDate, "%02d-%02d-%04d %02d:%02d", day, mois, an, h, min);

    switch (logLevel){
        case 0:
            strcpy(logLevelString, "INFO");
            break;
        case 1:
            strcpy(logLevelString, "WARNING");
            break;
        case 2:
            strcpy(logLevelString, "ERROR");
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
            vsprintf(message, format, args);
        }
        sprintf(ligne, "civilisation (%s) %s => %s", logLevelString, logDate, message);
        printf("%s\n",ligne);
    }
    va_end(args);
}   

//-----------------------------------------
//
//          setLogLevel
//
//-----------------------------------------
void setLogLevel(int logLevel){
    log(LOG_DEBUG, "setLogLevel %d", logLevel);
    logLevelLimit = logLevel;
}