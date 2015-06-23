#frandauto -- Fast Random Automata

##Current Status:
v0.4.1 -- Alpha.
Build passing.

##License:
Unlicensed, free to use and distribute.
Copyright (c) Isabell Cowan 2015.

##Provides:
###frandauto
* Executable generating random sequences
* Full command line user interface
* Depends on libfrandauto

###libfrandauto
* C library for the generation of random numbers and sequences

##Contains:
###Project root
* Makefile -- Builds frandauto and libfrandauto
* README.md -- Symbolic link to doc/README.md

###doc -- Documentation directory
* CHANGELOG.md -- Log of minor version changes
* README.md -- This document

###src -- Source code directory
* options.c -- Parsing command line options frandauto
* main.c -- Contains entry point for frandauto

###src/include -- Headers for frandauto
* globals.h -- Globals for communication between options.c and main.c
* options.h -- Header for options.c

###src/lib -- Source code for libfrandauto
* auto.c -- Cellular automata generation
* conv.c -- Converts array of cellular automata states to various useful forms
* next.c -- Provides functions for simultaneous manipulation of auto.c and conv.c, ie `fra_next_<..>`

###src/lib/include -- Header(s) for libfrandauto
* frandauto.h -- Api for libfrandauto

<!-- vim : set ts=2 sw=2 et syn=markdown : -->
