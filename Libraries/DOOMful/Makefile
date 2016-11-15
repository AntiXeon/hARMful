########################################
# Debugging and Oriented-Object Modules
########################################
# @Author: Denis CARLUS <dcarlus>
# @Date:   01-Nov-2016
# @Filename: Makefile
# @Last modified by:   Denis CARLUS
# @Last modified time: 14-Nov-2016
# @License: GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007

CC          = g++
CCOPTS      = -std=c++1y
OBJ_OPTS    = -g3
# Specific options to library types
STATIC_OPTS = $(CCOPTS) -W -Wall -Werror -Wfatal-errors -ffast-math -rdynamic
SHARED_OPTS = $(STATIC_OPTS)


# Source and compiled objects
SOURCES_DIR = src
SOURCES     = $(shell find ./$(SOURCES_DIR) -name "*.c" -print)                 \
              $(shell find ./$(SOURCES_DIR) -name "*.cpp" -print)
TMP_OBJECTS = $(SOURCES:.c=.o)
OBJECTS     = $(TMP_OBJECTS:.cpp=.o)
I18N_DIR	= i18n

# Required external tools
ARCH        = $(shell uname -m)
LIB_DIR     = lib
BINARY      = $(LIB_DIR)/$(ARCH)
STATIC      = $(BINARY)/static
INCLUDE     = -I$(realpath ./include)
LIBRARY     =
OUTPUT      = DOOM
SHARED_NAME = lib$(OUTPUT)
STATIC_NAME = lib$(OUTPUT)
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

all: linux

translation:
	@xgettext -d $(OUTPUT) -o $(I18N_DIR)/$(OUTPUT).pot -ki18n --add-comments -s src/$(OUTPUT)Strings.cpp

clean:
	@rm -r $(BINARY)
	@rm -r $(LIB_DIR)
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
	@$(CC) -shared -Wl,-soname,$(BINARY)/$(PREFX_SHARED)$(SHARED_EXT) 			\
				 -o $(BINARY)/$(PREFX_SHARED)$(SHARED_EXT).$(LIB_VERSION)		\
				 $(OBJECTS) $(LIBRARY)
	@cd ./$(BINARY) && ln -sf $(PREFX_SHARED)$(SHARED_EXT).$(LIB_VERSION)		\
				 $(PREFX_SHARED)$(SHARED_EXT)

SharedWindows: SetSharedOptions $(OBJECTS)
	@$(CC) -shared -o $(BINARY)/$(PREFX_SHARED)$(SHARED_EXT) $(OBJECTS) $(LIBRARY)\
				-Wl,--out-implib=$(BINARY)/$(PREFX_STATIC)$(STATIC_EXT)			\
				-Wl,--export-all-symbols										\
				-Wl,--enable-auto-import										\
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
