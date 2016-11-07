ROOT_DIR = ../..

ITEMS_DIR = potions

INVENTORY_CLASS = Inventory
AMMOSTOCK_CLASS = AmmoStock

all : $(INVENTORY_CLASS).o $(AMMOSTOCK_CLASS).o
	@cd $(ITEMS_DIR) && $(MAKE)
	@cd ../

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(CCOPTS)
