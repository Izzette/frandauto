#frandauto

##Provides:
* frandauto
  * Executable generating random sequences and numbers
  * Full command line user interface
  * Depends on libfrandauto
* libfrandauto
  * C library for the generation of random sequences and numbers

##Contains:
* Makefile -- Makefile to build <!-- NI: and install --> frandauto and libfrandauto
* src -- Source code dir
  * main.c -- Source code for frandauto executeable
  * globals.c -- Source code for frandauto global variables
  * options.c -- Source code for parsing options to change frandauto global variables
  * lib -- libfrandauto dir
    * frandauto.c -- libfrandauto root
    * auto.c -- Internal high entropy cellular automata
  * include -- Header for libfrandauto dir
    * frandauto.h -- libfrandauto header
    * auto.h -- auto.c header
* doc -- Documentation dir
  * README.md -- This document
  * CHANGELOG.md -- History of minor version changes to frandautod
  * LIB-CHANGELOG.md -- History of minor version changes to libfrandauto
  <!-- NI: man pages for frandauto and frandauto.h -->

<!-- vim : set ts=2 sw=2 et syn=markdown : -->
