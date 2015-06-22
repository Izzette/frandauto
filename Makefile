#!/usr/bin/make -f

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
#-- NOT IMPLEMENTED! --#
#   END DEBUG FLAGS   #

#   START INSTALL FLAGS #
#-- NOT IMPLEMENTED! --#
#   END INSTALL FLAGS   #

##  END FLAGS   ##

##  START COMPILERS ##

CC = gcc

##  END COMPILERS   ##

### END COMPILATION   ###

### START TARGETS ###

##  START PRIMARY TARGETS ##

all: dirs local

dirs:
	$(MKDIR) $(DIRS)

local: dirs local-e-frandauto local-so-libfrandauto

##  END PRIMARY TARGETS   ##

##  START LOCAL TARGETS ##

local-e-frandauto: dirs local-o-main local-o-options local-o-frandauto
	$(CC) $(BUILD_DIR)*.o $(INC_DIR)*.h $(LI_DIR)*.h $(LEFLAGS) $(BUILD_DIR)frandauto

local-o-main: dirs
	$(CC) $(SRC_DIR)main.c $(LOFLAGS) $(BUILD_DIR)main.o

local-o-options: dirs
	$(CC) $(SRC_DIR)options.c $(LOFLAGS) $(BUILD_DIR)options.o

local-o-frandauto: dirs
	$(CC) $(LIB_DIR)frandauto.c $(LOFLAGS) $(BUILD_DIR)frandauto.o

local-o-auto: dirs
	$(CC) $(LIB_DIR)auto.c $(LOFLAGS) $(BUILD_DIR)auto.o

local-so-libfrandauto: dirs local-o-frandauto local-o-auto
	$(CC) $(BUILD_DIR)frandauto.o $(BUILD_DIR)auto.o $(LSOFLAGS) $(BUILD_DIR)libfrandauto.so

##  END LOCAL TARGETS   ##

##  START DEBUG TARGETS ##
#-- NOT IMPLEMENTED! --#
##  END DEBUG TARGETS   ##

##  START INSTALL TARGETS ##
#-- NOT IMPLEMENTED! --#
##  END INSTALL TARGETS   ##

### END TARGETS   ###

# vim : set ts=4 sw=4 noet syn=make :
