####################################################
# Stacked Images with iNterations (2D Game Engine) #
####################################################
# SINful Makefile                                  #
# Author: Denis CARLUS                             #
# Version 1, 2015/02/07                            #
####################################################

CC          = g++
CCOPTS      =
OBJ_OPTS	= -g3
# Specific options to library types
STATIC_OPTS = -W -Wall -Werror -Wfatal-errors -ffast-math -rdynamic
SHARED_OPTS = $(STATIC_OPTS)


# Source and compiled objects
SOURCES_DIR = src
SOURCES     = $(shell find ./$(SOURCES_DIR) -name "*.cpp" -print)
OBJECTS     = $(SOURCES:.cpp=.o)

# Required external tools
ARCH        = $(shell uname -m)
BINARY      = lib/$(ARCH)
STATIC      = $(BINARY)/static
SIN_ROOT	= ../..
LIBS_ROOT 	= ../$(SIN_ROOT)
COMMON_SIN	= $(SIN_ROOT)/common
INCLUDE     = -I./include -I$(COMMON_SIN)/include								\
			  -I$(LIBS_ROOT)/DOOMful/include									\
			  -I$(LIBS_ROOT)/MINDful/include									\
			  -I$(LIBS_ROOT)/SPITEful/include
LIBRARY     = -L $(COMMON_SIN)/lib/$(ARCH) -lSIN								\
			  -L$(LIBS_ROOT)/DOOMful/lib/$(ARCH) -lDOOM							\
			  -L$(LIBS_ROOT)/MINDful/lib/$(ARCH) -lMIND							\
			  -L$(LIBS_ROOT)/SPITEful/lib/$(ARCH) -lSPITE
OUTPUT      = SIN_SDL2
LIB_VERSION = 1.0

# Extensions
SHARED_UNIX	= .so
SHARED_WIN	= .dll
SHARED_EXT	= $(SHARED_UNIX)
SHARED_RULE = SharedUnix

STATIC_UNIX	= .a
STATIC_WIN	= .dll.a
STATIC_EXT	= $(STATIC_UNIX)


# Rules
%.o: %.c
	@echo "Compiling" $(notdir $@)
	@$(CC) $(CCOPTS) $(OBJ_OPTS) $(INCLUDE) -c $< -o $@

%.o: %.cpp
	@echo "Compiling" $(notdir $@)
	@$(CC) $(CCOPTS) $(OBJ_OPTS) $(INCLUDE) -c $< -o $@

all: prerequisite linux

prerequisite:
	@cd $(COMMON_SIN) && make

clean:
	@rm -r $(BINARY)
	@rm -f $(OBJECTS)


# Static library compilation
SetStaticOptions:
	@$(eval CCOPTS := $(STATIC_OPTS))
	@mkdir -p $(STATIC)

Static: SetStaticOptions $(OBJECTS)
	@ar rcs $(STATIC)/$(PREFX_STATIC)$(STATIC_EXT) $(OBJECTS)


# Shared library compilation
SetSharedOptions:
	@$(eval CCOPTS := $(SHARED_OPTS))
	@mkdir -p $(BINARY)

SharedUnix: SetSharedOptions $(OBJECTS)
	@$(CC) -shared -Wl,-soname,$(BINARY)/$(PREFX_SHARED)$(SHARED_EXT) 						\
			   -o $(BINARY)/$(PREFX_SHARED)$(SHARED_EXT).$(LIB_VERSION)							  \
			   $(OBJECTS) $(LIBRARY)
	@cd ./$(BINARY) && ln -sf $(PREFX_SHARED)$(SHARED_EXT).$(LIB_VERSION)			 	  \
			$(PREFX_SHARED)$(SHARED_EXT)

SharedWindows: SetSharedOptions $(OBJECTS)
	@$(CC) -shared -o $(BINARY)/$(PREFX_SHARED)$(SHARED_EXT) $(OBJECTS) $(LIBRARY)\
				 -Wl,--out-implib=$(BINARY)/$(PREFX_STATIC)$(STATIC_EXT)								\
				 -Wl,--export-all-symbols																								\
				 -Wl,--enable-auto-import																								\
				 -Wl,--no-whole-archive


# OS specific build rules
linux: ParameterLinux SharedUnix Static

ParameterLinux:
	@$(eval PREFX_SHARED = lib$(OUTPUT))
	@$(eval PREFX_STATIC = lib$(OUTPUT))
	@$(eval SHARED_OPTS := $(SHARED_OPTS) -fPIC)
	@$(eval SHARED_EXT := $(SHARED_UNIX))
	@$(eval STATIC_EXT := $(STATIC_UNIX))

cygwin: ParameterWindows SharedWindows Static

ParameterWindows:
	@$(eval PREFX_SHARED = cyg$(OUTPUT))
	@$(eval PREFX_STATIC = lib$(OUTPUT))
	@$(eval SHARED_EXT := $(SHARED_WIN))
	@$(eval STATIC_EXT := $(STATIC_WIN))
