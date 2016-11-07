ROOT_DIR = ../..

FIREARM_DIR = firearm

#SWORD_CLASS = Sword
WEAPON_CLASS = Weapon
WEAPONSTATUS_CLASS = WeaponStatus
DEFAULTWEAPONSTATUS_CLASS = DefaultWeaponStatus

#$(SWORD_CLASS).o
all : $(WEAPON_CLASS).o $(WEAPONSTATUS_CLASS).o \
      $(DEFAULTWEAPONSTATUS_CLASS).o
	@cd $(FIREARM_DIR) && $(MAKE)
	@cd ../

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(CCOPTS)
