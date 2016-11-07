###############################################
# Debugging Options and Log Extension - Tests #
###############################################
# DOOMful Makefile                            #
# Author: Denis CARLUS                        #
# Version 1, 2014/03/27                       #
###############################################

CC      	= g++
CCOPTS      = -W -Wall -g3

ARCH        = $(shell uname -m)
BIN_DIR     = ../bin
LIB_DIR		= ../lib

BIN         = $(BIN_DIR)/test
INCLUDES    = -I../include/
LIBS        = -lpthread -L$(LIB_DIR)/$(ARCH)/ -lDOOM
SRC         = Threads.cpp

all:
	@cd $(BIN_DIR) && ln -sf $(LIB_DIR)
	@$(CC) $(SRC) -o $(BIN) $(CCOPTS) $(INCLUDES) $(LIBS)

debug:
	@valgrind -v ./$(BIN)

clean:
	@rm $(BIN)
