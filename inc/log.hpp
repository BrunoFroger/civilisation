//-----------------------------------------
//
//          log.hpp
//
//-----------------------------------------


#ifndef __LOG__
#define __LOG__

    #define LOG_NONE    -1
    #define LOG_ERROR   0
    #define LOG_WARNING 1
    #define LOG_INFO    2
    #define LOG_DEBUG   3

    extern void log(int logLevel, const char *format, ...);
    extern void setLogLevel(int logLevel);
    extern void restoreLogLevel(void);
    extern int getLogLevel(void);

#endif