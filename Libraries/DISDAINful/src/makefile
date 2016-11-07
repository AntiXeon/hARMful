# -fsigned-char required because char type is unsigned by default in ARM C/C++
export CC = g++
export CCOPTS = -W -Wall -std=c++0x -fsigned-char

# Activate debug or release mode
# Compile with make DEBUG_MODE=1 to generate a release version of the software
ECHO_DEBUG = "Compiling in"
ifndef NDEBUG
CCOPTS += -g -DDEBUG_MODE -fexpensive-optimizations -O3
ECHO_DEBUG += "DEBUG"
export DEBUG_MODE = 1
else
CCOPTS += -fexpensive-optimizations -O3
ECHO_DEBUG += "RELEASE"
endif
ECHO_DEBUG += "mode..."

# Name of the project
ENGINE_NAME = hARMfulEngine

# List of variables used to compile
PARENT_DIR = ../..
export OBJ_DIR = $(PARENT_DIR)/build/obj/$(ENGINE_NAME)

# Library
LIB_NAME = lib$(ENGINE_NAME).a
LIB_DIR = $(PARENT_DIR)/lib

# Includes
export INCLUDE_ROOT = $(PARENT_DIR)/include/$(ENGINE_NAME)
export INCLUDE_HARMFUL = $(INCLUDE_ROOT)/harmful/


# Classes to compile in the current folder
HARMFUL_CLASS = hARMful
ALLPOTIONS_CLASS = AllPotions
ALLMAGIC_CLASS = AllMagic
ALLWEAPONS_CLASS = AllWeapons

# Subfolders containing classes
CHARACTERS_DIR = characters
MAGIC_DIR = magic
THINGS_EQUIPMENT_DIR = equipment
PATTERN_DIR = pattern
UTILS_DIR = utils

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

# Compilation rules
all: infoCompilation EngineOBJ
	$(AR) rs $(LIB_DIR)/$(LIB_NAME) $(OBJ_DIR)/*.o

EngineOBJ: $(OBJ)
	@cd $(CHARACTERS_DIR) && $(MAKE)
	@cd ../
	@cd $(THINGS_EQUIPMENT_DIR) && $(MAKE)
	@cd ../
	@cd $(MAGIC_DIR) && $(MAKE)
	@cd ../
	@cd $(PATTERN_DIR) && $(MAKE)
	@cd ../
	@cd $(UTILS_DIR) && $(MAKE)
	@cd ../

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(OBJ_DIR)/$@ -I$(INCLUDE_ROOT) -I$(INCLUDE_HARMFUL) -c $< $(CCOPTS)

infoCompilation:
	@echo $(ECHO_DEBUG)

.PHONY: clean
clean:
	@rm -f $(OBJ_DIR)/*.o $(LIB_DIR)/$(LIB_NAME) 
