# Makefile to build all programs in all subdirectories
#
# DIRS is a list of all subdirectories containing makefiles
# (The library directory is first so that the library gets built first)
#

DIRS = 	06.BruthForce

BUILD_DIRS = ${DIRS}

# Dummy targets for building and clobbering everything in all subdirectories

all: 	
	@ for dir in ${BUILD_DIRS}; do (cd $${dir}; ${MAKE}) ; done

allgen: 
	@ for dir in ${BUILD_DIRS}; do (cd $${dir}; ${MAKE} allgen) ; done

clean: 
	@ for dir in ${BUILD_DIRS}; do (cd $${dir}; ${MAKE} clean) ; done
