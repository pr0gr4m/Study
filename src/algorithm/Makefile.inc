# Makefile.inc - common definitions used by all makefiles

# Library lists
LINUX_LIBRT = -lrt
LINUX_LIBDL = -ldl
LINUX_LIBACL = -lacl
LINUX_LIBCRYPT = -lcrypt
LINUX_LIBCAP = -lcap

# Set compiler
CC = gcc
CXX = g++

# Set flags
IMPL_CFLAGS = -std=c++11 \
			  -D_DEFAULT_SOURCE \
			  -g \
			  -pedantic \
			  -Wall \
			  -W

CPPFLAGS = ${IMPL_CFLAGS}

RM = rm -f
