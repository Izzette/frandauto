# Changelog
This document includes all major and minor version changes to the project.  This mirrors the git log, but excludes the patch messages.  For information about patches see the git log.

##v0 -- Alpha
###v0.0 -- Initial Commit
* Created skeleton of project
* Wrote the packages and directory structure to README
* Makefile builds currently vacant local frandauto and libfrandauto

###v0.1 -- Started auto.c
* Created auto.c and auto.h
* Added `auto_init` to auto.c
* Updated Makefile
* Updated README

###v0.2 -- Continued auto.c
* Changed naming conventions, `fra`-prefixed  
* Updated directory structure
* Minor updates to skelaton
* `auto_init` renamed `fra_init`
* Added `fra_seed`
* Updated Makefile
* Updated README

###v0.3 -- Continued auto.c
* Added the series `fra_is_init`, `fra_size`, `fra_is_seed`

###v0.4 -- Finished auto.c
* Added `fra_free`, `fra_step`, and `fra_get_states`
* Cleaned up unneeded headers in src/lib/include
* Divided src/lib/frandauto.c into src/lib/conv.c and src/lib/next.c
* Updated Makefile

###v0.5 -- Added debug targets to Makefile
* Makefile build debug targets under the tag `debug`
* Debug targets use gdb debugger

<!-- vim : set ts=2 sw=2 et syn=markdown : -->
