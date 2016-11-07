#########################################
# HARMFUL unit tests Makefile           #
#########################################
# DOLEful Makefile                      #
# Author: Denis CARLUS                  #
# Version 1, 2015/10/12                 #
#########################################

# Tested libraries :
LIB_DOOM    = DOOMful
LIB_GUILE   = GUILEful
LIB_MIND    = MINDful


CC          = g++
CCOPTS      = -W -Wall -g3 -ffast-math -pthread
MAKE_THREAD = 64

# Source and compiled objects
HARMFUL_DIR = ../Libraries
SOURCES_DIR = src
SOURCES     = $(shell find ./$(SOURCES_DIR) -name "*.c" -print)                 \
              $(shell find ./$(SOURCES_DIR) -name "*.cpp" -print)
TMP_OBJECTS = $(SOURCES:.c=.o)
OBJECTS     = $(TMP_OBJECTS:.cpp=.o)
EXE_EXT     = test.exe
BINARIES    = $(OBJECTS:.o=.test.exe)

# Required external tools
ARCH        = $(shell uname -m)
BINARY_DIR  = bin
INCLUDE_DIR = include
INCLUDE     = -I$(INCLUDE_DIR)                                                  \
              -I$(INCLUDE_DIR)/$(LIB_DOOM) -I$(INCLUDE_DIR)/$(LIB_GUILE)        \
              -I$(INCLUDE_DIR)/$(LIB_MIND)
LIB_DIR     = lib
LIBRARY     = -lSDL2 -L$(LIB_DIR)/$(ARCH) -lDOOM -lGUILE -lMIND

# List of the
HARMFUL_LIBS = $(LIB_DOOM) $(LIB_MIND) $(LIB_GUILE)
CLEAN_HARMFUL_LIBS = $(HARMFUL_LIBS:ful=ful.Clean)



################################################################################
##################################### RULES ####################################
################################################################################

# BUILDING RULES
# Compilation of source files to object files
%.o: %.cpp
	@$(CC) $(CCOPTS) $(INCLUDE) $(LIBRARY) -c $< -o $@

# Compilation of object files to executable files
%.test.exe: %.o
#	@echo "Compiling" $@
	@$(CC) $(CCOPTS) $^ -o $(BINARY_DIR)/$(notdir $@) $(INCLUDE) $(LIBRARY)

# Entry point of the Makefile
all: CreateDirs $(HARMFUL_LIBS) $(OBJECTS) $(BINARIES)
	@./RunTests.sh

# Create directories for tests
CreateDirs:
	@mkdir -p $(BINARY_DIR)
	@cd $(BINARY_DIR) && ln -sf ../$(LIB_DIR)

# Compile a library to test
%ful:
	@mkdir -p $(INCLUDE_DIR)/$@
	@echo "+------ Compile library " $@ " ------+"
	@cd $(HARMFUL_DIR)/$@ && $(MAKE) -j$(MAKE_THREAD)
	@cp -r $(HARMFUL_DIR)/$@/lib/* ./lib/
	@cp -r $(HARMFUL_DIR)/$@/include/* ./include/$@/
	@echo "+--- " $@ " successfully compiled ---+"
	@printf "\n"


# CLEANING RULES
# Restore to proper folders, remove built files
clean: $(CLEAN_HARMFUL_LIBS)
	@rm -f $(BINARY_DIR)/*.$(EXE_EXT)
	@rm -f $(BINARY_DIR)/$(LIB_DIR)
	@rm -rf $(LIB_DIR)/$(ARCH)
	@rm -rf $(INCLUDE_DIR)/*ful
	@rm -f $(OBJECTS)

%ful.Clean:
	@cd $(HARMFUL_DIR)/$(basename $@) && $(MAKE) clean
