//-----------------------------------------
//
//          tests.hpp
//
//-----------------------------------------

#ifndef __TESTS__
#define __TESTS__

    #define TEST_MODE_STD   0
    #define TEST_MODE_ALL   1
    #define TEST_MODE_CIVI  2
    #define TEST_MODE_ELEM  3
    #define TEST_MODE_HUMA  4
    #define TEST_MODE_ENTR  5
    #define TEST_MODE_TOOL  6
    #define TEST_MODE_BANK  7

    extern void executeTests(int mode);

#endif