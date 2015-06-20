#!/usr/bin/make -f

### START DIRS ###

##  START LOCAL DIRS ##

SRC_DIR = ./src/
LIB_DIR = $(SRC_DIR)lib/
INC_DIR = $(SRC_DIR)include/
BUILD_DIR = ./build/

##  END LOCAL DIRS   ##

##  START INSTALL DIRS ##

#I_LIB_DIR = /usr/lib/
#I_INC_DIR = /usr/include/
#I_BIN_DIR = /usr/bin/

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
#-- NOT IMPLEMENTED! --#

#DFLAGS = -ggdb -Wextra -o
#DOFLAGS = $(OFLAGS) $(DFLAGS)
#DEFLAGS = $(BUILD_DIR)frandauto.o $(EFLAGS) $(DFLAGS)

#   END DEBUG FLAGS   #

#   START INSTALL FLAGS #
#-- NOT IMPLEMENTED! --#

#IFLAGS = -Ofast -Wall -o
#IEFLAGS = -lfrandauto $(EFLAGS) $(IFLAGS)

#   END INSTALL FLAGS   #

##  END FLAGS   ##

CC = gcc

### END COMPILATION   ###

### START TARGETS ###

all: dirs local

##  START LOCAL TARGETS ##

local: dirs local-e-frandauto

dirs:
	$(MKDIR) $(DIRS)

local-e-frandauto: dirs local-so-libfrandauto
	$(CC) $(SRC_DIR)main.c $(INC_DIR)frandauto.h $(BUILD_DIR)frandauto.o $(LEFLAGS) $(BUILD_DIR)frandauto

local-so-libfrandauto: dirs local-o-frandauto
	$(CC) $(BUILD_DIR)frandauto.o $(BUILD_DIR)auto.o $(LSOFLAGS) $(BUILD_DIR)libfrandauto.so

local-o-frandauto: dirs local-o-auto
	$(CC) $(LIB_DIR)frandauto.c $(LOFLAGS) $(BUILD_DIR)frandauto.o

local-o-auto: dirs
	$(CC) $(LIB_DIR)auto.c $(LOFLAGS) $(BUILD_DIR)auto.o

##  END LOCAL TARGETS   ##

##  START DEBUG TARGETS ##
#-- NOT IMPLEMENTED! --#
##  END DEBUG TARGETS   ##

##  START INSTALL TARGETS ##
#-- NOT IMPLEMENTED! --#
##  END INSTALL TARGETS   ##

### END TARGETS   ###

# vim : set ts=4 sw=4 noet syn=make :
