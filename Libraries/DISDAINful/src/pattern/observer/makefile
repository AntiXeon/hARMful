SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

ROOT_DIR = ../..

OBSERVABLE_CLASS = Observable
OBSERVER_INTERFACE = ObserverInterface

all : $(OBSERVABLE_CLASS).o $(OBSERVER_INTERFACE).o

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(CCOPTS)
