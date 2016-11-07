ROOT_DIR = ../../..

LIMB_CLASS = Limb
LIMBHEAD_CLASS = LimbHead
LIMBTRUNK_CLASS = LimbTrunk

all : $(LIMB_CLASS).o $(LIMBHEAD_CLASS).o $(LIMBTRUNK_CLASS).o

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(CCOPTS)
