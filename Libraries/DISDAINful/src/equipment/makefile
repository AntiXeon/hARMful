SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

ROOT_DIR = ..

ARMORS_DIR = armors
INVENTORY_DIR = inventory
WEAPONS_DIR = weapons

ITEM_CLASS = Item
ITEMSTATUS_CLASS = ItemStatus

all : $(ITEM_CLASS).o $(ITEMSTATUS_CLASS).o
	@cd $(ARMORS_DIR) && $(MAKE)
	@cd ../
	@cd $(WEAPONS_DIR) && $(MAKE)
	@cd ../
	@cd $(INVENTORY_DIR) && $(MAKE)
	@cd ../

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(CCOPTS)
