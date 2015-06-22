#frandauto -- Fast Random Automata

##Current Status:
v0.3.1 -- Alpha.
Build passing.

##License:
Unlicensed, free to use and distribute.
Copyright (c) Isabell Cowan 2015.

##Provides:
* frandauto
  * Executable generating random sequences
  * Full command line user interface
  * Depends on libfrandauto
* libfrandauto
  * C library for the generation of random numbers and sequences

##Contains:
* doc -- Documentation dir
  * CHANGELOG.md -- History of minor version changes to this project
  * README.md -- This document
* src -- Source code dir
  * include -- Header for libfrandauto dir
    * globals.h -- global variables for main.c options.c communication
    * options.h -- options.c header
  * lib -- libfrandauto dir
    * auto.c -- Interface for high entropy automata
    * frandauto.c -- Converts automata states to useful numbers and sequences
  * lib/include -- libfrandauto headers dir
    * auto.h -- headers for auto.c
    * frandauto.h -- header for linking in (lib)frandauto.(s)o
    * globals.h -- header for shared macros and types
  * options.c -- Command line option parsing
  * main.c -- Contains main for frandauto executeable
* Makefile -- Makefile to build frandauto and libfrandauto locally
* README.md -- symbolic link to doc/README.md

<!-- vim : set ts=2 sw=2 et syn=markdown : -->
