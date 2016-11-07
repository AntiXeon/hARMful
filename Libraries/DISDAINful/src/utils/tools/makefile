ROOT_DIR = ../..

# Classes in the current directory to compile
POINT_CLASS = Point
LEVELMAP2D_CLASS = LevelMap2D
LEVELPARSER_CLASS = LevelParser

# Rules
all : $(POINT_CLASS).o $(LEVELMAP2D_CLASS).o $(LEVELPARSER_CLASS).o

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(CCOPTS)
