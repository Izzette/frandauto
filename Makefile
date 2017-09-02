# Makefile

### START DIRS ###

##  START LOCAL DIRS ##

SRC_DIR = ./src/
INC_DIR = $(SRC_DIR)include/
LIB_DIR = $(SRC_DIR)lib/
LI_DIR = $(LIB_DIR)include/
BUILD_DIR = ./build/

##  END LOCAL DIRS   ##

##  START INSTALL DIRS ##
#-- NOT IMPLEMENTED! --#
##  END INSTALL DIRS   ##

MKDIR = mkdir -p
DIRS = $(SRC_DIR) $(LIB_DIR) $(INC_DIR) $(BUILD_DIR) 

### END DIRS   ###

### START COMPILATION ###

##  START FLAGS ##

OFLAGS = -c -fpic
SOFLAGS = -shared

#   START LOCAL FLAGS #

LFLAGS = -Ofast -Wall -o
LOFLAGS = $(OFLAGS) $(LFLAGS)
LSOFLAGS = $(SOFLAGS) $(LFLAGS)
LEFLAGS = $(LFLAGS)

#   END LOCAL FLAGS   #

#   START DEBUG FLAGS #

DFLAGS = -ggdb -Wextra -o
DOFLAGS = $(OFLAGS) $(DFLAGS)
DSOFLAGS = $(SOFLAGS) $(DFLAGS)
DEFLAGS = $(DFLAGS)

#   END DEBUG FLAGS   #

#   START INSTALL FLAGS #
#-- NOT IMPLEMENTED! --#
#   END INSTALL FLAGS   #

##  END FLAGS   ##

##  START COMPILERS ##

CC = gcc

##  END COMPILERS   ##

##  START ARCHIVERS ##

AR = ar

##  END ARCHIVERS   ##

### END COMPILATION   ###

### START TARGETS ###

##  START PRIMARY TARGETS ##

all: dirs local

dirs:
	$(MKDIR) $(DIRS)

local: dirs local-e-frandauto local-so-libfrandauto local-a-libfrandauto

debug: dirs debug-e-frandauto debug-so-libfrandauto

##  END PRIMARY TARGETS   ##

##  START LOCAL TARGETS ##

local-e-frandauto: dirs local-o-main local-o-options local-o-next local-o-conv local-o-auto
	$(CC) $(BUILD_DIR)*.o $(INC_DIR)*.h $(LI_DIR)*.h $(LEFLAGS) $(BUILD_DIR)frandauto

local-o-main: dirs
	$(CC) $(SRC_DIR)main.c $(LOFLAGS) $(BUILD_DIR)main.o

local-o-options: dirs
	$(CC) $(SRC_DIR)options.c $(LOFLAGS) $(BUILD_DIR)options.o

local-o-next: dirs
	$(CC) $(LIB_DIR)next.c $(LOFLAGS) $(BUILD_DIR)next.o

local-o-conv: dirs
	$(CC) $(LIB_DIR)conv.c  $(LOFLAGS) $(BUILD_DIR)conv.o

local-o-auto: dirs
	$(CC) $(LIB_DIR)auto.c $(LOFLAGS) $(BUILD_DIR)auto.o

local-so-libfrandauto: dirs local-o-next local-o-conv local-o-auto
	$(CC) $(BUILD_DIR)next.o $(BUILD_DIR)conv.o $(BUILD_DIR)auto.o $(LSOFLAGS) $(BUILD_DIR)libfrandauto.so

local-a-libfrandauto: dirs local-o-next local-o-conv local-o-auto
	$(AR) rcs $(BUILD_DIR)libfrandauto.a $(BUILD_DIR)next.o $(BUILD_DIR)conv.o $(BUILD_DIR)auto.o

##  END LOCAL TARGETS   ##

##  START DEBUG TARGETS ##

debug-e-frandauto: dirs debug-o-main debug-o-options debug-o-next debug-o-conv debug-o-auto
	$(CC) $(BUILD_DIR)*.o $(INC_DIR)*.h $(LI_DIR)*.h $(DEFLAGS) $(BUILD_DIR)frandauto

debug-o-main: dirs
	$(CC) $(SRC_DIR)main.c $(DOFLAGS) $(BUILD_DIR)main.o

debug-o-options: dirs
	$(CC) $(SRC_DIR)options.c $(DOFLAGS) $(BUILD_DIR)options.o

debug-o-next: dirs
	$(CC) $(LIB_DIR)next.c $(DOFLAGS) $(BUILD_DIR)next.o

debug-o-conv: dirs
	$(CC) $(LIB_DIR)conv.c  $(DOFLAGS) $(BUILD_DIR)conv.o

debug-o-auto: dirs
	$(CC) $(LIB_DIR)auto.c $(DOFLAGS) $(BUILD_DIR)auto.o

debug-so-libfrandauto: dirs debug-o-next debug-o-conv debug-o-auto
	$(CC) $(BUILD_DIR)next.o $(BUILD_DIR)conv.o $(BUILD_DIR)auto.o $(DSOFLAGS) $(BUILD_DIR)libfrandauto.so

##  END DEBUG TARGETS   ##

##  START INSTALL TARGETS ##
#-- NOT IMPLEMENTED! --#
##  END INSTALL TARGETS   ##

### END TARGETS   ###

# vim : set ts=4 sw=4 noet syn=make :
