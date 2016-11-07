SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

ROOT_DIR = ..

# Folders where make must be launched too
OBSERVER_DIR = observer

# Classes to compile in the current folder
NOCOPY_CLASS = NoCopy

all : $(NOCOPY_CLASS).o
	@cd $(OBSERVER_DIR) && $(MAKE)

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(CCOPTS)
