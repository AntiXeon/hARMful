ROOT_DIR = ..

# Folders where make must be launched too
TOOLS_DIR = tools

# Classes to compile in the current folder
LOGGEN_CLASS = LogGen
TIMER_CLASS = Timer
GAUGETIMER_CLASS = GaugeTimer

COMPILE = $(TIMER_CLASS).o
COMPILE += $(GAUGETIMER_CLASS).o

ifdef DEBUG_MODE
COMPILE += $(LOGGEN_CLASS).o
endif

all : $(COMPILE)
	@cd $(TOOLS_DIR) && $(MAKE)
	@cd ../

%.o: %.cpp
	@echo "Compiling" $@
	@$(CC) -o $(ROOT_DIR)/$(OBJ_DIR)/$@ -I$(ROOT_DIR)/$(INCLUDE_ROOT) -I$(ROOT_DIR)/$(INCLUDE_HARMFUL) -c $< $(CCOPTS)
