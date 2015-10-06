###
#
# For more information about makefiles, check here:
#     http://www.gnu.org/software/make/manual/make.html
#
# Original makefile by Shane Culpepper, modified by Jeffrey Chan, 2015 
###

# The name of the applications we're trying to generate.  Do not change these.
TARGET_AL_AL = bpGraphAL_AL
TARGET_MATCH = match
TARGET_AL_BL = bpGraphAL_BL
TARGET_AM = bpGraphAdjMat

SRC_AL_AL = main.c memoryUtil.c linkedList.c bpGraphAdjList_AL.c
SRC_AL_MATCH = main.c memoryUtil.c linkedList.c match.c
SRC_AL_BL = main.c memoryUtil.c linkedList.c binaryTree.c bpGraphAdjList_BL.c
#SRC_AL_BT = testMain.c memoryUtil.c linkedList.c binaryTree.c bpGraphAdjList_BT.c
SRC_AM = main.c memoryUtil.c linkedList.c bpGraphAdjMat_AA.c
HDR = memoryUtil.h linkedList.h binaryTree.h bipartiteGraph.h commonDefs.h 

OBJ_AL_AL := $(SRC_AL_AL:.c=.o)
OBJ_MATCH := $(SRC_MATCH:.c=.o)
OBJ_AL_BL := $(SRC_AL_BL:.c=.o)
OBJ_AM := $(SRC_AM:.c=.o)


# These variables are used by make in all of it's automatic rules.
# Specifically, use CFLAGS for the "-g -O0" option if you want to do debugging,
# and LDFLAGS for the "-lm" option if you are using the math library.
CC = gcc
#CFLAGS = -W -Wall -ansi -O3
#CFLAGS = -Wall -ansi -pedantic -g -O0 
# c99 standard
CFLAGS = -Wall -std=c99 -pedantic -g -O0 
# maths library
LDFLAGS = -lm

all : $(TARGET_MATCH) 

$(TARGET_AL_AL) : $(OBJ_AL_AL)
	$(CC) $(LDFLAGS) -o $@ $(OBJ_AL_AL)
	
$(TARGET_MATCH) : $(OBJ_MATCH)
	$(CC) $(LDFLAGS) -o $@ $(OBJ_MATCH)	
	
$(TARGET_AL_BL) : $(OBJ_AL_BL)
	$(CC) $(LDFLAGS) -o $@ $(OBJ_AL_BL)		

$(TARGET_AM) : $(OBJ_AM)
	$(CC) $(LDFLAGS) -o $@ $(OBJ_AM)





# This generates the dependencies between your various .c and .h files, using
# the c compiler's -MM option.
depend : $(SRC_AL_AL) $(SRC_MATCH) $(SRC_AM) $(SRC_EL) $(HDR)
	$(CC) $(CFLAGS) -MM $(SRC_AL_AL) > depend
	$(CC) $(CFLAGS) -MM $(SRC_MATCH) > depend
	$(CC) $(CFLAGS) -MM $(SRC_AL_BL) > depend
	$(CC) $(CFLAGS) -MM $(SRC_AM) > depend


# This includes the dependencies made with the previous rule, and in fact forces
# them to be generated.
-include depend

# The rules below clean up any files generated by the make process.  clean
# should be run to clear out the temporary files, and clobber should be run if
# you modify your makefile (for example to change the CFLAGS or LDFLAGS options)
# so that you can get a clean recompile.
.PHONY : clean

clean :
	-rm -f depend
	-rm -f $(TARGET_AL_AL) $(TARGET_MATCH) $(TARGET_AL_BL) $(TARGET_AM) $(OBJ_AL_AL) $(OBJ_MATCH) $(OBJ_AL_BL) $(OBJ_AM) 
	-rm -f *~ 
