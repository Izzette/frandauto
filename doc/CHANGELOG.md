# Changelog
This document includes all major and minor version changes to the project.  This mirrors the git log, but excludes the patch messages.  For information about patches see the git log.

##v0 -- Alpha
###v0.0 -- Initial Commit
* Created skeleton of project
* Wrote the packages and directory structure to README
* Makefile builds currently vacant local frandauto and libfrandauto
###v0.1 -- Started auto.c
* Created auto.c and auto.h
* Added auto\_init to auto
* Updated Makefile
* Updated README
###v0.2 -- Continued auto.c
* Changed naming conventions, fra-prefixed  
* Updated directory structure
* Minor updates to skelaton
* auto\_init renamed fra\_init
* Added fra\_seed
* Updated Makefile
* Updated README
###v0.3 -- Continued auto.c
* Added the series fra\_is\_init, fra\_size, fra\_is\_seed
###v0.4 -- Finished auto.c
* Added fra\_free, fra\_step, and fra\_get\_states
* Cleaned up unneeded headers in src/lib/include
* Divided src/lib/frandauto.c into src/lib/conv.c and src/lib/next.c
* Updated Makefile

<!-- vim : set ts=2 sw=2 et syn=markdown : -->
