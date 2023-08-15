#############################################################
#                   M a k e f i l e 
# 
#     généré automatiquement le 15/08/2023 à 22:37:22
#         avec buildMakefile (version du 19 Oct 2022)
#                 (c) B. Froger 
# 
#############################################################

#------------------------------------------------------------
# Définition des variables
#------------------------------------------------------------
CC=gcc
CCFLAGS=-Wall 
LDFLAGS=

SRCDIR=src
INCDIR=inc
OBJDIR=obj
BINDIR=bin
INSTALLDIR=~/bin

SRCCPP=$(wildcard $(SRCDIR)/*.cpp)
SRCC=$(wildcard $(SRCDIR)/*.c)
TMPCPP=$(patsubst %.cpp, %.o, $(SRCCPP))
TMPC=$(patsubst %.c, %.o, $(SRCC))
TMP=$(TMPCPP) $(TMPC)
OBJ=$(patsubst $(SRCDIR)/%.o, $(OBJDIR)/%.o, $(TMP))
EXEC = $(BINDIR)/civilisation

#------------------------------------------------------------
# Définition des règles génériques
#------------------------------------------------------------
ALL : $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) $(LDFLAGS) $(OBJ) -o $@
	@echo "Edition de lien de $@ OK"

#------------------------------------------------------------
# Définition des règles pour chaque fichier source
#------------------------------------------------------------
$(OBJDIR)/element.o: $(SRCDIR)/element.cpp \
	$(INCDIR)/element.hpp \
	$(INCDIR)/log.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/entreprise.o: $(SRCDIR)/entreprise.cpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/humain.o: $(SRCDIR)/humain.cpp \
	$(INCDIR)/humain.hpp \
	$(INCDIR)/log.hpp \
	$(INCDIR)/element.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/log.o: $(SRCDIR)/log.cpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp \
	$(INCDIR)/log.hpp \
	$(INCDIR)/humain.hpp \
	$(INCDIR)/tests.hpp \
	$(INCDIR)/element.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/tests.o: $(SRCDIR)/tests.cpp \
	$(INCDIR)/element.hpp \
	$(INCDIR)/humain.hpp \
	$(INCDIR)/log.hpp
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
