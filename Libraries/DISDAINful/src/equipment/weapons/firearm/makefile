ROOT_DIR = ../../..

FIREARM_CLASS = Firearm
FIREARMSTATUS_CLASS = FirearmStatus

all : $(FIREARM_CLASS).o $(FIREARMSTATUS_CLASS).o

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(CCOPTS)
