ROOT_DIR = ../..

# Folders where make must be launched too
MEMORY_DIR = memory
PATHFINDING_DIR = pathfinding

# Classes to compile in the current folder
ARTIFICIALINTELLIGENCE_CLASS = ArtificialIntelligence

all : $(ARTIFICIALINTELLIGENCE_CLASS).o
	@cd $(MEMORY_DIR) && $(MAKE)
	@cd ../
	@cd $(PATHFINDING_DIR) && $(MAKE)
	@cd ../

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(CCOPTS)
