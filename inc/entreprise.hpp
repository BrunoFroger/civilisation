//-----------------------------------------
//
//          entreprise.hpp
//
//-----------------------------------------

#ifndef __ENTREPRISE__
#define __ENTREPRISE__

    class Entreprise{
        public:
            void initEntreprise(long id, const char *nom);
            void evolution(void);
            long getId();
            char *getNom();

        private:
            int id;
            char nom[50]; 
    };

#endif