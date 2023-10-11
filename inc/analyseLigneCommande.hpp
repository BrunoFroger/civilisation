//-----------------------------------------
//
//          analyseLigneCommande.hpp
//
//-----------------------------------------


#ifndef __ANALYSELIGNECOMMANDE__
#define __ANALYSELIGNECOMMANDE__

    #define NB_COMMANDE_HISTORIQUE  30

    extern void analyseLigneCommande(char *ligneCommande);
    extern void historiseCommande(char *ligneCommande);
    extern void initHistoriqueCommande(void);
    extern void afficheHistorique(void);

#endif
