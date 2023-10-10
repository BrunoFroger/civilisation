#############################################################
#                   M a k e f i l e 
# 
#     généré automatiquement le 10/10/2023 à 16:16:19
#         avec buildMakefile (version du 23 Aug 2023)
#                 (c) B. Froger 
# 
#############################################################

#------------------------------------------------------------
# Définition des variables
#------------------------------------------------------------
# de compilation
CC=g++
CCFLAGS=-Werror -Wall 
LDFLAGS=

# de definition des répertoires
SRCDIR=src
INCDIR=inc
OBJDIR=obj
BINDIR=bin
INSTALLDIR=~/bin

# de definition des listes de fichiers a traiter
SRCCPP=$(wildcard $(SRCDIR)/*.cpp)
SRCC=$(wildcard $(SRCDIR)/*.c)
TMPCPP=$(patsubst %.cpp, %.o, $(SRCCPP))
TMPC=$(patsubst %.c, %.o, $(SRCC))
TMP=$(TMPCPP) $(TMPC)
OBJ=$(patsubst $(SRCDIR)/%.o, $(OBJDIR)/%.o, $(TMP))
EXEC = $(BINDIR)/civilisation

# des autres variables
ENTETE = $(info ******************************) $(info *) $(info *   M A K E (civilisation)) $(info *) $(info ******************************)

#------------------------------------------------------------
# Définition des règles génériques
#------------------------------------------------------------
ALL : $(info $(ENTETE)) $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) $(LDFLAGS) $(OBJ) -o $@
	@echo "Edition de lien de $@ OK"

#------------------------------------------------------------
# Définition des règles pour chaque fichier source
#------------------------------------------------------------
$(OBJDIR)/aide.o: $(SRCDIR)/aide.cpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/analyseLigneCommande.o: $(SRCDIR)/analyseLigneCommande.cpp \
	$(INCDIR)/log.hpp \
	$(INCDIR)/civilisation.hpp \
	$(INCDIR)/tools.hpp \
	$(INCDIR)/aide.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/analyseParametre.o: $(SRCDIR)/analyseParametre.cpp \
	$(INCDIR)/log.hpp \
	$(INCDIR)/tests.hpp \
	$(INCDIR)/aide.hpp \
	$(INCDIR)/civilisation.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/civilisation.o: $(SRCDIR)/civilisation.cpp \
	$(INCDIR)/civilisation.hpp \
	$(INCDIR)/log.hpp \
	$(INCDIR)/element.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/compteBancaire.o: $(SRCDIR)/compteBancaire.cpp \
	$(INCDIR)/compteBancaire.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/element.o: $(SRCDIR)/element.cpp \
	$(INCDIR)/element.hpp \
	$(INCDIR)/log.hpp \
	$(INCDIR)/tools.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/entreprise.o: $(SRCDIR)/entreprise.cpp \
	$(INCDIR)/entreprise.hpp \
	$(INCDIR)/log.hpp \
	$(INCDIR)/tools.hpp \
	$(INCDIR)/civilisation.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/humain.o: $(SRCDIR)/humain.cpp \
	$(INCDIR)/humain.hpp \
	$(INCDIR)/log.hpp \
	$(INCDIR)/element.hpp \
	$(INCDIR)/civilisation.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/log.o: $(SRCDIR)/log.cpp \
	$(INCDIR)/log.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp \
	$(INCDIR)/log.hpp \
	$(INCDIR)/humain.hpp \
	$(INCDIR)/tests.hpp \
	$(INCDIR)/element.hpp \
	$(INCDIR)/civilisation.hpp \
	$(INCDIR)/analyseParametres.hpp \
	$(INCDIR)/aide.hpp \
	$(INCDIR)/analyseLigneCommande.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/tests.o: $(SRCDIR)/tests.cpp \
	$(INCDIR)/civilisation.hpp \
	$(INCDIR)/element.hpp \
	$(INCDIR)/humain.hpp \
	$(INCDIR)/log.hpp \
	$(INCDIR)/tests.hpp \
	$(INCDIR)/tools.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/tools.o: $(SRCDIR)/tools.cpp \
	$(INCDIR)/element.hpp \
	$(INCDIR)/log.hpp \
	$(INCDIR)/civilisation.hpp \
	$(INCDIR)/humain.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

#------------------------------------------------------------
# Définition des règles utilitaires
#------------------------------------------------------------
clean: 
	@rm -f $(OBJDIR)/* $(BINDIR)/*
	@echo "Clean OK"

info: 
	@echo "Liste des variables du makefile"
	@echo "CC         = " $(CC)
	@echo "CCFLAGS    = " $(CCFLAGS)
	@echo "LDFLAGS    = " $(LDFLAGS)
	@echo "SRCDIR     = " $(SRCDIR)
	@echo "INCDIR     = " $(INCDIR)
	@echo "OBJDIR     = " $(OBJDIR)
	@echo "BINDIR     = " $(BINDIR)
	@echo "INSTALLDIR = " $(INSTALLDIR)
	@echo "SRCCPP     = " $(SRCCPP)
	@echo "SRCC       = " $(SRCC)
	@echo "TMPCPP     = " $(TMPCPP)
	@echo "TMPC       = " $(TMPC)
	@echo "TMP        = " $(TMP)
	@echo "OBJ        = " $(OBJ)
	@echo "EXEC       = " $(EXEC)

install: 
	@make
	@rm -f $(INSTALLDIR)/civilisation
	@cp -f $(BINDIR)/civilisation ~/bin
	@chmod +x $(INSTALLDIR)/civilisation
	@echo "installation de civilisation dans ~/bin OK"
