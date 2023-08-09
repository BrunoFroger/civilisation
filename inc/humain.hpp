//-----------------------------------------
//
//          humain.hpp
//
//-----------------------------------------

#ifndef __HUMAIN__
#define __HUMAIN__

    #define HOMME   0
    #define FEMME   1

    class Humain{
        public:
            void init(long id, int sexe, const char *nom);
            void evolution(void);
            long getId();
            char *getNom();
            int getSexe();
            int getAge();
            bool getCelibataire();
            bool execScript(void);
            bool isVariable(char *nomVariable);
            int getIntValue(char *nomVariable);
            long getLongValue(char *nomVariable);
            char *getCharValue(char *nomVariable);
            bool testCommandeSiVraiValide(char *valeur);

        private:
            long id;
            int sexe;   // 0 : homme, 1 = femme
            char nom[50];
            long age;
            bool celibataire;
    };

#endif