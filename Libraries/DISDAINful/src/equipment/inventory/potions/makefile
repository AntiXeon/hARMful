ROOT_DIR = ../../..

POTION_CLASS = Potion
LIFEPOTION_CLASS = LifePotion

all : $(POTION_CLASS).o $(LIFEPOTION_CLASS).o

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(CCOPTS)
