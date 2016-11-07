ROOT_DIR = ..

# Folders where make must be launched too
AI_DIR = ai
BODY_DIR = body

# Classes to compile in the current folder
CHARACTER_CLASS = Character
COLONYDATA_CLASS = ColonyData
COLONYSTRATEGY_CLASS = ColonyStrategy
COLONYMANAGER_CLASS = ColonyManager
STATISTICS_CLASS = Statistics
STATUS_CLASS = Status

all : $(CHARACTER_CLASS).o $(COLONYDATA_CLASS).o $(COLONYSTRATEGY_CLASS).o $(COLONYMANAGER_CLASS).o $(STATISTICS_CLASS).o $(STATUS_CLASS).o
	@cd $(AI_DIR) && $(MAKE)
	@cd ../
	@cd $(BODY_DIR) && $(MAKE)
	@cd ../

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(CCOPTS)
