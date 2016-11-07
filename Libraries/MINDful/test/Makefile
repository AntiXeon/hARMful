##########################################################
# Mathematics Interface to New Developments - Test Tools #
##########################################################
# MINDful Makefile                                       #
# Author: Denis CARLUS                                   #
# Version 1, 2014/02/11                                  #
##########################################################

CC          = g++
CCOPTS      = -ffast-math -Wl,-rpath,lib -pthread


# Source and compiled objects
SOURCES_DIR = .
FAST_MATH   = fast_math
MATH        = math
MATRIX2D    = matrix2d
POINT2D     = point2d
POINT3D     = point3d
DIM2D       = dimension2d
DIM3D       = dimension3d
LINE2D      = line2d
RECTANGLE2D = rectangle2d
MATRIX3X3	= matrix3x3
MATRIX4X4	= matrix4x4
SIMD_INTEL	= simd_intel
SIMD_EMUL	= simd_emulated

# Required external tools
ARCH        = $(shell uname -m)
BINARY      = ../bin/$(ARCH)
DOOMful		= ../../DOOMful
INCLUDE     = -I../include -I$(DOOMful)/include
LIB_DIR     = ../lib
LIBRARY     = -L$(DOOMful)/lib/$(ARCH) -lDOOM -L$(LIB_DIR)/$(ARCH) -lMIND



# Rules
%.o: %.cpp
	@echo -e "Compiling" $(notdir $@)
	@$(CC) $(CCOPTS) $(INCLUDE) -c $< -o $@

all: MakeDir $(FAST_MATH) $(MATH) $(MATRIX2D) $(POINT2D) $(POINT3D) $(DIM2D)    \
	 $(DIM3D) $(LINE2D) $(RECTANGLE2D) $(MATRIX3X3) $(MATRIX4X4) $(SIMD_INTEL)	\
	 $(SIMD_EMUL)

MakeDir:
	@mkdir -p $(BINARY)
	@cd $(BINARY) && ln -sf ../$(LIB_DIR)


$(FAST_MATH): $(FAST_MATH).o
	$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $@.o $(LIBRARY)

$(MATH): $(MATH).o
	$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $@.o $(LIBRARY)

$(MATRIX2D): $(MATRIX2D).o
	$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $@.o $(LIBRARY)

$(POINT2D): $(POINT2D).o
	$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $@.o $(LIBRARY)

$(POINT3D): $(POINT3D).o
	$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $@.o $(LIBRARY)

$(DIM2D): $(DIM2D).o
	$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $@.o $(LIBRARY)

$(DIM3D): $(DIM3D).o
	$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $@.o $(LIBRARY)

$(LINE2D): $(LINE2D).o
	$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $@.o $(LIBRARY)

$(RECTANGLE2D): $(RECTANGLE2D).o
	$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $@.o $(LIBRARY)

$(MATRIX3X3): $(MATRIX3X3).o
	$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $@.o $(LIBRARY)

$(MATRIX4X4): $(MATRIX4X4).o
	$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $@.o $(LIBRARY)

$(SIMD_INTEL): $(SIMD_INTEL).o
	$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $@.o $(LIBRARY)

$(SIMD_EMUL): $(SIMD_EMUL).o
	$(CC) $(CCOPTS) -o $(BINARY)/$@.test $(INCLUDE) $@.o $(LIBRARY)


clean:
	@rm -f $(BINARY)/*.test
	@rm -f $(SOURCES_DIR)/*.o

shared: Shared
