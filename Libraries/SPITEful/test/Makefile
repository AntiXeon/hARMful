###########################################################
# Saving and Parsing Images, Texts and Extra - Test Tools #
###########################################################
# SPITEful Makefile                                       #
# Author: Denis CARLUS                                    #
# Version 1, 2015/29/01                                   #
###########################################################

CC          = g++
CCOPTS      = -W -Wall -O3 -ffast-math -Wl,-rpath,lib


# Source and compiled objects
SOURCES_DIR = .
PATH_Bin    = path

# Required external tools
ARCH        = $(shell uname -m)
BINARY      = ../bin/$(ARCH)
DOOMful		= ../../DOOMful
INCLUDE     = -I../include -I$(DOOMful)/include 
LIB_DIR     = ../lib
LIBRARY     = -lpthread -L$(LIB_DIR)/$(ARCH) -lSPITE -L$(DOOMful)/lib/$(ARCH) -lDOOM



# Rules
%.o: %.cpp
	@echo -e "Compiling" $(notdir $@)
	@$(CC) $(CCOPTS) $(INCLUDE) -c $< -o $@

all: MakeDir $(PATH_Bin)

MakeDir:
	@mkdir -p $(BINARY)
	@cd $(BINARY) && ln -sf ../$(LIB_DIR) 


$(PATH_Bin): $(PATH_Bin).o
	@$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $(LIBRARY) $@.o


clean:
	@rm -f $(BINARY)/*.test
	@rm -f $(SOURCES_DIR)/*.o

shared: Shared
