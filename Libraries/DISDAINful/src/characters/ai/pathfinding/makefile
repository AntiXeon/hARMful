ROOT_DIR = ../../..

# Classes in the current directory to compile
#ASTARPATHFINDING_CLASS = AStarPathfinding
PATHFINDING_CLASS = Pathfinding
STATENODE_CLASS = StateNode

# Rules
all : $(PATHFINDING_CLASS).o $(STATENODE_CLASS).o

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) $(CCOPTS) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(DEPENDENCIES)
