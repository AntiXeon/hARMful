CC          = g++
ARCH        = $(shell uname -m)

LIB_NAME    = DemoLib
LIB_DIR     = ../$(LIB_NAME)/lib/$(ARCH)
INCL_DIR    = ../$(LIB_NAME)/include

SRC         = DemoSoft.cpp
INCLUDE     = 
LIB         = -L$(LIB_DIR)/ -lDEMO
BIN         = DemoSoft


all:
	$(CC) -I$(INCL_DIR) $(SRC) -o $(BIN) $(LIB) 
	@ln -sf ../$(LIB_NAME)/lib/
