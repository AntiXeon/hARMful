ROOT_DIR = ../..

# Folders where make must be launched too
EQUIPMENT_DIR = equipment
LIMB_DIR = limb
PHYSIQUE_DIR = physique

# Classes to compile in the current folder
BODY_CLASS = Body

all : $(BODY_CLASS).o
	@cd $(EQUIPMENT_DIR) && $(MAKE)
	@cd ../
	@cd $(LIMB_DIR) && $(MAKE)
	@cd ../
	@cd $(PHYSIQUE_DIR) && $(MAKE)
	@cd ../

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(CCOPTS)
